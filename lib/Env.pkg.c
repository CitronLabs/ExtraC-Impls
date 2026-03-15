#pragma once
#include "Env.pkg.h"
#include "XC.Common/pkg.c"


#if defined(__TUNDRA__) && defined(USE_TUNDRA)
	#define ENV_SUBMODULE Tundra

#elif defined(__PYTHON__) && defined(USE_PYTHON)
	#include "XC.Python/pkg.c"
	#define ENV_SUBMODULE Python
#else
    #if defined(__linux__) || defined(__linux) || defined(linux)
	#include "XC.Linux/pkg.c"
	#define ENV_SUBMODULE Linux
    #endif

    #if defined(_WIN32) || defined(_WIN64)
	#include "XC.Windows/pkg.c"
	#define ENV_SUBMODULE  Windows
    #endif
#endif


#define module env

export(
SUBMODULE(ENV_SUBMODULE),
VALUES(), 
);

#undef ENV_SUBMODULE
#undef module
