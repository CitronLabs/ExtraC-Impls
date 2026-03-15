#pragma once
#define __ENV_GODOT_API__
#include "../pkg.h"
#include "../types.h"
#include "../String/pkg.h"
#include "../Type/pkg.h"
#include "../Object/pkg.h"

#ifndef __ENV_GODOT_API_SCRIPT__
#include "types.h"

#define package gde_Script

Interface_Pkg(
/**
 * @name script_instance_create3
 * @since 4.3
 *
 * Creates a script instance that contains the given info and instance data.
 *
 * @param p_info A pointer to a gde_ScriptInstanceInfo3 struct.
 * @param p_instance_data A pointer to a data representing the script instance in the gde_. This will be passed to all the function pointers on p_info.
 *
 * @return A pointer to a ScriptInstanceExtension object.
 */
	gde_Script_InstancePtr vfn(ScriptInstanceCreate)(
			const gde_Script_InstanceInfo* p_info, 
			gde_Script_InstanceDataPtr p_instance_data
	);

/**
 * @name placeholder_script_instance_create
 * @since 4.2
 *
 * Creates a placeholder script instance for a given script and instance.
 *
 * This interface is optional as a custom placeholder could also be created with script_instance_create().
 *
 * @param p_language A pointer to a ScriptLanguage.
 * @param p_script A pointer to a Script.
 * @param p_owner A pointer to an Object.
 *
 * @return A pointer to a PlaceHolderScriptInstance object.
 */
	gde_Script_InstancePtr vfn(PlaceHolderInstanceCreate)(
			gde_Object_Ptr p_language, 
			gde_Object_Ptr p_script, 
			gde_Object_Ptr p_owner
	);

/**
 * @name placeholder_script_instance_update
 * @since 4.2
 *
 * Updates a placeholder script instance with the given properties and values.
 *
 * The passed in placeholder must be an instance of PlaceHolderScriptInstance
 * such as the one returned by placeholder_script_instance_create().
 *
 * @param p_placeholder A pointer to a PlaceHolderScriptInstance.
 * @param p_properties A pointer to an Array of Dictionary representing PropertyInfo.
 * @param p_values A pointer to a Dictionary mapping StringName to Variant values.
 */
	void vfn(PlaceHolderInstanceUpdate)(
			gde_Script_InstancePtr p_placeholder, 
			gde_Type_ConstPtr p_properties, 
			gde_Type_ConstPtr p_values
	);

/**
 * @name object_get_script_instance
 * @since 4.2
 *
 * Get the script instance data attached to this object.
 *
 * @param p_object A pointer to the Object.
 * @param p_language A pointer to the language expected for this script instance.
 *
 * @return A gde_ScriptInstanceDataPtr that was attached to this object as part of script_instance_create.
 */
	gde_Script_InstanceDataPtr vfn(ObjectGetScriptInstance)(
			gde_Object_ConstPtr p_object, 
			gde_Object_Ptr p_language
	);

/**
 * @name object_set_script_instance
 * @since 4.5
 *
 * Set the script instance data attached to this object.
 *
 * @param p_object A pointer to the Object.
 * @param p_script_instance A pointer to the script instance data to attach to this object.
 */
	void vfn(ObjectSetScriptInstance)(
			gde_Object_Ptr p_object, 
			gde_Script_InstanceDataPtr p_script_instance
	);
)

#undef package
#endif
