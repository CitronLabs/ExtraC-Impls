#pragma once
#include <Godot.pkg.h>

#define module godot, API, Object

moduleValuesDef(FuncNames,
	.MethodBindCall		= "object_method_bind_call",
	.MethodBindPtrcall	= "object_method_bind_ptrcall",
	.Destroy		= "object_destroy",
	.GetSingleton		= "global_get_singleton",
	.GetInstanceBinding	= "object_get_instance_binding",
	.SetInstanceBinding	= "object_set_instance_binding",
	.FreeInstanceBinding	= "object_free_instance_binding",
	.SetInstance		= "object_set_instance",
	.GetClassName		= "object_get_class_name",
	.CastTo			= "object_cast_to",
	.GetInstanceFromId	= "object_get_instance_from_id",
	.GetInstanceId		= "object_get_instance_id",
	.HasScriptMethod	= "object_has_script_method",
	.CallScriptMethod	= "object_call_script_method",
	.RefGetObject		= "ref_get_object",
	.RefSetObject           = "ref_set_object"
)

export(
SUBMODULE(), 
VALUES(FuncNames), 
	load
)

#undef module
