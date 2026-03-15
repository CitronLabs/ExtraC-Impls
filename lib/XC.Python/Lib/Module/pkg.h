#pragma once
#define __ENV_PYTHON__
#include "../../pkg.h"
#include "../Object/pkg.h"


#ifndef __ENV_PYTHON_IMPORT__
#define package env_Python


Interface(Module,
	pkg(Object)* fn(import)(strc8 name);
)

#undef package
#endif
