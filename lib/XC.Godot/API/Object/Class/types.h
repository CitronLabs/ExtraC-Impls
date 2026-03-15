#pragma once
#define __GODOT_API_OBJECT_CLASS__
#include "pkg.h"
#define package gde_Object_Class



typefrom(constpntr, 		MethodBindPtr);
type_fn(gde_Object_Ptr, 	Constructor);
typefrom(pntr, 			InstancePtr);

type_fn(gde_Bool, Set,	gde_Object_Class_InstancePtr, gde_String_ConstNamePtr, gde_Type_Variant_ConstPtr);
type_fn(gde_Bool, Get,	gde_Object_Class_InstancePtr, gde_String_ConstNamePtr, gde_Type_Variant_Ptr);
type_fn(u64, 		GetRID,	gde_Object_Class_InstancePtr);

type(PropertyInfo,
	gde_Type_Variant_Type type;
	gde_String_NamePtr name;
	gde_String_NamePtr class_name;
	u32 hint; // Bitfield of `PropertyHint` (defined in `extension_api.json`).
	gde_String_Ptr hint_string;
	u32 usage; // Bitfield of `PropertyUsageFlags` (defined in `extension_api.json`).
)

type(MethodInfo,
	gde_String_NamePtr 		name;
	gde_Object_Class_PropertyInfo 	return_value;
	u32 					flags; 		// Bitfield of `GDE_ClassMethodFlags`.
	i32 					id;

	/* Arguments: `default_arguments` is an array of size `argument_count`. */
	u32 					argument_count;
	gde_Object_Class_PropertyInfo*	arguments;

	/* Default arguments: `default_arguments` is an array of size `default_argument_count`. */
	u32 					default_argument_count;
	gde_Type_Variant_Ptr*		default_arguments;
)

#define PropertyInfo const pkg(PropertyInfo)*
#define InstancePtr_t  gde_Object_Class_InstancePtr
#define CallVirtual_t  gde_Object_Class_CallVirtual
type_fn(void, 		FreePropertyList, 	 gde_Object_Class_InstancePtr, const gde_Object_Class_PropertyInfo*);
type_fn(void, 		FreePropertyList2,	 gde_Object_Class_InstancePtr, const gde_Object_Class_PropertyInfo*, u32);
type_fn(gde_Bool,	PropertyCanRevert,	 gde_Object_Class_InstancePtr, gde_String_ConstNamePtr);
type_fn(gde_Bool,	PropertyGetRevert,	 gde_Object_Class_InstancePtr, gde_String_ConstNamePtr, gde_Type_Variant_Ptr);
type_fn(gde_Bool,	ValidateProperty,	 gde_Object_Class_InstancePtr, gde_Object_Class_PropertyInfo*);
type_fn(PropertyInfo, 	GetPropertyList, 	 gde_Object_Class_InstancePtr, u32*);


type_fn(void,			Notification,		gde_Object_Class_InstancePtr, i32 , 	     gde_Bool);
type_fn(void,			ToString,		gde_Object_Class_InstancePtr, gde_Bool*, gde_String_Ptr);
type_fn(void,			Reference,		gde_Object_Class_InstancePtr);
type_fn(void,			Unreference,		gde_Object_Class_InstancePtr);
type_fn(void,			CallVirtual,		gde_Object_Class_InstancePtr, const gde_Type_ConstPtr*, gde_Type_Ptr);
type_fn(gde_Object_Ptr,	CreateInstance,		void*, gde_Bool);
type_fn(void,			FreeInstance,		void*, gde_Object_Class_InstancePtr);
type_fn(InstancePtr_t,		RecreateInstance,	void*, gde_Object_Ptr);
type_fn(CallVirtual_t,		GetVirtual,		void*, gde_String_ConstNamePtr, u32);
type_fn(void*,			GetVirtualCallData,	void*, gde_String_ConstNamePtr, u32);
type_fn(void,			CallVirtualWithData,
						gde_Object_Class_InstancePtr, 
						gde_String_ConstNamePtr,
						void*,
						const gde_Type_ConstPtr*,
						gde_Type_Ptr
					);
#undef PropertyInfo
#undef InstancePtr
#undef CallVirtual

type(CreationInfo,
	gde_Bool 			is_virtual;
	gde_Bool 			is_abstract;
	gde_Bool 			is_exposed;
	gde_Bool 			is_runtime;
	gde_String_ConstPtr 	icon_path;
	pkg(Set) 			set_func;
	pkg(Get) 			get_func;
	pkg(GetPropertyList) 		get_property_list_func;
	pkg(FreePropertyList2) 		free_property_list_func;
	pkg(PropertyCanRevert) 		property_can_revert_func;
	pkg(PropertyGetRevert) 		property_get_revert_func;
	pkg(ValidateProperty) 		validate_property_func;
	pkg(Notification) 		notification_func;
	pkg(ToString) 			to_string_func;
	pkg(Reference) 			reference_func;
	pkg(Unreference) 		unreference_func;
	pkg(CreateInstance) 		create_instance_func; 		// (Default) constructor; mandatory. 
	pkg(FreeInstance) 		free_instance_func; 		// Destructor; mandatory.
	pkg(RecreateInstance) 		recreate_instance_func;

	// Queries a virtual function by name and returns a callback to invoke the requested virtual function.
	pkg(GetVirtual) 		get_virtual_func;

	// Paired with `call_virtual_with_data_func`, this is an alternative to `get_virtual_func` for extensions that
	// need or benefit from extra data when calling virtual functions.
	// Returns user data that will be passed to `call_virtual_with_data_func`.
	// Returning `NULL` from this function signals to Godot that the virtual function is not overridden.
	// Data returned from this function should be managed by the extension and must be valid until the extension is deinitialized.
	// You should supply either `get_virtual_func`, or `get_virtual_call_data_func` with `call_virtual_with_data_func`.
	pkg(GetVirtualCallData) 	get_virtual_call_data_func;

	// Used to call virtual functions when `get_virtual_call_data_func` is not null.
	pkg(CallVirtualWithData) 	call_virtual_with_data_func;

	void *class_userdata; // Per-class user data, later accessible in instance bindings.
)

#undef package
#define package gde_Object_Class_Method

typefrom(u32, Flag);
typefrom(u32, ArgMetadata);
typefrom(pntr, 		BindPtr);

type_fn(void, Call,		
		void*,
		gde_Object_Class_InstancePtr,
		const gde_Type_Variant_ConstPtr*,
		gde_Int,
		gde_Type_Variant_Ptr,
		gde_CallError*
	);


type_fn(void, ValidatedCall,
		void*,
		gde_Object_Class_InstancePtr,
		const gde_Type_Variant_ConstPtr*,
		gde_Type_Variant_Ptr
	);

type_fn(void, PtrCall,	
		void*, 
		gde_Object_Class_InstancePtr, 
		const gde_Type_ConstPtr*,
		gde_Type_Ptr
	);

type(Info,
	gde_String_NamePtr 		name;
	void*					method_userdata;
	gde_Object_Class_Method_Call 	call_func;
	gde_Object_Class_Method_PtrCall 	ptrcall_func;
	u32 					method_flags; // Bitfield of `GDE_ClassMethodFlags`.

	/* If `has_return_value` is false, `return_value_info` and `return_value_metadata` are ignored.
	 *
	 * @todo Consider dropping `has_return_value` and making the other two properties match `GDE_MethodInfo` and `GDE_ClassVirtualMethod` for consistency in future version of this struct.
	 */
	gde_Bool has_return_value;
	gde_Object_Class_PropertyInfo *return_value_info;
	gde_Object_Class_Method_ArgMetadata return_value_metadata;

	/* Arguments: `arguments_info` and `arguments_metadata` are array of size `argument_count`.
	 * Name and hint information for the argument can be omitted in release builds. Class name should always be present if it applies.
	 *
	 * @todo Consider renaming `arguments_info` to `arguments` for consistency in future version of this struct.
	 */
	u32 argument_count;
	gde_Object_Class_PropertyInfo *arguments_info;
	gde_Object_Class_Method_ArgMetadata *arguments_metadata;

	/* Default arguments: `default_arguments` is an array of size `default_argument_count`. */
	u32 default_argument_count;
	gde_Type_Variant_Ptr *default_arguments;
)

type(VirtualInfo,
	gde_String_NamePtr name;
	u32 method_flags; // Bitfield of `GDE_ClassMethodFlags`.

	gde_Object_Class_PropertyInfo return_value;
	gde_Object_Class_Method_ArgMetadata return_value_metadata;

	u32 argument_count;
	gde_Object_Class_PropertyInfo *arguments;
	gde_Object_Class_Method_ArgMetadata *arguments_metadata;
)


#undef package
