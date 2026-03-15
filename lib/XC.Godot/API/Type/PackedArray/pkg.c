#pragma once
#include <Godot.pkg.h>

#define module godot, API, Type, PackedArray

moduleValuesDef(FuncNames,
	.ByteIndex		= "packed_byte_array_operator_index",
	.ByteIndexConst		= "packed_byte_array_operator_index_const",
	.F32Index		= "packed_float32_array_operator_index",
	.F32IndexConst		= "packed_float32_array_operator_index_const",
	.F64Index		= "packed_float64_array_operator_index",
	.F64IndexConst		= "packed_float64_array_operator_index_const",
	.I32Index		= "packed_int32_array_operator_index",
	.I32IndexConst		= "packed_int32_array_operator_index_const",
	.I64Index		= "packed_int64_array_operator_index",
	.I64IndexConst		= "packed_int64_array_operator_index_const",
	.StringIndex		= "packed_string_array_operator_index",
	.StringIndexConst	= "packed_string_array_operator_index_const",
	.Vector2Index		= "packed_vector2_array_operator_index",
	.Vector2IndexConst	= "packed_vector2_array_operator_index_const",
	.Vector3Index		= "packed_vector3_array_operator_index",
	.Vector3IndexConst	= "packed_vector3_array_operator_index_const",
	.Vector4Index		= "packed_vector4_array_operator_index",
	.Vector4IndexConst	= "packed_vector4_array_operator_index_const",
	.ColorIndex		= "packed_color_array_operator_index",
	.ColorIndexConst	= "packed_color_array_operator_index_const",
	.Index			= "array_operator_index",
	.IndexConst		= "array_operator_index_const",
	.ArrayRef		= "array_ref",
	.ArraySetTyped		= "array_set_typed"
)

export(
SUBMODULE(), 
VALUES(FuncNames), 
	load
)

#undef module
