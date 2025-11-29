#pragma once
#define __LINUX__
#include "../pkg.h"



#ifndef __LINUX_OS__
	#include "FS/pkg.h"
	#include "Memory/pkg.h"

	#define package lin

	Interface(OS,
		interface(lin_Memory) Mem;

	)

	#undef package
#endif
