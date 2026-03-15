#pragma once
#define __ENV_GODOT_API__
#include "../pkg.h"
#include "../types.h"
#include "../String/pkg.h"
#include "../Object/pkg.h"

#ifndef __ENV_GODOT_API_CORE__
#define package gde_Core

Interface(Mem,
/**
 * @name mem_alloc
 * @since 4.1
 *
 * Allocates memory.
 *
 * @param p_bytes The amount of memory to allocate in bytes.
 *
 * @return A pointer to the allocated memory, or NULL if unsuccessful.
 */
	void *vfn(Alloc)(len_t p_bytes);

/**
 * @name mem_realloc
 * @since 4.1
 *
 * Reallocates memory.
 *
 * @param p_ptr A pointer to the previously allocated memory.
 * @param p_bytes The number of bytes to resize the memory block to.
 *
 * @return A pointer to the allocated memory, or NULL if unsuccessful.
 */
	void *vfn(Realloc)(void *p_ptr, len_t p_bytes);

/**
 * @name mem_free
 * @since 4.1
 *
 * Frees memory.
 *
 * @param p_ptr A pointer to the previously allocated memory.
 */
	void vfn(Free)(void *p_ptr);

/**
 * @name get_native_struct_size
 * @since 4.1
 *
 * Gets the size of a native struct (ex. ObjectID) in bytes.
 *
 * @param p_name A pointer to a StringName identifying the struct name.
 *
 * @return The size in bytes.
 */
	u64 vfn(GetNativeStructSize)(gde_String_ConstNamePtr p_name);
)

Interface(Print,
/**
 * @name print_error
 * @since 4.1
 *
 * Logs an error to Godot's built-in debugger and to the OS terminal.
 *
 * @param p_description The code triggering the error.
 * @param p_function The function name where the error occurred.
 * @param p_file The file where the error occurred.
 * @param p_line The line where the error occurred.
 * @param p_editor_notify Whether or not to notify the editor.
 */
	void vfn(Error)(
		const char *p_description, 
		const char *p_function, 
		const char *p_file, 
		i32 p_line, 
		gde_Bool p_editor_notify
	);

/**
 * @name print_error_with_message
 * @since 4.1
 *
 * Logs an error with a message to Godot's built-in debugger and to the OS terminal.
 *
 * @param p_description The code triggering the error.
 * @param p_message The message to show along with the error.
 * @param p_function The function name where the error occurred.
 * @param p_file The file where the error occurred.
 * @param p_line The line where the error occurred.
 * @param p_editor_notify Whether or not to notify the editor.
 */
	void vfn(ErrorWithMessage)(
		const char *p_description,
		const char *p_message,
		const char *p_function,
		const char *p_file,
		i32 p_line,
		gde_Bool p_editor_notify
	);

/**
 * @name print_warning
 * @since 4.1
 *
 * Logs a warning to Godot's built-in debugger and to the OS terminal.
 *
 * @param p_description The code triggering the warning.
 * @param p_function The function name where the warning occurred.
 * @param p_file The file where the warning occurred.
 * @param p_line The line where the warning occurred.
 * @param p_editor_notify Whether or not to notify the editor.
 */
	void vfn(Warning)(
		const char *p_description,
		const char *p_function,
		const char *p_file,
		i32 p_line,
		gde_Bool p_editor_notify
	);

/**
 * @name print_warning_with_message
 * @since 4.1
 *
 * Logs a warning with a message to Godot's built-in debugger and to the OS terminal.
 *
 * @param p_description The code triggering the warning.
 * @param p_message The message to show along with the warning.
 * @param p_function The function name where the warning occurred.
 * @param p_file The file where the warning occurred.
 * @param p_line The line where the warning occurred.
 * @param p_editor_notify Whether or not to notify the editor.
 */
	void vfn(WarningWithMessage)(
		const char *p_description, 
		const char *p_message, 
		const char *p_function, 
		const char *p_file, 
		i32 p_line, 
		gde_Bool p_editor_notify
	);

/**
 * @name print_script_error
 * @since 4.1
 *
 * Logs a script error to Godot's built-in debugger and to the OS terminal.
 *
 * @param p_description The code triggering the error.
 * @param p_function The function name where the error occurred.
 * @param p_file The file where the error occurred.
 * @param p_line The line where the error occurred.
 * @param p_editor_notify Whether or not to notify the editor.
 */
	void vfn(ScriptError)(
		const char *p_description,
		const char *p_function,
		const char *p_file,
		i32 p_line,
		gde_Bool p_editor_notify
	);

/**
 * @name print_script_error_with_message
 * @since 4.1
 *
 * Logs a script error with a message to Godot's built-in debugger and to the OS terminal.
 *
 * @param p_description The code triggering the error.
 * @param p_message The message to show along with the error.
 * @param p_function The function name where the error occurred.
 * @param p_file The file where the error occurred.
 * @param p_line The line where the error occurred.
 * @param p_editor_notify Whether or not to notify the editor.
 */
	void vfn(ScriptErrorWithMessage)(
		const char *p_description,
		const char *p_message,
		const char *p_function,
		const char *p_file,
		i32 p_line,
		gde_Bool p_editor_notify
	);
)

Interface(File,
/**
 * @name xml_parser_open_buffer
 * @since 4.1
 *
 * Opens a raw XML buffer on an XMLParser instance.
 *
 * @param p_instance A pointer to an XMLParser object.
 * @param p_buffer A pointer to the buffer.
 * @param p_size The size of the buffer.
 *
 * @return A Godot error code (ex. OK, ERR_INVALID_DATA, etc).
 *
 * @see XMLParser::open_buffer()
 */
	gde_Int vfn(XmlParserOpenBuffer)(gde_Object_Ptr p_instance, const u8* p_buffer, len_t p_size);


/**
 * @name file_access_store_buffer
 * @since 4.1
 *
 * Stores the given buffer using an instance of FileAccess.
 *
 * @param p_instance A pointer to a FileAccess object.
 * @param p_src A pointer to the buffer.
 * @param p_length The size of the buffer.
 *
 * @see FileAccess::store_buffer()
 */
	void vfn(FileAccessStoreBuffer)(gde_Object_Ptr p_instance, const u8 *p_src, u64 p_length);

/**
 * @name file_access_get_buffer
 * @since 4.1
 *
 * Reads the next p_length bytes into the given buffer using an instance of FileAccess.
 *
 * @param p_instance A pointer to a FileAccess object.
 * @param p_dst A pointer to the buffer to store the data.
 * @param p_length The requested number of bytes to read.
 *
 * @return The actual number of bytes read (may be less than requested).
 */
	u64 vfn(FileAccessGetBuffer)(gde_Object_ConstPtr p_instance, u8 *p_dst, u64 p_length);

/* INTERFACE: Image Utilities */

/**
 * @name image_ptrw
 * @since 4.3
 *
 * Returns writable pointer to internal Image buffer.
 *
 * @param p_instance A pointer to a Image object.
 *
 * @return Pointer to internal Image buffer.
 *
 * @see Image::ptrw()
 */
	u8 *vfn(ImagePtrw)(gde_Object_Ptr p_instance);

/**
 * @name image_ptr
 * @since 4.3
 *
 * Returns read only pointer to internal Image buffer.
 *
 * @param p_instance A pointer to a Image object.
 *
 * @return Pointer to internal Image buffer.
 *
 * @see Image::ptr()
 */
	const u8 *vfn(ImagePtr)(gde_Object_Ptr p_instance);
)

type_fn(void, ThreadPool_GroupTask, void *, u32);
type_fn(void, ThreadPool_Task, void *);
Interface(ThreadPool,
/**
 * @name worker_thread_pool_add_native_group_task
 * @since 4.1
 *
 * Adds a group task to an instance of WorkerThreadPool.
 *
 * @param p_instance A pointer to a WorkerThreadPool object.
 * @param p_func A pointer to a function to run in the thread pool.
 * @param p_userdata A pointer to arbitrary data which will be passed to p_func.
 * @param p_elements The number of element needed in the group.
 * @param p_tasks The number of tasks needed in the group.
 * @param p_high_priority Whether or not this is a high priority task.
 * @param p_description A pointer to a String with the task description.
 *
 * @return The task group ID.
 *
 * @see WorkerThreadPool::add_group_task()
 */
	i64 vfn(AddNativeGroupTask)(
	  	gde_Object_Ptr p_instance, 
	  	gde_Core_ThreadPool_GroupTask p_func, 
	  	void *p_userdata, 
	  	int p_elements, 
	  	int p_tasks,
	  	gde_Bool p_high_priority, 
	  	gde_String_ConstPtr p_description
	);

/**
 * @name worker_thread_pool_add_native_task
 * @since 4.1
 *
 * Adds a task to an instance of WorkerThreadPool.
 *
 * @param p_instance A pointer to a WorkerThreadPool object.
 * @param p_func A pointer to a function to run in the thread pool.
 * @param p_userdata A pointer to arbitrary data which will be passed to p_func.
 * @param p_high_priority Whether or not this is a high priority task.
 * @param p_description A pointer to a String with the task description.
 *
 * @return The task ID.
 */
	i64 vfn(AddNativeTask)(
	  	gde_Object_Ptr p_instance, 
	  	gde_Core_ThreadPool_Task p_func, 
	  	void* p_userdata, 
	  	gde_Bool p_high_priority, 
	  	gde_String_ConstPtr p_description
	);
)

Interface_Pkg(
	vtable(pkg(Mem))   	 Mem;
	vtable(pkg(Print)) 	 Print;
	vtable(pkg(File))  	 File;
	vtable(pkg(ThreadPool))  ThreadPool;
)

#undef package
#endif
