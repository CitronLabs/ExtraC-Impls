#pragma once
#include <Godot.pkg.h>

#define module godot, API, Class


moduleValues(MethodFlag,
	NORMAL 		as 1,				
	EDITOR		as 2,			 
	CONST           as 4,			
	VIRTUAL         as 8,			
	VARARG          as 16,			
	STATIC          as 32,
	DEFAULT         as mod(MethodFlag_NORMAL),

)

moduleValues(MethodArgMetadata,
	NONE,,
	INT_IS_INT8,,
	INT_IS_INT16,,
	INT_IS_INT32,,
	INT_IS_INT64,,
	INT_IS_UINT8,,
	INT_IS_UINT16,,
	INT_IS_UINT32,,
	INT_IS_UINT64,,
	REAL_IS_FLOAT,,
	REAL_IS_DOUBLE,,
	INT_IS_CHAR16,,
	INT_IS_CHAR32,,
)

moduleValuesDef(FuncNames,
	.ConstructObject		= "classdb_construct_object2",
	.GetMethodBind			= "classdb_get_method_bind",
	.GetClassTag			= "classdb_get_class_tag",
	.RegisterClass			= "classdb_register_extension_class5",
	.RegisterMethod			= "classdb_register_extension_class_method",
	.RegisterVirtualMethod		= "classdb_register_extension_class_virtual_method",
	.RegisterIntegerConstant	= "classdb_register_extension_class_integer_constant",
	.RegisterProperty		= "classdb_register_extension_class_property",
	.RegisterPropertyIndexed	= "classdb_register_extension_class_property_indexed",
	.RegisterPropertyGroup		= "classdb_register_extension_class_property_group",
	.RegisterPropertySubgroup	= "classdb_register_extension_class_property_subgroup",
	.RegisterSignal			= "classdb_register_extension_class_signal",
	.UnregisterClass		= "classdb_unregister_extension_class"
)

export(
SUBMODULE(), 
VALUES(MethodArgMetadata, MethodFlag, FuncNames),
	load
)


#undef module

