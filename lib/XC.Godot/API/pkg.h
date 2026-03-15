#pragma once
#define __ENV_GODOT__
#include "../pkg.h"

// EXPORTS
#ifndef __ENV_GODOT_API__
#include "utils.h"
#include "types.h"
#include "String/pkg.h"
#include "Core/pkg.h"
#include "Type/pkg.h"
#include "Object/pkg.h"
#include "Script/pkg.h"

#define package gde
/*
 * Each GDExtension should define a C function that matches the signature of GDE_InitializationFunction,
 * and export it so that it can be loaded via dlopen() or equivalent for the given platform.
 *
 * For example:
 *
 *   GDE_Bool my_extension_init(GDE_InterfaceGetProcAddress p_get_proc_address, GDE_ClassLibraryPtr p_library, GDE_Initialization *r_initialization);
 *
 * This function's name must be specified as the 'entry_symbol' in the .gdextension file.
 *
 * This makes it the entry point of the GDE_ and will be called on initialization.
 *
 * The GDExtension can then modify the r_initialization structure, setting the minimum initialization level,
 * and providing pointers to functions that will be called at various stages of initialization/shutdown.
 *
 * The rest of the GDE_'s interface to Godot consists of function pointers that can be loaded
 * by calling p_get_proc_address("...") with the name of the function.
 *
 * For example:
 *
 *   GDE_InterfaceGetGodotVersion get_godot_version = (GDE_InterfaceGetGodotVersion)p_get_proc_address("get_godot_version");
 *
 * (Note that snippet may cause "cast between incompatible function types" on some compilers, you can
 * silence this by adding an intermediary `void*` cast.)
 *
 * You can then call it like a normal function:
 *
 *   GDE_GodotVersion godot_version;
 *   get_godot_version(&godot_version);
 *   printf("Godot v%d.%d.%d\n", godot_version.major, godot_version.minor, godot_version.patch);
 *
 * All of these interface functions are described below, together with the name that's used to load it,
 * and the function pointer typedef that shows its signature.
 */

Interface(Version,
	u32 	 
		MAJOR,
	 	MINOR,
		PATCH,
	  	HEX; 	// Full version encoded as hexadecimal with one byte (2 hex digits) per number (e.g. for "3.1.12" it would be 0x03010C)
	
	const char 
	  	* STATUS, // (e.g. "stable", "beta", "rc1", "rc2")
		* BUILD,  // (e.g. "custom_build")
		* HASH;   // Full Git commit hash.

	u64 TIME_STAMP; 	// Git commit date UNIX timestamp in seconds, or 0 if unavailable.
	const char * STRING; 	// (e.g. "Godot v3.1.4.stable.official.mono")
)

Interface(Editor,
/**
 * @name get_library_path
 * @since 4.1
 *
 * Gets the path to the current gde_ library.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param r_path A pointer to a String which will receive the path.
 */
	void vfn(GetLibraryPath)(gde_ClassLibraryPtr p_library, gde_String_UninitPtr r_path);

/**
 * @name editor_add_plugin
 * @since 4.1
 *
 * Adds an editor plugin.
 *
 * It's safe to call during initialization.
 *
 * @param p_class_name A pointer to a StringName with the name of a class (descending from EditorPlugin) which is already registered with ClassDB.
 */
	void vfn(AddPlugin)(gde_String_ConstNamePtr p_class_name);

/**
 * @name editor_remove_plugin
 * @since 4.1
 *
 * Removes an editor plugin.
 *
 * @param p_class_name A pointer to a StringName with the name of a class that was previously added as an editor plugin.
 */
	void vfn(RemovePlugin)(gde_String_ConstNamePtr p_class_name);

/**
 * @name editor_help_load_xml_from_utf8_chars
 * @since 4.3
 *
 * Loads new XML-formatted documentation data in the editor.
 *
 * The provided pointer can be immediately freed once the function returns.
 *
 * @param p_data A pointer to a UTF-8 encoded C string (null terminated).
 */
	void vfn(HelpLoadXmlFromUtf8Chars)(const char *p_data);

/**
 * @name editor_help_load_xml_from_utf8_chars_and_len
 * @since 4.3
 *
 * Loads new XML-formatted documentation data in the editor.
 *
 * The provided pointer can be immediately freed once the function returns.
 *
 * @param p_data A pointer to a UTF-8 encoded C string.
 * @param p_size The number of bytes (not code units).
 */
	void vfn(HelpLoadXmlFromUtf8CharsAndLen)(const char *p_data, gde_Int p_size);

/**
 * @name editor_register_get_classes_used_callback
 * @since 4.5
 *
 * Registers a callback that Godot can call to get the list of all classes (from ClassDB) that may be used by the calling gde_.
 *
 * This is used by the editor to generate a build profile (in "Tools" > "Engine Compilation Configuration Editor..." > "Detect from project"),
 * in order to recompile Godot with only the classes used.
 * In the provided callback, the gde_ should provide the list of classes that _may_ be used statically, thus the time of invocation shouldn't matter.
 * If a gde_ doesn't register a callback, Godot will assume that it could be using any classes.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_callback The callback to retrieve the list of classes used.
 */
	void vfn(EditorRegisterGetClassesUsedCallback)(gde_ClassLibraryPtr p_library, gde_EditorGetClassesUsedCallback p_callback);

/**
 * @name register_main_loop_callbacks
 * @since 4.5
 *
 * Registers callbacks to be called at different phases of the main loop.
 *
 * @param p_library A pointer the library received by the gde_'s entry point function.
 * @param p_callbacks A pointer to the structure that contains the callbacks.
 */
	void vfn(RegisterMainLoopCallbacks)(gde_ClassLibraryPtr p_library, const gde_MainLoopCallbacks *p_callbacks);
)

Module(gde){
	vtable(pkg(Version)) 		Version;
	vtable(pkg(Editor))		Editor;
	vtable(pkg(Script))		Script;
       	vtable(pkg(Type)) 		Type;
       	vtable(pkg(Object)) 		Object;
       	vtable(pkg(Object_Class)) 	Class;
       	vtable(pkg(Object_Callable))	Callable;
       	vtable(pkg(String)) 		String;
       	vtable(pkg(Core)) 		Core;
};

#undef package
#endif
