#define module XC, Sys, Arch
#include <Core/pkg.h>



#define __PKG
#ifdef __PKG
	import(XC)	


	importFn(
		addCarry, subCarry, getFlags, 
		getFramePtr, getInstructionPtr, 
		getStackPtr, saveRegs, loadRegs,
		setFlags
	);

	export(
		addCarry, subCarry, getFlags, 
		getFramePtr, getInstructionPtr, 
		getStackPtr, saveRegs, loadRegs,
		setFlags
	);

#else
#include "../../../pkg.h"

import(env)
import(XC)
import(std)

#endif
#undef module
