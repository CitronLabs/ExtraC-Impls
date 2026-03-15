import os
import sys
import json
import uuid
import glob
import shutil
import argparse
from datetime import datetime

# --- Configuration & Setup ---
ISSUES_DIR = os.path.join("docs", "Issues")
BIN_DIR = os.path.join(ISSUES_DIR, ".bin")
CONFIG_FILE = ".tracker_config.json"

def ensure_setup():
    """Ensure all required directories, gitignores, and config files exist."""
    if not os.path.exists(ISSUES_DIR): 
        os.makedirs(ISSUES_DIR)
    if not os.path.exists(BIN_DIR): 
        os.makedirs(BIN_DIR)
    
    # Auto-gitignore the bin directory so deleted issues don't clog up git commits
    gitignore_path = os.path.join(BIN_DIR, ".gitignore")
    if not os.path.exists(gitignore_path):
        with open(gitignore_path, 'w') as f:
            f.write("*\n!.gitignore\n")
    
    # Setup initial config if missing
    if not os.path.exists(CONFIG_FILE):
        with open(CONFIG_FILE, 'w') as f:
            json.dump({
                "current_user": None, 
                "users": {}, 
                "tags": ["bug", "feature", "docs", "ui", "backend", "frontend"]
            }, f, indent=4)

def load_config():
    ensure_setup()
    with open(CONFIG_FILE, 'r') as f: 
        return json.load(f)

def save_config(config):
    with open(CONFIG_FILE, 'w') as f: 
        json.dump(config, f, indent=4)

# --- User Management ---
def handle_user(args):
    """Registers or updates a user in the local config."""
    config = load_config()
    username = args.username
    
    # Require email only for brand new users
    if username not in config["users"] and not args.email:
        print("Error: --email is required for new users.")
        sys.exit(1)
        
    user_data = config["users"].get(username, {})
    if args.email: user_data["email"] = args.email
    if args.org: user_data["organization"] = args.org
    if args.links: user_data["links"] = args.links
    
    config["users"][username] = user_data
    
    # Set as active user if requested or if it's the first user ever
    if args.set_active or not config.get("current_user"):
        config["current_user"] = username
        
    save_config(config)
    print(f"Saved profile for '{username}'.")

def handle_user_list(args):
    """Outputs a list of formatted user strings for the TUI to consume."""
    config = load_config()
    for uname, data in config["users"].items():
        if args.org and data.get("organization") != args.org: 
            continue
        print(f"{uname} | {data.get('email')} | Org: {data.get('organization','N/A')} | Links: {data.get('links', 'None')}")

# --- Issue Parsing & Formatting ---
def parse_issue_file(filepath):
    """Safely extracts metadata and content from a markdown issue file."""
    try:
        with open(filepath, 'r', encoding='utf-8') as f: 
            lines = f.readlines()
    except FileNotFoundError:
        return None
        
    if not lines: 
        return None
        
    title = lines[0].strip('# \n')
    start_idx, end_idx = -1, -1
    
    # Find the bounds of the metadata codeblock
    for i, line in enumerate(lines):
        if line.strip().startswith('```'):
            if start_idx == -1: 
                start_idx = i
            else:
                end_idx = i
                break
                
    # Default metadata
    metadata = {
        "Picked-Up": "None", 
        "Status": "NOT_STARTED", 
        "Module": "None", 
        "Tags": "None", 
        "Priority": "5"
    }
    
    # Populate found metadata
    if start_idx != -1 and end_idx != -1:
        for line in lines[start_idx+1:end_idx]:
            if line.startswith('- '):
                parts = line[2:].split(':', 1)
                if len(parts) == 2: 
                    metadata[parts[0].strip()] = parts[1].strip()
                    
    return {
        "title": title, 
        "metadata": metadata, 
        "raw_lines": lines, 
        "block_start": start_idx, 
        "block_end": end_idx
    }

# --- Core Issue Actions ---
def register_tags(tags_str):
    """Adds any newly encountered tags to the central config."""
    if not tags_str or tags_str == "None": 
        return
        
    config = load_config()
    current_tags = set(config.get("tags", []))
    
    for t in tags_str.split(','):
        current_tags.add(t.strip())
        
    config["tags"] = sorted(list(current_tags))
    save_config(config)

def handle_create(args):
    """Generates a new markdown file with the required strict format."""
    config = load_config()
    current_user = config.get("current_user")
    
    if not current_user: 
        sys.exit("Error: No active user. Create a user first.")
        
    now = datetime.now()
    filename = f"{current_user}_{now.strftime('%m-%d-%Y')}_{now.strftime('%H\'%M')}_{uuid.uuid4().hex[:8]}.md"
    filepath = os.path.join(ISSUES_DIR, filename)
    
    register_tags(args.tags)
    
    content = f"# {args.title}\n"
    content += "```\n"
    content += f"- Picked-Up: None\n"
    content += f"- Status: NOT_STARTED\n"
    content += f"- Module: {args.module}\n"
    content += f"- Tags: {args.tags}\n"
    content += f"- Priority: {args.priority}\n"
    content += "```\n\n"
    content += f"{args.description}\n"
    
    with open(filepath, 'w', encoding='utf-8') as f: 
        f.write(content)
        
    print(filepath)

def handle_list(args):
    """Filters and prints issues for the TUI to consume as pipe-separated rows."""
    # Depending on args.bin, search in normal dir or bin dir
    target_dir = BIN_DIR if args.bin else ISSUES_DIR
    files = [f for f in glob.glob(os.path.join(target_dir, "*.md")) if not os.path.basename(f).startswith('.')]
    
    for filepath in files:
        filename = os.path.basename(filepath)
        parsed = parse_issue_file(filepath)
        if not parsed: continue
        meta = parsed["metadata"]
        
        # Apply filters
        if args.status and meta.get("Status") != args.status: continue
        if args.picked_up and meta.get("Picked-Up") != args.picked_up: continue
        if args.module and meta.get("Module") != args.module: continue
        if args.tag and args.tag not in meta.get("Tags", ""): continue
            
        print(f"{filename}|{meta.get('Status')}|{meta.get('Priority')}|{meta.get('Tags')[:15]}|{meta.get('Module')[:15]}|{parsed['title']}")

def handle_copy(args):
    """Duplicates an existing issue template to a new file."""
    src = os.path.join(ISSUES_DIR, args.filename)
    parsed = parse_issue_file(src)
    
    if not parsed: 
        sys.exit("File not found.")
    
    config = load_config()
    now = datetime.now()
    new_filename = f"{config.get('current_user')}_{now.strftime('%m-%d-%Y')}_{now.strftime('%H\'%M')}_{uuid.uuid4().hex[:8]}.md"
    new_filepath = os.path.join(ISSUES_DIR, new_filename)
    
    lines = parsed["raw_lines"]
    lines[0] = f"# {args.title}\n" # Swap out the title
    
    with open(new_filepath, 'w', encoding='utf-8') as f: 
        f.writelines(lines)
        
    print(f"Copied to {new_filename}")

def handle_bin(args):
    """Manages soft-deletions (recycle bin functionality)."""
    if args.action == "delete":
        shutil.move(os.path.join(ISSUES_DIR, args.filename), os.path.join(BIN_DIR, args.filename))
        print(f"Moved {args.filename} to bin.")
    elif args.action == "restore":
        shutil.move(os.path.join(BIN_DIR, args.filename), os.path.join(ISSUES_DIR, args.filename))
        print(f"Restored {args.filename}.")
    elif args.action == "empty":
        for f in glob.glob(os.path.join(BIN_DIR, "*.md")): 
            os.remove(f)
        print("Bin emptied.")

def handle_update(args):
    """Updates an existing issue's metadata in place."""
    filepath = os.path.join(ISSUES_DIR, args.filename)
    if not os.path.exists(filepath):
        sys.exit(f"Error: Could not find issue {args.filename}")
        
    parsed = parse_issue_file(filepath)
    if not parsed or parsed["block_start"] == -1:
        sys.exit("Error: File format is invalid or missing metadata block.")
        
    meta = parsed["metadata"]
    
    if args.status: meta["Status"] = args.status
    if args.pickup: meta["Picked-Up"] = args.pickup
    if args.module: meta["Module"] = args.module
    if args.tags: meta["Tags"] = args.tags
    if args.priority: meta["Priority"] = str(args.priority)
    
    lines = parsed["raw_lines"]
    new_block = ["```\n"]
    for k, v in meta.items():
        new_block.append(f"- {k}: {v}\n")
    new_block.append("```\n")
    
    new_lines = lines[:parsed["block_start"]] + new_block + lines[parsed["block_end"]+1:]
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)
        
    print(f"Successfully updated {args.filename}")

# --- CLI Setup ---
def main():
    parser = argparse.ArgumentParser(description="Local Markdown Issue Tracker Backend")
    subparsers = parser.add_subparsers(dest="command", required=True)
    
    # User Management
    u_p = subparsers.add_parser("user")
    u_p.add_argument("username")
    u_p.add_argument("--email")
    u_p.add_argument("--org")
    u_p.add_argument("--links")
    u_p.add_argument("--set-active", action="store_true")
    
    subparsers.add_parser("user-list").add_argument("--org")
    subparsers.add_parser("get-tags")
    
    # Issue Creation
    c_p = subparsers.add_parser("create")
    c_p.add_argument("title")
    c_p.add_argument("--module", required=True)
    c_p.add_argument("--tags", default="None")
    c_p.add_argument("--priority", default=5)
    c_p.add_argument("--description", default="")
    
    # Issue Listing
    l_p = subparsers.add_parser("list")
    l_p.add_argument("--status")
    l_p.add_argument("--picked-up")
    l_p.add_argument("--module")
    l_p.add_argument("--tag")
    l_p.add_argument("--bin", action="store_true")
    
    # Issue Copying
    copy_p = subparsers.add_parser("copy")
    copy_p.add_argument("filename")
    copy_p.add_argument("title")
    
    # Bin Management
    bin_p = subparsers.add_parser("bin")
    bin_p.add_argument("action", choices=["delete", "restore", "empty"])
    bin_p.add_argument("--filename", required=False)
    
    # Issue Updating
    update_parser = subparsers.add_parser("update")
    update_parser.add_argument("filename")
    update_parser.add_argument("--status", choices=["NOT_STARTED", "IN_PROGRESS", "DONE"])
    update_parser.add_argument("--pickup")
    update_parser.add_argument("--module")
    update_parser.add_argument("--tags")
    update_parser.add_argument("--priority", type=int, choices=range(1, 6))
    
    args = parser.parse_args()
    ensure_setup()
    
    if args.command == "user": handle_user(args)
    elif args.command == "user-list": handle_user_list(args)
    elif args.command == "get-tags": print("\n".join(load_config().get("tags", [])))
    elif args.command == "create": handle_create(args)
    elif args.command == "list": handle_list(args)
    elif args.command == "copy": handle_copy(args)
    elif args.command == "bin": handle_bin(args)
    elif args.command == "update": handle_update(args)

if __name__ == "__main__": 
    main()
