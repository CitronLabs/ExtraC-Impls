#pragma once
#define __ENV_GODOT_API_OBJECT__
#include "../pkg.h"
#include "../types.h"
#include "../../Type/pkg.h"


#ifndef __ENV_GODOT_API_OBJECT_CALLABLE__
#include "types.h"

#define package gde_Object_Callable

Interface_Pkg(
/**
 * @name callable_custom_create2
 * @since 4.3
 *
 * Creates a custom Callable object from a function pointer.
 *
 * Provided struct can be safely freed once the function returns.
 *
 * @param r_callable A pointer that will receive the new Callable.
 * @param p_callable_custom_info The info required to construct a Callable.
 */
	void vfn(CallableCustomCreate)(gde_Type_UninitPtr r_callable, pkg(CustomInfo)* p_callable_custom_info);

/**
 * @name callable_custom_get_userdata
 * @since 4.2
 *
 * Retrieves the userdata pointer from a custom Callable.
 *
 * If the Callable is not a custom Callable or the token does not match the one provided to callable_custom_create() via gde_CallableCustomInfo then NULL will be returned.
 *
 * @param p_callable A pointer to a Callable.
 * @param p_token A pointer to an address that uniquely identifies the gde_.
 *
 * @return The userdata pointer given when creating this custom Callable.
 */
	void *vfn(CallableCustomGetUserData)(gde_Type_ConstPtr p_callable, void *p_token);
)

#undef package
#endif
