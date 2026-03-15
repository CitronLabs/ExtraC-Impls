#pragma once
#define __GODOT_API__
#include "pkg.h"

#define package gde

typefrom(i64, 		Int);
typefrom(u8, 		Bool);
typefrom(pntr, 		Ptr);
typefrom(constpntr,  	ConstPtr);
typefrom(pntr, 		UninitPtr);
typefrom(pntr, 		Object_InstanceID);

#define Call_ErrorType							\
	ALLOK,								\
	INVALID_METHOD,							\
	INVALID_ARGUMENT,   /*Expected a different variant type.*/	\
	TOO_MANY_ARGUMENTS, /*Expected lower number of arguments.*/	\
	TOO_FEW_ARGUMENTS,  /*Expected higher number of arguments.*/	\
	INSTANCE_IS_NULL,						\
	METHOD_NOT_CONST    /*Used for const call.*/			


type(CallError,
	errvt error;
	i32   argument;
	i32   expected;
)

typefrom(uword, InitLevel)

type_fn(void, InitializeCallback,   void *p_userdata, gde_InitLevel p_level);
type_fn(void, DeinitializeCallback, void *p_userdata, gde_InitLevel p_level);

type(Initialization,
	/* Minimum initialization level required.
	 * If Core or Servers, the extension needs editor or game restart to take effect */
	gde_InitLevel minInitLvl;
	/* Up to the user to supply when initializing */
	void *userdata;
	/* This function will be called multiple times for each initialization level. */
	gde_InitializeCallback 	 init;
	gde_DeinitializeCallback deinit;
)

type_fn(void, InterfaceFunctionPtr);
type_fn(gde_InterfaceFunctionPtr, InterfaceGetProcAddress, const char *p_function_name);

typefrom(pntr, ClassLibraryPtr)

/* Passed a pointer to a PackedStringArray that should be filled with the classes that may be used by the GDE_. */
type_fn(void, EditorGetClassesUsedCallback, void* p_packed_string_array);

type_fn(gde_Bool, InitializationFunction, 
			gde_InterfaceGetProcAddress p_get_proc_address, 
			gde_ClassLibraryPtr p_library, 
			gde_Initialization *r_initialization
	);


/* Called when starting the main loop. */
type_fn(void, MainLoopStartupCallback);

/* Called when shutting down the main loop. */
type_fn(void, MainLoopShutdownCallback);

/* Called for every frame iteration of the main loop. */
type_fn(void, MainLoopFrameCallback);

type(MainLoopCallbacks,
	// Will be called after Godot is started and is fully initialized.
	gde_MainLoopStartupCallback startup_func;
	// Will be called before Godot is shutdown when it is still fully initialized.
	gde_MainLoopShutdownCallback shutdown_func;
	// Will be called for each process frame. This will run after all `_process()` methods on Node, and before `ScriptServer::frame()`.
	// This is intended to be the equivalent of `ScriptLanguage::frame()` for gde_ language bindings that don't use the script API.
	gde_MainLoopFrameCallback frame_func;
)

#undef package
