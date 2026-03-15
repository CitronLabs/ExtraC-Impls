#pragma once
#define __ENV_PYTHON__
#include "../../pkg.h"


#ifndef __ENV_PYTHON_IMPORT__
#define package env_Python

Class(Object,
INIT(),
FMT(),

private(PyObject* object;)
){
	errvt 		method(Object, setAttrib,  strc8 name, pkg(Object));
	pkg(Object)* 	method(Object, getAttrib,  strc8 name);
	pkg(Object)* 	method(Object, callMethod, strc8 name, __);
	pkg(Object)* 	method(Object, call, __);
};

#undef package
#endif
