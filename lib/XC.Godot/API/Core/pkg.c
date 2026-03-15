#pragma once
#include <Godot.pkg.h>

#define module godot, API, Core, Mem

moduleValuesDef(FuncNames,
	.Alloc 			= "mem_alloc",
	.Realloc 		= "mem_realloc",
	.Free 			= "mem_free",
	.GetNativeStructSize 	= "get_native_struct_size"
)


export(
SUBMODULE(),
VALUES(FuncNames),
	load
)

#undef module
#define module godot, API, Core, Print

moduleValuesDef(FuncNames,
	.Error			= "print_error",
	.ErrorWithMessage	= "print_error_with_message",
	.Warning		= "print_warning",
	.WarningWithMessage	= "print_warning_with_message",
	.ScriptError		= "print_script_error",
	.ScriptErrorWithMessage = "print_script_error_with_message"
)


export(
SUBMODULE(),
VALUES(FuncNames),
	load
)

#undef module
#define module godot, API, Core, File

moduleValuesDef(FuncNames,
	.XmlParserOpenBuffer	= "xml_parser_open_buffer",
	.FileAccessStoreBuffer	= "file_access_store_buffer",
	.FileAccessGetBuffer	= "file_access_get_buffer",
	.ImagePtrw		= "image_ptrw",
	.ImagePtr		= "image_ptr"
)

export(
SUBMODULE(),
VALUES(FuncNames),
	load
)

#undef module
#define module godot, API, Core, ThreadPool

moduleValuesDef(FuncNames,
	.AddNativeGroupTask	= "worker_thread_pool_add_native_group_task",
	.AddNativeTask		= "worker_thread_pool_add_native_task"
)

export(
SUBMODULE(),
VALUES(FuncNames),
	load
)

#undef module
#define module godot, API, Core

export(
SUBMODULE(Mem, File, Print, ThreadPool),
VALUES(),
	load
)

#undef module
