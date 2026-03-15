#pragma once
#define __ENV_GODOT_API_OBJECT__
#include "../pkg.h"
#include "../types.h"
#include "../../String/pkg.h"
#include "../../Type/pkg.h"

#undef RegisterClass
#undef UnregisterClass
#undef CONST
#ifndef __ENV_GODOT_API_OBJECT_CLASS__
#include "types.h"

#define package gde_Object_Class

Interface_Pkg(
	values(MethodFlag, pkg(Method_Flag),	
		NORMAL,	
		EDITOR, 
		CONST,
		VIRTUAL,
		VARARG,
		STATIC,
		DEFAULT
	)

	values(MethodArgMetadata, pkg(Method_ArgMetadata),
		NONE,
		INT_IS_INT8,
		INT_IS_INT16,
		INT_IS_INT32,
		INT_IS_INT64,
		INT_IS_UINT8,
		INT_IS_UINT16,
		INT_IS_UINT32,
		INT_IS_UINT64,
		REAL_IS_FLOAT,
		REAL_IS_DOUBLE,
		INT_IS_CHAR16,
		INT_IS_CHAR32
	)
/**
 * @name classdb_construct_object2
 * @since 4.4
 *
 * Constructs an Object of the requested class.
 *
 * The passed class must be a built-in godot class, or an already-registered extension class. In both cases, object_set_instance() should be called to fully initialize the object.
 *
 * "NOTIFICATION_POSTINITIALIZE" must be sent after construction.
 *
 * @param p_classname A pointer to a StringName with the class name.
 *
 * @return A pointer to the newly created Object.
 */
	gde_Object_Ptr vfn(ConstructObject)(gde_String_ConstNamePtr p_classname);

/**
 * @name classdb_get_method_bind
 * @since 4.1
 *
 * Gets a pointer to the MethodBind in ClassDB for the given class, method and hash.
 *
 * @param p_classname A pointer to a StringName with the class name.
 * @param p_methodname A pointer to a StringName with the method name.
 * @param p_hash A hash representing the function signature.
 *
 * @return A pointer to the MethodBind from ClassDB.
 */
	pkg(Method_BindPtr) vfn(GetMethodBind)(gde_String_ConstNamePtr p_classname, gde_String_ConstNamePtr p_methodname, gde_Int p_hash);

/**
 * @name classdb_get_class_tag
 * @since 4.1
 *
 * Gets a pointer uniquely identifying the given built-in class in the ClassDB.
 *
 * @param p_classname A pointer to a StringName with the class name.
 *
 * @return A pointer uniquely identifying the built-in class in the ClassDB.
 */
	void *vfn(GetClassTag)(gde_String_ConstNamePtr p_classname);

/* INTERFACE: ClassDB Extension */

/**
 * @name classdb_register_extension_class5
 * @since 4.5
 *
 * Registers an extension class in the ClassDB.
 *
 * Provided struct can be safely freed once the function returns.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_parent_class_name A pointer to a StringName with the parent class name.
 * @param p_extension_funcs A pointer to a gde_ClassCreationInfo5 struct.
 */
	void vfn(RegisterClass)(
			gde_ClassLibraryPtr 		   p_library, 
			gde_String_ConstNamePtr 		   p_class_name, 
			gde_String_ConstNamePtr 		   p_parent_class_name, 
			const gde_Object_Class_CreationInfo* p_extension_funcs);

/**
 * @name classdb_register_extension_class_method
 * @since 4.1
 *
 * Registers a method on an extension class in the ClassDB.
 *
 * Provided struct can be safely freed once the function returns.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_method_info A pointer to a gde_ClassMethodInfo struct.
 */
	void vfn(RegisterMethod)(
			gde_ClassLibraryPtr 		  p_library,
			gde_String_ConstNamePtr 		  p_class_name,
			const gde_Object_Class_Method_Info* p_method_info
	);

/**
 * @name classdb_register_extension_class_virtual_method
 * @since 4.3
 *
 * Registers a virtual method on an extension class in ClassDB, that can be implemented by scripts or other extensions.
 *
 * Provided struct can be safely freed once the function returns.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_method_info A pointer to a gde_ClassMethodInfo struct.
 */
	void vfn(RegisterVirtualMethod)(
			gde_ClassLibraryPtr 			 p_library, 
			gde_String_ConstNamePtr 			 p_class_name, 
			const gde_Object_Class_Method_VirtualInfo* p_method_info
	);

/**
 * @name classdb_register_extension_class_integer_constant
 * @since 4.1
 *
 * Registers an integer constant on an extension class in the ClassDB.
 *
 * Note about registering bitfield values (if p_is_bitfield is true): even though p_constant_value is signed, language bindings are
 * advised to treat bitfields as uint64_t, since this is generally clearer and can prevent mistakes like using -1 for setting all bits.
 * Language APIs should thus provide an abstraction that registers bitfields (uint64_t) separately from regular constants (int64_t).
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_enum_name A pointer to a StringName with the enum name.
 * @param p_constant_name A pointer to a StringName with the constant name.
 * @param p_constant_value The constant value.
 * @param p_is_bitfield Whether or not this constant is part of a bitfield.
 */
	void vfn(RegisterIntegerConstant)(
			gde_ClassLibraryPtr p_library,
			gde_String_ConstNamePtr p_class_name,
			gde_String_ConstNamePtr p_enum_name,
			gde_String_ConstNamePtr p_constant_name,
			gde_Int p_constant_value,
			gde_Bool p_is_bitfield
	);

/**
 * @name classdb_register_extension_class_property
 * @since 4.1
 *
 * Registers a property on an extension class in the ClassDB.
 *
 * Provided struct can be safely freed once the function returns.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_info A pointer to a gde_PropertyInfo struct.
 * @param p_setter A pointer to a StringName with the name of the setter method.
 * @param p_getter A pointer to a StringName with the name of the getter method.
 */
	void vfn(RegisterProperty)(
			gde_ClassLibraryPtr 	p_library, 
			gde_String_ConstNamePtr 	p_class_name, 
			const pkg(PropertyInfo)*	p_info, 
			gde_String_ConstNamePtr 	p_setter, 
			gde_String_ConstNamePtr 	p_getter
	);

/**
 * @name classdb_register_extension_class_property_indexed
 * @since 4.2
 *
 * Registers an indexed property on an extension class in the ClassDB.
 *
 * Provided struct can be safely freed once the function returns.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_info A pointer to a gde_PropertyInfo struct.
 * @param p_setter A pointer to a StringName with the name of the setter method.
 * @param p_getter A pointer to a StringName with the name of the getter method.
 * @param p_index The index to pass as the first argument to the getter and setter methods.
 */
	void vfn(RegisterPropertyIndexed)(
			gde_ClassLibraryPtr 	p_library, 
			gde_String_ConstNamePtr 	p_class_name, 
			const pkg(PropertyInfo)* 	p_info, 
			gde_String_ConstNamePtr 	p_setter, 
			gde_String_ConstNamePtr 	p_getter, 
			gde_Int 			p_index
	);

/**
 * @name classdb_register_extension_class_property_group
 * @since 4.1
 *
 * Registers a property group on an extension class in the ClassDB.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_group_name A pointer to a String with the group name.
 * @param p_prefix A pointer to a String with the prefix used by properties in this group.
 */
	void vfn(RegisterPropertyGroup)(
			gde_ClassLibraryPtr 	p_library, 
			gde_String_ConstNamePtr 	p_class_name,
			gde_String_ConstPtr 	p_group_name, 
			gde_String_ConstPtr 	p_prefix
	);

/**
 * @name classdb_register_extension_class_property_subgroup
 * @since 4.1
 *
 * Registers a property subgroup on an extension class in the ClassDB.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_subgroup_name A pointer to a String with the subgroup name.
 * @param p_prefix A pointer to a String with the prefix used by properties in this subgroup.
 */
	void vfn(RegisterPropertySubgroup)(
			gde_ClassLibraryPtr 	p_library, 
			gde_String_ConstNamePtr 	p_class_name, 
			gde_String_ConstPtr 	p_subgroup_name, 
			gde_String_ConstPtr 	p_prefix
	);

/**
 * @name classdb_register_extension_class_signal
 * @since 4.1
 *
 * Registers a signal on an extension class in the ClassDB.
 *
 * Provided structs can be safely freed once the function returns.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 * @param p_signal_name A pointer to a StringName with the signal name.
 * @param p_argument_info A pointer to a gde_PropertyInfo struct.
 * @param p_argument_count The number of arguments the signal receives.
 */
	void vfn(RegisterSignal)(
			gde_ClassLibraryPtr 	p_library, 
			gde_String_ConstNamePtr 	p_class_name, 
			gde_String_ConstNamePtr 	p_signal_name, 
			const pkg(PropertyInfo)* 	p_argument_info, 
			gde_Int 			p_argument_count
	);

/**
 * @name classdb_unregister_extension_class
 * @since 4.1
 *
 * Unregisters an extension class in the ClassDB.
 *
 * Unregistering a parent class before a class that inherits it will result in failure. Inheritors must be unregistered first.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_class_name A pointer to a StringName with the class name.
 */
	void vfn(UnregisterClass)(
			gde_ClassLibraryPtr p_library, 
			gde_String_ConstNamePtr p_class_name
	);
)

#undef package
#endif
