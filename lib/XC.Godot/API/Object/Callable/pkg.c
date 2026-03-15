#pragma once
#include <Godot.pkg.h>

#define module godot, API, Callable

moduleValuesDef(FuncNames,
	.CallableCustomCreate 		= "callable_custom_create2",
	.CallableCustomGetUserData 	= "callable_custom_get_userdata"
)

export(
SUBMODULE(), 
VALUES(FuncNames), 
	load
)

#undef module
