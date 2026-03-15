#pragma once
#define __GODOT_API_STRING__
#include "pkg.h"

#define package gde_String

typefrom(pntr, 		NamePtr);
typefrom(constpntr, 	ConstNamePtr);
typefrom(pntr, 		UninitNamePtr);
typefrom(pntr, 		Ptr);
typefrom(constpntr, 	ConstPtr);
typefrom(pntr, 		UninitPtr);


#undef package
