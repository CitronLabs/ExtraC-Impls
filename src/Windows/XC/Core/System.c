#include "WinEnv.h"
#include <XC.Builtin/Assembly.pkg.h>

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

moduleHandle moduleFn(load)(const char* modulePath){
	nonull(modulePath) return nil;

	c16* modulePathWide = alloca(strnlen(modulePath, MAX_COMMAND_LEN));

	std.String.Encoding.UTF8.toUtf16(
		generic modulePath, MAX_COMMAND_LEN, 
		modulePathWide,     MAX_COMMAND_LEN
	);

	var result = LoadLibraryW(generic modulePathWide);

return result ? result : ({
		ERR(ERR.FAIL, "Failed to run command");
		var errmsg = WinLib.Error.getMsg(GetLastError());

		printlnErr("Error Info: ", $(errmsg));

		WinLib.Error.freeMsg(errmsg);

		nil;
});
}
pntr moduleFn(symbol)(moduleHandle handle, const char* symbol){
	nonull(handle, symbol) return nil;

	// Note: GetProcAddress ONLY accepts ANSI (LPCSTR). 
    	// Function names in DLLs are almost exclusively ASCII/ANSI.
return GetProcAddress(generic handle, symbol);
}
errvt moduleFn(unload)(moduleHandle handle){
	nonull(handle) return err;

return FreeLibrary(generic handle) ? OK : 
({
	var err    = ERR(ERR.FAIL, "Failed to run command");
	var errmsg = WinLib.Error.getMsg(GetLastError());

	printlnErr("Error Info: ", $(errmsg));

	WinLib.Error.freeMsg(errmsg);

	err;
});
}

void moduleFn(terminate)(word status, word flags){
	ExitProcess(status);
}


struct __xc_stateData {
	u64 magic, status, cookie;
	asm_context context;
};

bool moduleFn(saveState)(stateData* statePtr){
	
	*statePtr = malloc(sizeof(stateData));
	var state = *statePtr;

	asm(
		ctxsave(r1)
		input_ref(*state)
	)

}
errvt moduleFn(loadState)(stateData state){
	


return ERR(ERR.FAIL, "Failed to load state");
}

