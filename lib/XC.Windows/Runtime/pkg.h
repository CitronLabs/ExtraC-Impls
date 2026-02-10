#pragma once
#define __ENV_WINDOWS__
#include "../pkg.h"
#include "../Lib/pkg.h"


#ifndef __ENV_WINDOWS_RUNTIME__
#define package env_Windows

Interface(Runtime,
  submodule(Memory,
	errvt fn(init)();
  )
  submodule(Device,
	errvt 				fn(init)();
	env_Common_Devices_Manager*     fn(getManager)();

	env_Common_Devices_ID fn(getIO)(), fn(getSys)();

	interface(device) IO, Sys;

	submodule(Resource,
		interface(stream)
	   		Console,
	   		StdOut,
	   		StdIn,
	   		StdErr;

	   	interface(register)
	    		Locale, 
	    		WorkDir, 
	    		CliArgs;
	)
  )
	void fn(init)();
)

#undef package
#endif
