#pragma once
#define __GODOT_API_OBJECT_CALLABLE__
#include "pkg.h"
#define package gde_Object_Callable

type_fn(void,		Call,		void*, const gde_Type_Variant_ConstPtr*, gde_Int, gde_Type_Variant_Ptr, gde_CallError*);
type_fn(gde_Bool,	IsValid,	void*);
type_fn(void,		Free,		void*);

type_fn(u32,		Hash,		void*);
type_fn(gde_Bool,	Equal,		void*, void *);
type_fn(gde_Bool,	LessThan,	void*, void *);

type_fn(void,		ToString,	void*, gde_Bool*, gde_String_Ptr);

type_fn(gde_Int,	GetArgCount,	void*, gde_Bool*);

typefrom(u64, InstanceID);


type(CustomInfo,
	/* Only `call_func` and `token` are strictly required, however, `object_id` should be passed if its not a static method.
	 *
	 * `token` should point to an address that uniquely identifies the GDE_ (for example, the
	 * `GDE_ClassLibraryPtr` passed to the entry symbol function.
	 *
	 * `hash_func`, `equal_func`, and `less_than_func` are optional. If not provided both `call_func` and
	 * `callable_userdata` together are used as the identity of the callable for hashing and comparison purposes.
	 *
	 * The hash returned by `hash_func` is cached, `hash_func` will not be called more than once per callable.
	 *
	 * `is_valid_func` is necessary if the validity of the callable can change before destruction.
	 *
	 * `free_func` is necessary if `callable_userdata` needs to be cleaned up when the callable is freed.
	 */
	void *callable_userdata;
	void *token;

	gde_Object_InstanceID object_id;

	gde_Object_Callable_Call call_func;
	gde_Object_Callable_IsValid is_valid_func;
	gde_Object_Callable_Free free_func;

	gde_Object_Callable_Hash hash_func;
	gde_Object_Callable_Equal equal_func;
	gde_Object_Callable_LessThan less_than_func;

	gde_Object_Callable_ToString to_string_func;

	gde_Object_Callable_GetArgCount get_argument_count_func;
)

#undef package
