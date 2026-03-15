#pragma once
#define __ENV_GODOT_API__
#include "../pkg.h"
#include "../types.h"

#ifndef __ENV_GODOT_API_TYPE__
#include "Variant/pkg.h"
#include "PackedArray/pkg.h"
#include "types.h"

#define package gde_Type

Interface(Dictionary,
/**
 * @name dictionary_operator_index
 * @since 4.1
 *
 * Gets a pointer to a Variant in a Dictionary with the given key.
 *
 * @param p_self A pointer to a Dictionary object.
 * @param p_key A pointer to a Variant representing the key.
 *
 * @return A pointer to a Variant representing the value at the given key.
 */
	gde_Type_Variant_Ptr vfn(OperatorIndex)(gde_Type_ConstPtr p_self, gde_Type_Variant_ConstPtr p_key);

/**
 * @name dictionary_operator_index_const
 * @since 4.1
 *
 * Gets a const pointer to a Variant in a Dictionary with the given key.
 *
 * @param p_self A const pointer to a Dictionary object.
 * @param p_key A pointer to a Variant representing the key.
 *
 * @return A const pointer to a Variant representing the value at the given key.
 */
	gde_Type_Variant_Ptr vfn(OperatorIndexConst)(gde_Type_ConstPtr p_self, gde_Type_Variant_ConstPtr p_key);

/**
 * @name dictionary_set_typed
 * @since 4.4
 *
 * Makes a Dictionary into a typed Dictionary.
 *
 * @param p_self A pointer to the Dictionary.
 * @param p_key_type The type of Variant the Dictionary key will store.
 * @param p_key_class_name A pointer to a StringName with the name of the object (if p_key_type is gde_VARIANT_TYPE_OBJECT).
 * @param p_key_script A pointer to a Script object (if p_key_type is gde_VARIANT_TYPE_OBJECT and the base class is extended by a script).
 * @param p_value_type The type of Variant the Dictionary value will store.
 * @param p_value_class_name A pointer to a StringName with the name of the object (if p_value_type is gde_VARIANT_TYPE_OBJECT).
 * @param p_value_script A pointer to a Script object (if p_value_type is gde_VARIANT_TYPE_OBJECT and the base class is extended by a script).
 */
	void vfn(SetTyped)(
			gde_Type_Ptr 			p_self, 
			gde_Type_Variant_Type 		p_key_type, 
			gde_String_ConstNamePtr 		p_key_class_name, 
			gde_Type_Variant_ConstPtr 	p_key_script, 
			gde_Type_Variant_Type 		p_value_type, 
			gde_String_ConstNamePtr 		p_value_class_name, 
			gde_Type_Variant_ConstPtr 	p_value_script
	);
)

Interface_Pkg(
	vtable(pkg(Variant)) 	 Variant;
	vtable(pkg(Dictionary))  Dictionary;
	vtable(pkg(PackedArray)) PackedArray;
)

#undef package
#endif
