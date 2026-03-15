#pragma once
#define __ENV_GODOT_API__
#include "../pkg.h"
#include "../types.h"

#ifndef __ENV_GODOT_API_OBJECT__
#include "Class/pkg.h"
#include "Callable/pkg.h"

#define package gde_Object


Interface_Pkg(
/**
 * @name object_method_bind_call
 * @since 4.1
 *
 * Calls a method on an Object.
 *
 * @param p_method_bind A pointer to the MethodBind representing the method on the Object's class.
 * @param p_instance A pointer to the Object.
 * @param p_args A pointer to a C array of Variants representing the arguments.
 * @param p_arg_count The number of arguments.
 * @param r_ret A pointer to Variant which will receive the return value.
 * @param r_error A pointer to a gde_CallError struct that will receive error information.
 */
	void vfn(MethodBindCall)(
		gde_Object_Class_Method_BindPtr p_method_bind, 
		gde_Object_Ptr p_instance, 
		const gde_Type_Variant_ConstPtr* p_args, 
		gde_Int p_arg_count, 
		gde_Type_Variant_UninitPtr r_ret, 
		gde_CallError *r_error
	);

/**
 * @name object_method_bind_ptrcall
 * @since 4.1
 *
 * Calls a method on an Object (using a "ptrcall").
 *
 * @param p_method_bind A pointer to the MethodBind representing the method on the Object's class.
 * @param p_instance A pointer to the Object.
 * @param p_args A pointer to a C array representing the arguments.
 * @param r_ret A pointer to the Object that will receive the return value.
 */
	void vfn(MethodBindPtrcall)(
		gde_Object_Class_Method_BindPtr p_method_bind, 
		gde_Object_Ptr p_instance, 
		const gde_Type_Variant_ConstPtr* p_args, 
		gde_Type_Ptr r_ret
	);

/**
 * @name object_destroy
 * @since 4.1
 *
 * Destroys an Object.
 *
 * @param p_o A pointer to the Object.
 */
	void vfn(Destroy)(gde_Object_Ptr p_o);

/**
 * @name global_get_singleton
 * @since 4.1
 *
 * Gets a global singleton by name.
 *
 * @param p_name A pointer to a StringName with the singleton name.
 *
 * @return A pointer to the singleton Object.
 */
	gde_Object_Ptr vfn(GetSingleton)(gde_String_ConstNamePtr p_name);

/**
 * @name object_get_instance_binding
 * @since 4.1
 *
 * Gets a pointer representing an Object's instance binding.
 *
 * @param p_o A pointer to the Object.
 * @param p_token A token the library received by the gde_'s entry point function.
 * @param p_callbacks A pointer to a gde_InstanceBindingCallbacks struct.
 *
 * @return A pointer to the instance binding.
 */
	void *vfn(GetInstanceBinding)(
			gde_Object_Ptr 		p_o, 
			void*				p_token, 
			const pkg(BindingCallbacks)* 	p_callbacks);

/**
 * @name object_set_instance_binding
 * @since 4.1
 *
 * Sets an Object's instance binding.
 *
 * @param p_o A pointer to the Object.
 * @param p_token A token the library received by the gde_'s entry point function.
 * @param p_binding A pointer to the instance binding.
 * @param p_callbacks A pointer to a gde_InstanceBindingCallbacks struct.
 */
	void vfn(SetInstanceBinding)(
			gde_Object_Ptr 		p_o,
			void*				p_token,
			void*				p_binding,
			const pkg(BindingCallbacks)* 	p_callbacks
	);

/**
 * @name object_free_instance_binding
 * @since 4.2
 *
 * Free an Object's instance binding.
 *
 * @param p_o A pointer to the Object.
 * @param p_token A token the library received by the gde_'s entry point function.
 */
	void vfn(FreeInstanceBinding)(gde_Object_Ptr p_o, void *p_token);

/**
 * @name object_set_instance
 * @since 4.1
 *
 * Sets an extension class instance on a Object.
 *
 * `p_classname` should be a registered extension class and should extend the `p_o` Object's class.
 *
 * @param p_o A pointer to the Object.
 * @param p_classname A pointer to a StringName with the registered extension class's name.
 * @param p_instance A pointer to the extension class instance.
 */
	void vfn(SetInstance)(
			gde_Object_Ptr p_o, 
			gde_String_ConstNamePtr p_classname, 
			gde_Object_Class_InstancePtr p_instance
	);

/**
 * @name object_get_class_name
 * @since 4.1
 *
 * Gets the class name of an Object.
 *
 * If the gde_ wraps the Godot object in an abstraction specific to its class, this is the
 * function that should be used to determine which wrapper to use.
 *
 * @param p_object A pointer to the Object.
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param r_class_name A pointer to a String to receive the class name.
 *
 * @return true if successful in getting the class name; otherwise false.
 */
	gde_Bool vfn(GetClassName)(
			gde_Object_ConstPtr p_object, 
			gde_ClassLibraryPtr p_library, 
			gde_String_UninitNamePtr r_class_name
	);

/**
 * @name object_cast_to
 * @since 4.1
 *
 * Casts an Object to a different type.
 *
 * @param p_object A pointer to the Object.
 * @param p_class_tag A pointer uniquely identifying a built-in class in the ClassDB.
 *
 * @return Returns a pointer to the Object, or NULL if it can't be cast to the requested type.
 */
	gde_Object_Ptr vfn(CastTo)(	gde_Object_ConstPtr p_object, void *p_class_tag);

/**
 * @name object_get_instance_from_id
 * @since 4.1
 *
 * Gets an Object by its instance ID.
 *
 * @param p_instance_id The instance ID.
 *
 * @return A pointer to the Object.
 */
	gde_Object_Ptr vfn(GetInstanceFromId)(gde_Object_InstanceID p_instance_id);

/**
 * @name object_get_instance_id
 * @since 4.1
 *
 * Gets the instance ID from an Object.
 *
 * @param p_object A pointer to the Object.
 *
 * @return The instance ID.
 */
	gde_Object_InstanceID vfn(GetInstanceId)(gde_Object_ConstPtr p_object);

/**
 * @name object_has_script_method
 * @since 4.3
 *
 * Checks if this object has a script with the given method.
 *
 * @param p_object A pointer to the Object.
 * @param p_method A pointer to a StringName identifying the method.
 *
 * @return true if the object has a script and that script has a method with the given name. Returns false if the object has no script.
 */
	gde_Bool vfn(HasScriptMethod)(gde_Object_ConstPtr p_object, gde_String_ConstNamePtr p_method);

/**
 * @name object_call_script_method
 * @since 4.3
 *
 * Call the given script method on this object.
 *
 * @param p_object A pointer to the Object.
 * @param p_method A pointer to a StringName identifying the method.
 * @param p_args A pointer to a C array of Variant.
 * @param p_argument_count The number of arguments.
 * @param r_return A pointer a Variant which will be assigned the return value.
 * @param r_error A pointer the structure which will hold error information.
 */
	void vfn(CallScriptMethod)(
			gde_Object_Ptr p_object, 
			gde_String_ConstNamePtr p_method, 
			const gde_Type_Variant_ConstPtr *p_args, 
			gde_Int p_argument_count, 
			gde_Type_Variant_UninitPtr r_return, 
			gde_CallError *r_error
	);

/**
 * @name ref_get_object
 * @since 4.1
 *
 * Gets the Object from a reference.
 *
 * @param p_ref A pointer to the reference.
 *
 * @return A pointer to the Object from the reference or NULL.
 */
	gde_Object_Ptr vfn(RefGetObject)(gde_Object_ConstRefPtr p_ref);

/**
 * @name ref_set_object
 * @since 4.1
 *
 * Sets the Object referred to by a reference.
 *
 * @param p_ref A pointer to the reference.
 * @param p_object A pointer to the Object to refer to.
 */
	void vfn(RefSetObject)(gde_Object_RefPtr p_ref, gde_Object_Ptr p_object);
)

Interface(Loading,
	values(FuncNames, strc8,
		MethodBindCall,
		MethodBindPtrcall,
		Destroy,
		GetSingleton,
		GetInstanceBinding,
		SetInstanceBinding,
		FreeInstanceBinding,
		SetInstance,
		GetClassName,
		CastTo,
		GetInstanceFromId,
		GetInstanceId,
		HasScriptMethod,
		CallScriptMethod,
		RefGetObject,
		RefSetObject
	)

	errvt fn(load)(gde_InterfaceGetProcAddress getProcAddr);
)


#undef package
#endif 
