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
		errvt err = ERR(ERR.FAIL, "Failed to run command");
		 GetLastError()
	});

}
processHandle moduleFn(execute)(const char* program, const char* arguments);
processHandle moduleFn(thisProcess)(){
	return GetCurrentProcess();
}

moduleHandle moduleFn(load)(const char* modulePath);
pntr moduleFn(symbol)(moduleHandle modulePath, const char* symbol);
errvt moduleFn(unload)(moduleHandle modulePath);

void moduleFn(terminate)(processHandle process, word status, word flags); 

bool moduleFn(saveState)(stateData* state);
errvt moduleFn(loadState)(stateData state);

