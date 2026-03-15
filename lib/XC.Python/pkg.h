/*---------------------------------------------------------------------------
MIT License

Copyright (c) 2025 CitronLabs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
---------------------------------------------------------------------------*/
#pragma once

#include "API/pkg.h"

#include <XC.pkg.h>
#include "../XC.Common/pkg.h"

#ifndef __ENV_PYTHON__
#include "Runtime/pkg.h"
#include "Devices/pkg.h"
#include "Lib/pkg.h"

#define package env

Interface(Python,
  values(Version, word,
	MAJOR,
	MINOR,
	PATCH
  )	
	interface(env_Python_Runtime) 	Runtime;

	submodule(Lib,
		interface(env_Python_Object) 	Object;
		interface(env_Python_List) 	List;
		interface(env_Python_Module) 	Module;
		errvt fn(init)();
	)
);

#undef package
#endif
