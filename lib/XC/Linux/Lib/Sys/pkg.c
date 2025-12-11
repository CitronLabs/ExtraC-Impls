#include <XC/pkg.h>

/*--------------------------------------|
 *					|
 *	    XC.Sys.Arch Module		|
 *					|
 *------------------------------------*/
#define module XC, Sys, Arch

export(
SUBMODULE(),
VALUES(),
	addCarry, subCarry, getFlags, 
	getFramePtr, getInstructionPtr, 
	getStackPtr, saveRegs, loadRegs,
	setFlags
);

#undef module

/*--------------------------------------|
 *					|
 *	   XC.Sys.Locale Module		|
 *					|
 *------------------------------------*/
#define module XC, Sys, Locale

moduleValues(Temp,
	Celsius,,
	Fahrenheit,,
)

moduleValues(Measure,
	Metric,,
	Imperial,,
)

export(
SUBMODULE(),
VALUES(Temp, Measure),
);

#undef module


/*--------------------------------------|
 *					|
 *	       XC.Sys Module		|
 *					|
 *------------------------------------*/
#define module XC, Sys


moduleValues(ExitCode,
	FAILURE, -1,
	SUCCESS,  0,
)

export(
SUBMODULE(Arch),
VALUES(ExitCode),
	saveState, loadState, terminate
)


#undef module
