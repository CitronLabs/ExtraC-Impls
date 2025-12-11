#pragma once
#define __ENV_LINUX__
#include "../pkg.h"



#ifndef __ENV_LINUX_OS__
	#include "Memory/pkg.h"

	#define package env_Linux

	Interface(OS,
		interface(env_Linux_OS_Memory) Mem;

	)

	#undef package
#endif
