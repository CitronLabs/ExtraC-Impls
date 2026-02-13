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
  submodule(System,
    submodule(Scheduler,
      submodule(Thread,
	
      )
      submodule(Process,
	processHandle	fn(current)();
	processHandle 	fn(run)(const char* path, const char* args);
	errvt 		fn(kill)(processHandle);

      )
	errvt 		fn(init)();
    )
    submodule(Module,
	moduleHandle 	fn(load)(const char* module, uword flags);
	errvt 		fn(unload)(moduleHandle);
	pntr 		fn(symbol)(moduleHandle, const char* symbol);
	errvt 		fn(init)();
    )
  )
	void fn(init)();
)

#undef package
#endif
