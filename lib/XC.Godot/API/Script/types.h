#pragma once
#define __ENV_GODOT_API_SCRIPT__
#include "pkg.h"
#define package gde_Script

typefrom(pntr, InstanceDataPtr); // Pointer to custom Script_Instance native implementation.

#define ConstPropInfo const gde_Object_Class_PropertyInfo*
#define PropInfo            gde_Object_Class_PropertyInfo*
#define MethodInfo    const gde_Object_Class_Method_Info*

type_fn(gde_Bool, Set, gde_Script_InstanceDataPtr, gde_String_ConstNamePtr, gde_Type_Variant_ConstPtr);
type_fn(gde_Bool, Get, gde_Script_InstanceDataPtr, gde_String_ConstNamePtr, gde_Type_Variant_Ptr);
type_fn(ConstPropInfo,  GetPropertyList,  gde_Script_InstanceDataPtr, u32*);
type_fn(void, 		FreePropertyList, gde_Script_InstanceDataPtr, ConstPropInfo, u32); 
type_fn(gde_Bool, GetClassCategory, gde_Script_InstanceDataPtr, PropInfo);

type_fn(gde_Type_Variant_Type, GetPropertyType, 
			gde_Script_InstanceDataPtr,
			gde_String_ConstNamePtr,
			gde_Bool*
);

type_fn(gde_Bool, ValidateProperty,  gde_Script_InstanceDataPtr, PropInfo);

type_fn(gde_Bool, PropertyCanRevert, gde_Script_InstanceDataPtr, gde_String_ConstNamePtr);
type_fn(gde_Bool, PropertyGetRevert, gde_Script_InstanceDataPtr, gde_String_ConstNamePtr, gde_Type_Variant_Ptr);

type_fn(gde_Object_Ptr, GetOwner, gde_Script_InstanceDataPtr);
type_fn(void, PropertyStateAdd, gde_String_ConstNamePtr, gde_Type_Variant_ConstPtr, void*);
type_fn(void, GetPropertyState, gde_Script_InstanceDataPtr,  gde_Script_PropertyStateAdd, void*);

type_fn(MethodInfo, GetMethodList, gde_Script_InstanceDataPtr, u32*);
type_fn(void, FreeMethodList, gde_Script_InstanceDataPtr, MethodInfo, u32);

type_fn(gde_Bool, HasMethod, gde_Script_InstanceDataPtr, gde_String_ConstNamePtr);

type_fn(gde_Int, GetMethodArgumentCount, gde_Script_InstanceDataPtr, gde_String_ConstNamePtr, gde_Bool*);

type_fn(void, Call, 
		gde_Script_InstanceDataPtr, 
		gde_String_ConstNamePtr, 
		const gde_Type_Variant_ConstPtr*, 
		gde_Int, 
		gde_Type_Variant_Ptr, 
		gde_CallError*
);

type_fn(void, Notification, 	gde_Script_InstanceDataPtr, i32, gde_Bool);
type_fn(void, ToString, 	gde_Script_InstanceDataPtr, gde_Bool*, gde_String_Ptr);

type_fn(void, 		RefCountIncremented, gde_Script_InstanceDataPtr);
type_fn(gde_Bool, RefCountDecremented, gde_Script_InstanceDataPtr);

type_fn(gde_Object_Ptr, 	GetScript, 	gde_Script_InstanceDataPtr);
type_fn(gde_Bool, 	IsPlaceholder, 	gde_Script_InstanceDataPtr);

typefrom(pntr, LanguagePtr);

type_fn(gde_Script_LanguagePtr, GetLanguage, gde_Script_InstanceDataPtr);

type_fn(void, Free, gde_Script_InstanceDataPtr);

type_fn(pntr, InstancePtr); // Pointer to Script_Instance.

type(InstanceInfo,
	gde_Script_Set set_func;
	gde_Script_Get get_func;
	gde_Script_GetPropertyList get_property_list_func;
	gde_Script_FreePropertyList free_property_list_func;
	gde_Script_GetClassCategory get_class_category_func; // Optional. Set to NULL for the default behavior.

	gde_Script_PropertyCanRevert property_can_revert_func;
	gde_Script_PropertyGetRevert property_get_revert_func;

	gde_Script_GetOwner get_owner_func;
	gde_Script_GetPropertyState get_property_state_func;

	gde_Script_GetMethodList get_method_list_func;
	gde_Script_FreeMethodList free_method_list_func;
	gde_Script_GetPropertyType get_property_type_func;
	gde_Script_ValidateProperty validate_property_func;

	gde_Script_HasMethod has_method_func;

	gde_Script_GetMethodArgumentCount get_method_argument_count_func;

	gde_Script_Call call_func;
	gde_Script_Notification notification_func;

	gde_Script_ToString to_string_func;

	gde_Script_RefCountIncremented refcount_incremented_func;
	gde_Script_RefCountDecremented refcount_decremented_func;

	gde_Script_GetScript get_script_func;

	gde_Script_IsPlaceholder is_placeholder_func;

	gde_Script_Set set_fallback_func;
	gde_Script_Get get_fallback_func;

	gde_Script_GetLanguage get_language_func;

	gde_Script_Free free_func;
)
