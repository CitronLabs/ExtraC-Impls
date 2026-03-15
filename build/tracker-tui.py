import curses
import subprocess
import os

def run_cli(command_list):
    """Executes the tracker.py backend and captures the output."""
    try:
        res = subprocess.run(['python', 'build/tracker-cli.py'] + command_list, capture_output=True, text=True)
        return res.stdout, res.stderr
    except Exception as e:
        return "", str(e)

# --- UI Components ---
def draw_modal_input(stdscr, prompt):
    """Draws a centered pop-up input box. Press ESC to cancel."""
    h, w = stdscr.getmaxyx()
    box_h, box_w = 5, min(60, w - 4)
    y, x = (h - box_h) // 2, (w - box_w) // 2
    
    win = curses.newwin(box_h, box_w, y, x)
    win.box()
    win.addstr(1, 2, prompt, curses.A_BOLD)
    win.addstr(3, 2, "ESC to cancel", curses.A_DIM)
    win.refresh()
    
    curses.echo()
    curses.curs_set(1)
    win.keypad(True)
    
    input_str = ""
    while True:
        ch = win.getch()
        if ch == 27: # ESC key
            input_str = None
            break
        elif ch in (10, 13): # Enter key
            break
        elif ch in (curses.KEY_BACKSPACE, 127, 8): # Backspace handling
            input_str = input_str[:-1]
        else:
            try:
                input_str += chr(ch)
            except:
                pass
            
        win.addstr(2, 2, " " * (box_w - 4)) # clear line
        win.addstr(2, 2, input_str)
        win.refresh()
        
    curses.noecho()
    curses.curs_set(0)
    return input_str.strip() if input_str else None

def draw_help_menu(stdscr, current_tab):
    """Displays a modal help menu with keybinds relevant to the current tab."""
    h, w = stdscr.getmaxyx()
    
    common = [
        "GLOBAL KEYBINDS:",
        "Tab : Switch View",
        "f   : Filter/Sort menu",
        "x   : Clear all filters",
        "q   : Quit",
        "?   : Show this help",
        "",
    ]
    
    tabs_help = {
        0: [
            "ISSUES TAB:",
            "c   : Create new issue",
            "e   : Edit in Neovim",
            "d   : Move to Bin",
            "y   : Copy single issue",
            "B   : BULK COPY (Filters -> Replace)",
        ],
        1: [
            "USERS TAB:",
            "n   : New/Update user",
        ],
        2: [
            "BIN TAB:",
            "r   : Restore issue",
            "E   : Empty bin (Permanent)",
        ]
    }
    
    content = common + tabs_help[current_tab] + ["", "Press any key to close"]
    
    box_h = len(content) + 2
    box_w = 45
    y, x = (h - box_h) // 2, (w - box_w) // 2
    
    win = curses.newwin(box_h, box_w, y, x)
    win.box()
    for i, line in enumerate(content):
        win.addstr(i + 1, 2, line[:box_w-4])
    
    win.refresh()
    win.getch()

def draw_tag_selector(stdscr):
    """A scrolling multi-select checklist for tags with live search filtering."""
    tags_output, _ = run_cli(['get-tags'])
    all_tags = [t for t in tags_output.splitlines() if t]
    
    h, w = stdscr.getmaxyx()
    box_h, box_w = min(20, h-4), min(50, w-4)
    y, x = (h - box_h) // 2, (w - box_w) // 2
    
    win = curses.newwin(box_h, box_w, y, x)
    win.keypad(True)
    
    selected = set()
    search_query = ""
    idx = 0
    
    while True:
        # Filter tags based on search query
        filtered_tags = [t for t in all_tags if search_query.lower() in t.lower()]
        
        # Add new tag option if it doesn't exist
        if search_query and search_query not in all_tags:
            display_tags = [f"(New) {search_query}"] + filtered_tags
        else:
            display_tags = filtered_tags

        if idx >= len(display_tags): idx = max(0, len(display_tags) - 1)
        
        win.clear()
        win.box()
        win.addstr(0, 2, " Tag Selector (Live Search) ", curses.A_BOLD)
        win.addstr(1, 2, f"Search: {search_query}_", curses.A_UNDERLINE)
        win.addstr(box_h-1, 2, " [Space] Toggle | [Enter] Done | [Esc] Cancel ", curses.A_DIM)
        
        # Render visible tags
        for i, tag_label in enumerate(display_tags[:box_h-4]):
            actual_tag = tag_label.replace("(New) ", "")
            mark = "[x]" if actual_tag in selected else "[ ]"
            attr = curses.A_REVERSE if i == idx else curses.A_NORMAL
            win.addstr(i+2, 2, f"{mark} {tag_label}"[:box_w-4], attr)
            
        win.refresh()
        ch = win.getch()
        
        if ch == 27: # ESC
            return None
        elif ch in (10, 13): # Enter
            break
        elif ch == curses.KEY_UP and idx > 0: 
            idx -= 1
        elif ch == curses.KEY_DOWN and idx < len(display_tags) - 1: 
            idx += 1
        elif ch == ord(' '): # Spacebar to toggle
            if display_tags:
                actual_tag = display_tags[idx].replace("(New) ", "")
                if actual_tag in selected: 
                    selected.remove(actual_tag)
                else: 
                    selected.add(actual_tag)
        elif ch in (curses.KEY_BACKSPACE, 127, 8):
            search_query = search_query[:-1]
        elif 32 <= ch <= 126: # Printable chars for search
            search_query += chr(ch)
            
    return ",".join(selected) if selected else "None"

def get_raw_data(tab_index, filters, sort_config):
    """Helper to get filtered/sorted dictionary list for issues/users."""
    if tab_index == 0 or tab_index == 2:
        args = ['list']
        if tab_index == 2: args.append('--bin')
        out, _ = run_cli(args)
        raw_data = []
        for line in out.splitlines():
            if '.md|' in line:
                parts = line.split('|')
                raw_data.append({
                    'file': parts[0],
                    'status': parts[1],
                    'prio': int(parts[2]) if parts[2].isdigit() else 5,
                    'tags': parts[3],
                    'module': parts[4],
                    'title': parts[5]
                })
        filtered = [d for d in raw_data if all(v.lower() in d.get(k, '').lower() for k, v in filters.items() if v)]
        s_field = sort_config['field']
        if s_field in ['prio', 'status', 'module', 'title']:
            filtered.sort(key=lambda x: x.get(s_field, ''), reverse=sort_config['reverse'])
        return filtered
    
    elif tab_index == 1:
        out, _ = run_cli(['user-list'])
        raw_users = []
        for line in out.splitlines():
            if '|' in line:
                parts = [p.strip() for p in line.split('|')]
                raw_users.append({
                    'name': parts[0],
                    'email': parts[1],
                    'org': parts[2].replace('Org: ', ''),
                    'links': parts[3].replace('Links: ', '')
                })
        filtered = [u for u in raw_users if all(v.lower() in u.get(k, '').lower() for k, v in filters.items() if v)]
        s_field = sort_config['field']
        if s_field in ['name', 'email', 'org']:
            filtered.sort(key=lambda x: x.get(s_field, ''), reverse=sort_config['reverse'])
        return filtered
    return []

def get_data(tab_index, filters, sort_config):
    """Formats raw data for TUI display."""
    items, display = [], []
    raw = get_raw_data(tab_index, filters, sort_config)
    
    for d in raw:
        if tab_index == 0 or tab_index == 2:
            items.append(d['file'])
            if tab_index == 0:
                display.append(f"{d['file'][:30]:<30} | {d['status']:<11} | {d['prio']:<4} | {d['tags']:<15} | {d['module']:<15} | {d['title']}")
            else:
                display.append(f"{d['file'][:40]:<40} | DELETED | {d['title']}")
        elif tab_index == 1:
            items.append(d['name'])
            display.append(f"{d['name']:<15} | {d['email']:<25} | Org: {d['org']:<15} | Links: {d['links']}")
                
    return items, display

def main(stdscr):
    curses.curs_set(0)
    stdscr.nodelay(False)
    
    tabs = ["ISSUES", "USERS", "BIN"]
    current_tab = 0
    current_row = 0
    message = "Tab: Switch | f: Filter | B: Bulk Copy | ?: Help | q: Quit"

    issue_filters = {"status": "", "module": "", "tags": "", "title": ""}
    user_filters = {"email": "", "org": "", "links": ""}
    sort_configs = {
        0: {"field": "prio", "reverse": False},
        1: {"field": "name", "reverse": False},
        2: {"field": "file", "reverse": False}
    }

    while True:
        filters = issue_filters if (current_tab == 0 or current_tab == 2) else user_filters
        items, display_lines = get_data(current_tab, filters, sort_configs[current_tab])
        
        if current_row >= len(items): 
            current_row = max(0, len(items) - 1)
        
        stdscr.clear()
        h, w = stdscr.getmaxyx()

        # Render Header Tabs
        tab_str = ""
        for i, t in enumerate(tabs):
            tab_str += f" [{t}] " if i == current_tab else f"  {t}  "
        stdscr.addstr(0, 0, tab_str.ljust(w - 1)[:w - 1], curses.A_REVERSE)
        
        # Render Headers
        if current_tab == 0:
            stdscr.addstr(2, 0, "FILENAME".ljust(30) + " | STATUS      | PRIO | TAGS            | MODULE          | TITLE")
            stdscr.addstr(3, 0, "-" * min(120, w - 1))
        elif current_tab == 1:
            stdscr.addstr(2, 0, f"USER MANAGEMENT (Sorted by: {sort_configs[1]['field']})")
            stdscr.addstr(3, 0, "-" * min(120, w - 1))
        elif current_tab == 2:
            stdscr.addstr(2, 0, "RECYCLE BIN")
            stdscr.addstr(3, 0, "-" * min(120, w - 1))
            
        # Render List Items
        for idx, line in enumerate(display_lines):
            y = 4 + idx
            if y >= h - 2: break
            attr = curses.A_STANDOUT if idx == current_row else curses.A_NORMAL
            stdscr.addstr(y, 0, line[:w-1], attr)

        # Render Filter Info
        active_filters = [f"{k}:{v}" for k, v in filters.items() if v]
        filter_msg = f" | Filters: {', '.join(active_filters)}" if active_filters else ""
        stdscr.addstr(h - 1, 0, f" Message: {message}{filter_msg}"[:w-1], curses.A_BOLD)
        stdscr.refresh()
        
        key = stdscr.getch()

        if key == ord('q'): 
            break
        elif key == ord('?'):
            draw_help_menu(stdscr, current_tab)
        elif key == 9: # TAB
            current_tab = (current_tab + 1) % 3
            current_row = 0
            message = f"Switched to {tabs[current_tab]}"
        elif key == curses.KEY_UP and current_row > 0: 
            current_row -= 1
        elif key == curses.KEY_DOWN and current_row < len(items) - 1: 
            current_row += 1
        
        elif key == ord('f'):
            if current_tab in (0, 2):
                field = draw_modal_input(stdscr, "Field (status/module/tags/title) or 'sort':")
                if field == "sort":
                    s_field = draw_modal_input(stdscr, "Sort by (prio/status/module/title):")
                    if s_field: sort_configs[current_tab] = {"field": s_field, "reverse": False}
                elif field in issue_filters:
                    val = draw_modal_input(stdscr, f"Filter {field} by:")
                    issue_filters[field] = val if val is not None else issue_filters[field]
            elif current_tab == 1:
                field = draw_modal_input(stdscr, "Field (email/org/links) or 'sort':")
                if field == "sort":
                    s_field = draw_modal_input(stdscr, "Sort by (name/email/org):")
                    if s_field: sort_configs[1] = {"field": s_field, "reverse": False}
                elif field in user_filters:
                    val = draw_modal_input(stdscr, f"Filter {field} by:")
                    user_filters[field] = val if val is not None else user_filters[field]

        elif key == ord('x'):
            if current_tab in (0, 2): issue_filters = {k: "" for k in issue_filters}
            else: user_filters = {k: "" for k in user_filters}
            message = "Filters cleared."

        # Handle Actions: ISSUES TAB
        elif current_tab == 0:
            if key == ord('c'):
                title = draw_modal_input(stdscr, "Issue Title:")
                if title:
                    mod = draw_modal_input(stdscr, "Module Path:") or "None"
                    prio = draw_modal_input(stdscr, "Priority (1-5):") or "3"
                    tags = draw_tag_selector(stdscr) or "None"
                    run_cli(['create', title, '--module', mod, '--priority', prio, '--tags', tags])
                    message = "Issue created."
            
            elif key == ord('B'): # BULK COPY FEATURE
                search_str = draw_modal_input(stdscr, "Bulk Copy - FIND string (e.g. old module name):")
                if search_str:
                    replace_str = draw_modal_input(stdscr, "Bulk Copy - REPLACE with:")
                    if replace_str is not None:
                        # Get currently filtered raw issues
                        raw_issues = get_raw_data(0, issue_filters, sort_configs[0])
                        count = 0
                        for issue in raw_issues:
                            # We create a new title/module by replacing the search string
                            new_title = issue['title'].replace(search_str, replace_str)
                            new_module = issue['module'].replace(search_str, replace_str)
                            
                            # Use CLI to create the copy
                            # Note: We use 'create' here because 'copy' only handles title changes currently
                            cmd = ['create', new_title, '--module', new_module, 
                                   '--priority', str(issue['prio']), '--tags', issue['tags']]
                            run_cli(cmd)
                            count += 1
                        message = f"Bulk copied {count} issues."

            elif key == ord('d') and items:
                run_cli(['bin', 'delete', '--filename', items[current_row]])
                message = "Moved issue to bin."
            elif key == ord('e') and items:
                filepath = os.path.join("docs", "Issues", items[current_row])
                curses.def_prog_mode(); curses.endwin()
                subprocess.run(['nvim', filepath])
                stdscr.clear(); curses.reset_prog_mode()
                message = "Returned from Neovim."
            elif key == ord('y') and items: 
                title = draw_modal_input(stdscr, "New Title for Copy:")
                if title:
                    run_cli(['copy', items[current_row], title])
                    message = "Issue copied."
                    
        # Handle Actions: USERS TAB
        elif current_tab == 1:
            if key == ord('n'):
                uname = draw_modal_input(stdscr, "Username:")
                if uname:
                    email = draw_modal_input(stdscr, "Email:")
                    org = draw_modal_input(stdscr, "Org:")
                    links = draw_modal_input(stdscr, "Links:")
                    cmd = ['user', uname]
                    if email: cmd += ['--email', email]
                    if org: cmd += ['--org', org]
                    if links: cmd += ['--links', links]
                    out, err = run_cli(cmd)
                    message = out.strip() or err.strip()
                    
        # Handle Actions: BIN TAB
        elif current_tab == 2:
            if key == ord('r') and items:
                run_cli(['bin', 'restore', '--filename', items[current_row]])
                message = "Issue restored."
            elif key == ord('E'):
                run_cli(['bin', 'empty'])
                message = "Bin emptied."

if __name__ == "__main__":
    curses.wrapper(main)
