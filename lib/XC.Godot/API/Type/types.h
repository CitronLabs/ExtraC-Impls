#pragma once
#define __GODOT_API_TYPE__
#include "pkg.h"
#define package gde_Type

typefrom(pntr, 		Ptr);
typefrom(constpntr, 	ConstPtr);
typefrom(pntr, 		UninitPtr);

#undef package
