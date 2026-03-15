#pragma once
#define __ENV_PYTHON__
#include "../../pkg.h"


#ifndef __ENV_PYTHON_IMPORT__
#define package env_Python

Class(List,
INIT(),
FMT(),
      
private(PyObject* object;)
){};

#undef package
#endif
