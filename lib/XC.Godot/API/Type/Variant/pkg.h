#pragma once
#define __ENV_GODOT_API_TYPE__
#include "../pkg.h"
#include "../types.h"
#include "../../String/pkg.h"

#undef IN
#ifndef __ENV_GODOT_API_TYPE_VARIANT__
#include "types.h"

#define package gde_Type_Variant

Interface_Pkg(

	VarientTypes;
	VariantOp;
/**
 * @name variant_new_copy
 * @since 4.1
 *
 * Copies one Variant into a another.
 *
 * @param r_dest A pointer to the destination Variant.
 * @param p_src A pointer to the source Variant.
 */
	void vfn(NewCopy)(pkg(UninitPtr) r_dest, pkg(ConstPtr) p_src);

/**
 * @name variant_new_nil
 * @since 4.1
 *
 * Creates a new Variant containing nil.
 *
 * @param r_dest A pointer to the destination Variant.
 */
	void vfn(NewNil)(pkg(UninitPtr) r_dest);

/**
 * @name variant_destroy
 * @since 4.1
 *
 * Destroys a Variant.
 *
 * @param p_self A pointer to the Variant to destroy.
 */
	void vfn(Destroy)(pkg(Ptr) p_self);

/**
 * @name variant_call
 * @since 4.1
 *
 * Calls a method on a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param p_method A pointer to a StringName identifying the method.
 * @param p_args A pointer to a C array of Variant.
 * @param p_argument_count The number of arguments.
 * @param r_return A pointer a Variant which will be assigned the return value.
 * @param r_error A pointer the structure which will hold error information.
 *
 * @see Variant::callp()
 */
	void vfn(Call)(
       		pkg(Ptr) 		 	 p_self, 
       		gde_String_ConstNamePtr 	 p_method, 
       		const pkg(ConstPtr)* 		 p_args, 
       		gde_Int 			 p_argument_count, 
       		pkg(UninitPtr) 	 		 r_return, 
       		gde_CallError* 		 r_error
	);

/**
 * @name variant_call_static
 * @since 4.1
 *
 * Calls a static method on a Variant.
 *
 * @param p_type The variant type.
 * @param p_method A pointer to a StringName identifying the method.
 * @param p_args A pointer to a C array of Variant.
 * @param p_argument_count The number of arguments.
 * @param r_return A pointer a Variant which will be assigned the return value.
 * @param r_error A pointer the structure which will be updated with error information.
 *
 * @see Variant::call_static()
 */
	void vfn(CallStatic)(
       		gde_Type_Variant_Type 	 p_type,
       		gde_String_ConstNamePtr 	 p_method, 
       		gde_Type_Variant_ConstPtr* p_args, 
       		gde_Int 			 p_argument_count, 
       		gde_Type_Variant_UninitPtr r_return, 
       		gde_CallError*		 r_error
       );

/**
 * @name variant_evaluate
 * @since 4.1
 *
 * Evaluate an operator on two Variants.
 *
 * @param p_op The operator to evaluate.
 * @param p_a The first Variant.
 * @param p_b The second Variant.
 * @param r_return A pointer a Variant which will be assigned the return value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 *
 * @see Variant::evaluate()
 */
	void vfn(Evaluate)(
       		pkg(Op) 	   p_op, 
       		pkg(ConstPtr)  p_a, 
       		pkg(ConstPtr)  p_b, 
       		pkg(UninitPtr) r_return, 
       		gde_Bool*		   r_valid);

/**
 * @name variant_set
 * @since 4.1
 *
 * Sets a key on a Variant to a value.
 *
 * @param p_self A pointer to the Variant.
 * @param p_key A pointer to a Variant representing the key.
 * @param p_value A pointer to a Variant representing the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 *
 * @see Variant::set()
 */
	void vfn(Set)(
       		pkg(Ptr) 	  p_self, 
       		pkg(ConstPtr) p_key, 
       		pkg(ConstPtr) p_value, 
       		gde_Bool*		  r_valid
       );

/**
 * @name variant_set_named
 * @since 4.1
 *
 * Sets a named key on a Variant to a value.
 *
 * @param p_self A pointer to the Variant.
 * @param p_key A pointer to a StringName representing the key.
 * @param p_value A pointer to a Variant representing the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 *
 * @see Variant::set_named()
 */
	void vfn(SetNamed)(
       		pkg(Ptr) p_self, 
       		gde_String_ConstNamePtr p_key, 
       		pkg(ConstPtr) p_value, 
       		gde_Bool *r_valid
       );

/**
 * @name variant_set_keyed
 * @since 4.1
 *
 * Sets a keyed property on a Variant to a value.
 *
 * @param p_self A pointer to the Variant.
 * @param p_key A pointer to a Variant representing the key.
 * @param p_value A pointer to a Variant representing the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 *
 * @see Variant::set_keyed()
 */
	void vfn(SetKeyed)(
       		pkg(Ptr) p_self, 
       		pkg(ConstPtr) p_key, 
       		pkg(ConstPtr) p_value, 
       		gde_Bool *r_valid
       );

/**
 * @name variant_set_indexed
 * @since 4.1
 *
 * Sets an index on a Variant to a value.
 *
 * @param p_self A pointer to the Variant.
 * @param p_index The index.
 * @param p_value A pointer to a Variant representing the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 * @param r_oob A pointer to a boolean which will be set to true if the index is out of bounds.
 */
	void vfn(SetIndexed)(
       		pkg(Ptr) p_self, 
       		gde_Int p_index, 
       		pkg(ConstPtr) p_value, 
       		gde_Bool *r_valid, 
       		gde_Bool *r_oob
       );

/**
 * @name variant_get
 * @since 4.1
 *
 * Gets the value of a key from a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param p_key A pointer to a Variant representing the key.
 * @param r_ret A pointer to a Variant which will be assigned the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 */
	void vfn(Get)(
       		pkg(ConstPtr) p_self, 
       		pkg(ConstPtr) p_key, 
       		pkg(UninitPtr) r_ret, 
       		gde_Bool *r_valid
       );

/**
 * @name variant_get_named
 * @since 4.1
 *
 * Gets the value of a named key from a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param p_key A pointer to a StringName representing the key.
 * @param r_ret A pointer to a Variant which will be assigned the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 */
	void vfn(GetNamed)(
       		pkg(ConstPtr) 	p_self, 
       		gde_String_ConstNamePtr 	p_key, 
       		pkg(UninitPtr) 	r_ret, 
       		gde_Bool*			r_valid
       );

/**
 * @name variant_get_keyed
 * @since 4.1
 *
 * Gets the value of a keyed property from a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param p_key A pointer to a Variant representing the key.
 * @param r_ret A pointer to a Variant which will be assigned the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 */
	void vfn(GetKeyed)(
       		pkg(ConstPtr) 	p_self, 
       		pkg(ConstPtr) 	p_key, 
       		pkg(UninitPtr) 	r_ret, 
       		gde_Bool*			r_valid
       );

/**
 * @name variant_get_indexed
 * @since 4.1
 *
 * Gets the value of an index from a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param p_index The index.
 * @param r_ret A pointer to a Variant which will be assigned the value.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 * @param r_oob A pointer to a boolean which will be set to true if the index is out of bounds.
 */
	void vfn(GetIndexed)(pkg(ConstPtr) p_self, gde_Int p_index, pkg(UninitPtr) r_ret, gde_Bool *r_valid, gde_Bool *r_oob);

/**
 * @name variant_iter_init
 * @since 4.1
 *
 * Initializes an iterator over a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param r_iter A pointer to a Variant which will be assigned the iterator.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 *
 * @return true if the operation is valid; otherwise false.
 *
 * @see Variant::iter_init()
 */
	gde_Bool vfn(IterInit)(pkg(ConstPtr) p_self, pkg(UninitPtr) r_iter, gde_Bool *r_valid);

/**
 * @name variant_iter_next
 * @since 4.1
 *
 * Gets the next value for an iterator over a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param r_iter A pointer to a Variant which will be assigned the iterator.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 *
 * @return true if the operation is valid; otherwise false.
 *
 * @see Variant::iter_next()
 */
	gde_Bool vfn(IterNext)(pkg(ConstPtr) p_self, pkg(Ptr) r_iter, gde_Bool *r_valid);

/**
 * @name variant_iter_get
 * @since 4.1
 *
 * Gets the next value for an iterator over a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param r_iter A pointer to a Variant which will be assigned the iterator.
 * @param r_ret A pointer to a Variant which will be assigned false if the operation is invalid.
 * @param r_valid A pointer to a boolean which will be set to false if the operation is invalid.
 *
 * @see Variant::iter_get()
 */
	void vfn(IterGet)(pkg(ConstPtr) p_self, pkg(Ptr) r_iter, pkg(UninitPtr) r_ret, gde_Bool *r_valid);

/**
 * @name variant_hash
 * @since 4.1
 *
 * Gets the hash of a Variant.
 *
 * @param p_self A pointer to the Variant.
 *
 * @return The hash value.
 *
 * @see Variant::hash()
 */
	gde_Int vfn(Hash)(pkg(ConstPtr) p_self);

/**
 * @name variant_recursive_hash
 * @since 4.1
 *
 * Gets the recursive hash of a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param p_recursion_count The number of recursive loops so far.
 *
 * @return The hash value.
 *
 * @see Variant::recursive_hash()
 */
	gde_Int vfn(RecursiveHash)(pkg(ConstPtr) p_self, gde_Int p_recursion_count);

/**
 * @name variant_hash_compare
 * @since 4.1
 *
 * Compares two Variants by their hash.
 *
 * @param p_self A pointer to the Variant.
 * @param p_other A pointer to the other Variant to compare it to.
 *
 * @return The hash value.
 *
 * @see Variant::hash_compare()
 */
	gde_Bool vfn(HashCompare)(pkg(ConstPtr) p_self, pkg(ConstPtr) p_other);

/**
 * @name variant_booleanize
 * @since 4.1
 *
 * Converts a Variant to a boolean.
 *
 * @param p_self A pointer to the Variant.
 *
 * @return The boolean value of the Variant.
 */
	gde_Bool vfn(Booleanize)(pkg(ConstPtr) p_self);

/**
 * @name variant_duplicate
 * @since 4.1
 *
 * Duplicates a Variant.
 *
 * @param p_self A pointer to the Variant.
 * @param r_ret A pointer to a Variant to store the duplicated value.
 * @param p_deep Whether or not to duplicate deeply (when supported by the Variant type).
 */
	void vfn(Duplicate)(pkg(ConstPtr) p_self, pkg(Ptr) r_ret, gde_Bool p_deep);

/**
 * @name variant_stringify
 * @since 4.1
 *
 * Converts a Variant to a string.
 *
 * @param p_self A pointer to the Variant.
 * @param r_ret A pointer to a String to store the resulting value.
 */
	void vfn(Stringify)(pkg(ConstPtr) p_self, gde_String_Ptr r_ret);

/**
 * @name variant_get_type
 * @since 4.1
 *
 * Gets the type of a Variant.
 *
 * @param p_self A pointer to the Variant.
 *
 * @return The variant type.
 */
	pkg(Type) vfn(GetType)(pkg(ConstPtr) p_self);

/**
 * @name variant_has_method
 * @since 4.1
 *
 * Checks if a Variant has the given method.
 *
 * @param p_self A pointer to the Variant.
 * @param p_method A pointer to a StringName with the method name.
 *
 * @return true if the variant has the given method; otherwise false.
 */
	gde_Bool vfn(HasMethod)(pkg(ConstPtr) p_self, gde_String_ConstNamePtr p_method);

/**
 * @name variant_has_member
 * @since 4.1
 *
 * Checks if a type of Variant has the given member.
 *
 * @param p_type The Variant type.
 * @param p_member A pointer to a StringName with the member name.
 *
 * @return true if the variant has the given method; otherwise false.
 */
	gde_Bool vfn(HasMember)(pkg(Type) p_type, gde_String_ConstNamePtr p_member);

/**
 * @name variant_has_key
 * @since 4.1
 *
 * Checks if a Variant has a key.
 *
 * @param p_self A pointer to the Variant.
 * @param p_key A pointer to a Variant representing the key.
 * @param r_valid A pointer to a boolean which will be set to false if the key doesn't exist.
 *
 * @return true if the key exists; otherwise false.
 */
	gde_Bool vfn(HasKey)(pkg(ConstPtr) p_self, pkg(ConstPtr) p_key, gde_Bool *r_valid);

/**
 * @name variant_get_object_instance_id
 * @since 4.4
 *
 * Gets the object instance ID from a variant of type gde_VARIANT_TYPE_OBJECT.
 *
 * If the variant isn't of type gde_VARIANT_TYPE_OBJECT, then zero will be returned.
 * The instance ID will be returned even if the object is no longer valid - use `object_get_instance_by_id()` to check if the object is still valid.
 *
 * @param p_self A pointer to the Variant.
 *
 * @return The instance ID for the contained object.
 */
	gde_Object_InstanceID vfn(GetObjectInstanceId)(pkg(ConstPtr) p_self);

/**
 * @name variant_get_type_name
 * @since 4.1
 *
 * Gets the name of a Variant type.
 *
 * @param p_type The Variant type.
 * @param r_name A pointer to a String to store the Variant type name.
 */
	void vfn(GetTypeName)(pkg(Type) p_type, gde_String_UninitPtr r_name);

/**
 * @name variant_can_convert
 * @since 4.1
 *
 * Checks if Variants can be converted from one type to another.
 *
 * @param p_from The Variant type to convert from.
 * @param p_to The Variant type to convert to.
 *
 * @return true if the conversion is possible; otherwise false.
 */
	gde_Bool vfn(CanConvert)(pkg(Type) p_from, pkg(Type) p_to);

/**
 * @name variant_can_convert_strict
 * @since 4.1
 *
 * Checks if Variant can be converted from one type to another using stricter rules.
 *
 * @param p_from The Variant type to convert from.
 * @param p_to The Variant type to convert to.
 *
 * @return true if the conversion is possible; otherwise false.
 */
	gde_Bool vfn(CanConvertStrict)(pkg(Type) p_from, pkg(Type) p_to);

/**
 * @name get_variant_from_type_constructor
 * @since 4.1
 *
 * Gets a pointer to a function that can create a Variant of the given type from a raw value.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function that can create a Variant of the given type from a raw value.
 */
	pkg(FromTypeConstructor) vfn(GetVariantFromTypeConstructor)(pkg(Type) p_type);

/**
 * @name get_variant_to_type_constructor
 * @since 4.1
 *
 * Gets a pointer to a function that can get the raw value from a Variant of the given type.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function that can get the raw value from a Variant of the given type.
 */
	pkg(ConstructorToType) vfn(GetVariantToTypeConstructor)(pkg(Type) p_type);

/**
 * @name variant_get_ptr_internal_getter
 * @since 4.4
 *
 * Provides a function pointer for retrieving a pointer to a variant's internal value.
 * Access to a variant's internal value can be used to modify it in-place, or to retrieve its value without the overhead of variant conversion functions.
 * It is recommended to cache the getter for all variant types in a function table to avoid retrieval overhead upon use.
 *
 * @note Each function assumes the variant's type has already been determined and matches the function.
 * Invoking the function with a variant of a mismatched type has undefined behavior, and may lead to a segmentation fault.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a type-specific function that returns a pointer to the internal value of a variant. Check the implementation of this function (gdextension_variant_get_ptr_internal_getter) for pointee type info of each variant type.
 */
	pkg(GetInternalPtr) vfn(GetVariantGetInternalPtrFunc)(pkg(Type) p_type);

/**
 * @name variant_construct
 * @since 4.1
 *
 * Constructs a Variant of the given type, using the first constructor that matches the given arguments.
 *
 * @param p_type The Variant type.
 * @param r_base A pointer to a Variant to store the constructed value.
 * @param p_args A pointer to a C array of Variant pointers representing the arguments for the constructor.
 * @param p_argument_count The number of arguments to pass to the constructor.
 * @param r_error A pointer the structure which will be updated with error information.
 */
	void vfn(Construct)(pkg(Type) p_type, pkg(UninitPtr) r_base, const pkg(ConstPtr) *p_args, i32 p_argument_count, gde_CallError *r_error);

/**
 * @name variant_get_ptr_operator_evaluator
 * @since 4.1
 *
 * Gets a pointer to a function that can evaluate the given Variant operator on the given Variant types.
 *
 * @param p_operator The variant operator.
 * @param p_type_a The type of the first Variant.
 * @param p_type_b The type of the second Variant.
 *
 * @return A pointer to a function that can evaluate the given Variant operator on the given Variant types.
 */
	pkg(Ptr_OpEval) vfn(GetPtrOperatorEvaluator)(gde_Type_Variant_Op p_operator, pkg(Type) p_type_a, pkg(Type) p_type_b);

/**
 * @name variant_get_ptr_builtin_method
 * @since 4.1
 *
 * Gets a pointer to a function that can call a builtin method on a type of Variant.
 *
 * @param p_type The Variant type.
 * @param p_method A pointer to a StringName with the method name.
 * @param p_hash A hash representing the method signature.
 *
 * @return A pointer to a function that can call a builtin method on a type of Variant.
 */
	pkg(Ptr_BuiltInMethod) vfn(GetPtrBuiltinMethod)(pkg(Type) p_type, gde_String_ConstNamePtr p_method, gde_Int p_hash);

/**
 * @name variant_get_ptr_constructor
 * @since 4.1
 *
 * Gets a pointer to a function that can call one of the constructors for a type of Variant.
 *
 * @param p_type The Variant type.
 * @param p_constructor The index of the constructor.
 *
 * @return A pointer to a function that can call one of the constructors for a type of Variant.
 */
	pkg(Ptr_Constructor) vfn(GetPtrConstructor)(pkg(Type) p_type, i32 p_constructor);

/**
 * @name variant_get_ptr_destructor
 * @since 4.1
 *
 * Gets a pointer to a function than can call the destructor for a type of Variant.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function than can call the destructor for a type of Variant.
 */
	pkg(Ptr_Destructor) vfn(GetPtrDestructor)(pkg(Type) p_type);


/**
 * @name variant_get_ptr_setter
 * @since 4.1
 *
 * Gets a pointer to a function that can call a member's setter on the given Variant type.
 *
 * @param p_type The Variant type.
 * @param p_member A pointer to a StringName with the member name.
 *
 * @return A pointer to a function that can call a member's setter on the given Variant type.
 */
	pkg(Ptr_Setter) vfn(GetPtrSetter)(pkg(Type) p_type, gde_String_ConstNamePtr p_member);

/**
 * @name variant_get_ptr_getter
 * @since 4.1
 *
 * Gets a pointer to a function that can call a member's getter on the given Variant type.
 *
 * @param p_type The Variant type.
 * @param p_member A pointer to a StringName with the member name.
 *
 * @return A pointer to a function that can call a member's getter on the given Variant type.
 */
	pkg(Ptr_Getter) vfn(GetPtrGetter)(pkg(Type) p_type, gde_String_ConstNamePtr p_member);

/**
 * @name variant_get_ptr_indexed_setter
 * @since 4.1
 *
 * Gets a pointer to a function that can set an index on the given Variant type.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function that can set an index on the given Variant type.
 */
	pkg(Ptr_IndexedSetter) vfn(GetPtrIndexedSetter)(pkg(Type) p_type);

/**
 * @name variant_get_ptr_indexed_getter
 * @since 4.1
 *
 * Gets a pointer to a function that can get an index on the given Variant type.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function that can get an index on the given Variant type.
 */
	pkg(Ptr_IndexedGetter) vfn(GetPtrIndexedGetter)(pkg(Type) p_type);

/**
 * @name variant_get_ptr_keyed_setter
 * @since 4.1
 *
 * Gets a pointer to a function that can set a key on the given Variant type.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function that can set a key on the given Variant type.
 */
	pkg(Ptr_KeyedSetter) vfn(GetPtrKeyedSetter)(pkg(Type) p_type);

/**
 * @name variant_get_ptr_keyed_getter
 * @since 4.1
 *
 * Gets a pointer to a function that can get a key on the given Variant type.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function that can get a key on the given Variant type.
 */
	pkg(Ptr_KeyedGetter) vfn(GetPtrKeyedGetter)(pkg(Type) p_type);

/**
 * @name variant_get_ptr_keyed_checker
 * @since 4.1
 *
 * Gets a pointer to a function that can check a key on the given Variant type.
 *
 * @param p_type The Variant type.
 *
 * @return A pointer to a function that can check a key on the given Variant type.
 */
	pkg(Ptr_KeyedChecker) vfn(GetPtrKeyedChecker)(pkg(Type) p_type);

/**
 * @name variant_get_constant_value
 * @since 4.1
 *
 * Gets the value of a constant from the given Variant type.
 *
 * @param p_type The Variant type.
 * @param p_constant A pointer to a StringName with the constant name.
 * @param r_ret A pointer to a Variant to store the value.
 */
	void vfn(GetConstantValue)(pkg(Type) p_type, gde_String_ConstNamePtr p_constant, pkg(UninitPtr) r_ret);

/**
 * @name variant_get_ptr_utility_function
 * @since 4.1
 *
 * Gets a pointer to a function that can call a Variant utility function.
 *
 * @param p_function A pointer to a StringName with the function name.
 * @param p_hash A hash representing the function signature.
 *
 * @return A pointer to a function that can call a Variant utility function.
 */
	pkg(Ptr_UtilityFunction) vfn(GetPtrUtilityFunction)(gde_String_ConstNamePtr p_function, gde_Int p_hash);
)

#undef package
#undef VariantOp
#undef VarientTypes
#endif
