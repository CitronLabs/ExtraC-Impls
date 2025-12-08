#define module XC, Sys
#include <Core/pkg.h>



#define __PKG
#ifdef __PKG

	#include "Arch.c"
	#define module XC, Sys

	import(XC)	


	importFn(terminate, loadState, saveState)
	
#else
#include "../../../pkg.h"

import(env)
import(XC)
import(std)

#endif
