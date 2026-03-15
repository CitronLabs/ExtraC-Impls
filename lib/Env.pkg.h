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

#ifndef __ENV__
#define __GODOT__
#define USE_GODOT

#if defined(__TUNDRA__) && defined(USE_TUNDRA)
	#include "XC.Tundra/pkg.h"

#elif defined(__PYTHON__) && defined(USE_PYTHON)
	#include "XC.Python/pkg.h"

#elif defined(__GODOT__) && defined(USE_GODOT)
	#include "XC.Godot/pkg.h"
#else
    #if defined(__linux__) || defined(__linux) || defined(linux)
	#include "XC.Linux/pkg.h"
    #endif

    #if defined(_WIN32) || defined(_WIN64)
	#include "XC.Windows/pkg.h"
    #endif
#endif

#include "XC.pkg.h"
#include "XC.Common/pkg.h"

#define package env

Module(env){
    #if defined(__TUNDRA__) && defined(USE_TUNDRA)
		interface(env_Tundra)  Tundra;

    #elif defined(__PYTHON__) && defined(USE_PYTHON)
		interface(env_Python)  Python;

    #elif defined(__GODOT__) && defined(USE_GODOT)
		interface(env_Godot)  Godot;

    #else
	#if defined(__linux__) || defined(__linux) || defined(linux)
		interface(env_Linux) 	Linux;
	#endif

	#if defined(_WIN32) || defined(_WIN64)
		interface(env_Windows) 	Windows;
	#endif
    #endif
		interface(env_Devices) 	Devices;
		interface(env_Common) 	Common;
};

#undef package

#endif
