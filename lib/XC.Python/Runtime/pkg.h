#pragma once
#define __ENV_PYTHON__
#include "../pkg.h"


#ifndef __ENV_PYTHON_RUNTIME__
#define package env_Python

Interface(Runtime,
	
	void fn(init)();
)

#undef package
#endif
