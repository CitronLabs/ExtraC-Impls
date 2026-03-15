#pragma once
#define __ENV_WINDOWS__
#include "../../pkg.h"


#ifndef __ENV_WINDOWS_RUNTIME__
#define package env_Windows_Lib_Exec

Class(Process,
INIT(const char* executable, args),
FMT(),
private()
){
	pkg(Process) fn(getCurrent)();

	errvt method(Process, kill, bool force);
};


Class(Thread,
INIT(errvt fn(thread_start)(void* args); void* args),
FMT(),
private()
){
	noFail 		fn(sleep)(len_t millisec);
	errvt 		fn(exit)();
	pkg(Thread) 	fn(getCurrent);

	errvt 		method(Thread, run);
	errvt 		method(Thread, join);
};

Interface_Pkg(
	interface(pkg(Process)) Process;
	interface(pkg(Thread))  Thread;
)

#undef package
#endif
