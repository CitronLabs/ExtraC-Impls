#pragma once
#include <Godot.pkg.h>

#include "Variant/pkg.c"
#include "PackedArray/pkg.c"

#define module godot, API, Type, Dictionary

moduleValuesDef(FuncNames,
	.OperatorIndex		= "dictionary_operator_index",
	.OperatorIndexConst	= "dictionary_operator_index_const",
	.SetTyped		= "dictionary_set_typed"
)


export(
SUBMODULE(), 
VALUES(FuncNames), 
	load
)

#undef module
#define module godot, API, Type

export(
SUBMODULE(Dictionary, PackedArray, Variant), 
VALUES(), 
	load
)

#undef module
