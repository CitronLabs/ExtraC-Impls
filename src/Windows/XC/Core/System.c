#include "WinEnv.h"

#define module core, System

#define MAX_COMMAND_LEN 1028

errvt moduleFn(command)(const char* command){

	c16* commandWide = alloca(strnlen(command, MAX_COMMAND_LEN));

	std.String.Encoding.UTF8.toUtf16(
		generic command, MAX_COMMAND_LEN, 
		commandWide,  	 MAX_COMMAND_LEN
	);

	/*Windows Docs
		The return value is cast as an HINSTANCE 
		for backward compatibility with 16-bit 
		Windows applications. It is not a true HINSTANCE, 
		however. It can be cast only to an INT_PTR
	*/
	var result = (INT_PTR)ShellExecuteW(NULL, L"open", L"cmd.exe", commandWide, NULL, SW_HIDE);

	
return (result > 32) ? OK : ({
		var err    = ERR(ERR.FAIL, "Failed to run command");
		var errmsg = WinLib.Error.getMsg(GetLastError());

		printlnErr("Error Info: ", $(errmsg));

		WinLib.Error.freeMsg(errmsg);

		err;
	});

}
processHandle moduleFn(execute)(const char* program, const char* arguments){
	STARTUPINFOW si = { sizeof(si) };
    	PROCESS_INFORMATION pi;
    
	c16
	    * programWide = alloca(strnlen(program, MAX_COMMAND_LEN)),
	    * argumentsWide = alloca(strnlen(arguments, MAX_COMMAND_LEN));

	std.String.Encoding.UTF8.toUtf16(
		generic program, MAX_COMMAND_LEN, 
		programWide,  	 MAX_COMMAND_LEN
	);

	std.String.Encoding.UTF8.toUtf16(
		generic arguments, MAX_COMMAND_LEN, 
		argumentsWide,     MAX_COMMAND_LEN
	);


    	if (CreateProcessW(
		generic programWide,	//Application Name,
		generic argumentsWide,  //Command Line Args,
		NULL, 			//Process Attributes,
		NULL,                   //Thread Attributes,
		FALSE,                  //Inherit Handles,
		0,                      //Creation Flags,
		NULL,                   //Environment,
		NULL,                   //Current Directory,
		&si,                    //Startup Info,
		&pi                     //Process Information
	)) {
    	    	CloseHandle(pi.hThread);
    	    	return pi.hProcess;
    	}

return nil;
}
processHandle moduleFn(thisProcess)(){
	return GetCurrentProcess();
}

// --- Module Loading --

moduleHandle moduleFn(load)(const char* modulePath, uword flags){
return WinRTSys.Module.load(modulePath, flags);
}
pntr moduleFn(symbol)(moduleHandle handle, const char* symbol){
return WinRTSys.Module.symbol(handle, symbol);
}
errvt moduleFn(unload)(moduleHandle handle){
return WinRTSys.Module.unload(handle);
}

void moduleFn(terminate)(word status, word flags){
	ExitProcess(status);
}


// --- State Loading / Saving ---

#define XC_CTX_MAGIC 0x58435F4354585F31

struct __xc_stateData {
	u64 magic, status, cookie;
	struct {
    	    u64 
		rbx, rbp, r12, r13, 
		r14, r15, rsp, rip,
		rdi, rsi; 
	} context;
};

bool moduleFn(saveState)(stateData* statePtr){
	
	*statePtr = malloc(sizeof(stateData));
	var state = *statePtr;

    	state->magic   = XC_CTX_MAGIC;
    	bool was_jumped = false;

    	__asm__ __volatile__ (
    	    ".intel_syntax noprefix\n"
    	    "mov [rax + 8],  rbx\n"
    	    "mov [rax + 16], rbp\n"
    	    "mov [rax + 24], r12\n"
    	    "mov [rax + 32], r13\n"
    	    "mov [rax + 40], r14\n"
    	    "mov [rax + 48], r15\n"
    	    "mov [rax + 56], rsp\n"
    	    "lea rdx, [rip + 1f]\n"   /* Get address of label '1' */
    	    "mov [rax + 64], rdx\n"   /* Save as RIP */
    	    "mov [rax + 72], rdi\n"
    	    "mov [rax + 80], rsi\n"
    	    "jmp 2f\n"                /* Skip the resume point during initial save */
    	    "1:\n"                    /* RESUMPTION POINT */
    	    "mov %0, 1\n"             /* Set was_jumped = 1 */
    	    "2:\n"                    /* END OF SAVE */
    	    ".att_syntax prefix\n"
    	    : "+r"(was_jumped) 
    	    : "a"(&state->context)                /* ctx in RAX */
    	    : "rdx", "memory"
    	);

return was_jumped;
}
errvt moduleFn(loadState)(stateData state){
	nonull(state) return err;
	if (state->magic != XC_CTX_MAGIC)
	    return ERR(ERR.INVALID, "State corruption detected, could not load");
	

	__asm__ __volatile__ (
    	".intel_syntax noprefix\n"
    	"mov rbx, [rax + 8]\n"
    	"mov rbp, [rax + 16]\n"
    	"mov r12, [rax + 24]\n"
    	"mov r13, [rax + 32]\n"
    	"mov r14, [rax + 40]\n"
    	"mov r15, [rax + 48]\n"
    	"mov rsp, [rax + 56]\n"
    	"mov rdi, [rax + 72]\n"
    	"mov rsi, [rax + 80]\n"
    	"mov rdx, [rax + 64]\n"   /* Load saved RIP */
    	"jmp rdx\n"               /* JUMP BACK */
    	".att_syntax prefix\n"
    	: : "a"(&state->context) : "memory"
    	);


return ERR(ERR.FAIL, "Failed to load state");
}

