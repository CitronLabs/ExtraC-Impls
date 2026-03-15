#pragma once
#define __ENV_WINDOWS__
#include "../pkg.h"
#include "../Lib/pkg.h"


#ifndef __ENV_WINDOWS_RUNTIME__
#define package env_Windows

struct __xc_stateData {
	u64 magic,

	rbx, rbp, r12, r13, 
	r14, r15, rsp, rip,
    	rdi, rsi; 
};


Interface(Runtime,
	
	submodule(Resource,
		env_Common_Devices_Manager*     
	   		fn(getManager)();
		
		std_Memory*     
	   		fn(getMemory)();

	   	errvt fn(init)();
	)


	void fn(init)();
)

#undef package
#endif
