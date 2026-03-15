#pragma once
#define __GODOT_API_OBJECT__
#include "pkg.h"

#define package gde_Object

typefrom(pntr, 		Ptr);
typefrom(constpntr, 	ConstPtr);
typefrom(pntr, 		UninitPtr);
typefrom(pntr, 		RefPtr);
typefrom(constpntr, 	ConstRefPtr);



type_fn(pntr, 		BindingCreate,		pntr, pntr);
type_fn(void,   	BindingFree,		pntr, pntr, pntr);
type_fn(gde_Bool, BindingReference,	pntr, pntr, gde_Bool);

type(BindingCallbacks,
	gde_Object_BindingCreate		create_callback;
	gde_Object_BindingFree		free_callback;
	gde_Object_BindingReference	reference_callback;
)


#undef package
