#pragma once
#include <Godot.pkg.h>

#define module godot, API, Script

moduleValuesDef(FuncNames,
	.ScriptInstanceCreate		= "script_instance_create3",
	.PlaceHolderInstanceCreate	= "placeholder_script_instance_create",
	.PlaceHolderInstanceUpdate	= "placeholder_script_instance_update",
	.ObjectGetScriptInstance	= "object_get_script_instance",
	.ObjectSetScriptInstance	= "object_set_script_instance"
)


export(
SUBMODULE(), 
VALUES(FuncNames), 
	load
)

#undef module
