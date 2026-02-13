#include "../Dev.h"
#define module core, Device, Stream, Type, FILE

from(env_Windows_Lib, 
	FS_File as File,
	FS_Dir  as Dir,

);

errvt moduleFn(watch)(streamHandle handle){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}

len_t moduleFn(isModified)(streamHandle handle){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}

len_t moduleFn(shift)(streamHandle handle, word offset, len_t from){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}

len_t moduleFn(readFrom)(streamHandle handle, void* buffer, len_t size){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
	
	
}

len_t moduleFn(writeTo)(streamHandle handle, const void* buffer, len_t size){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}

streamInfo moduleFn(info)(streamHandle handle){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}

errvt moduleFn(control)(streamHandle handle, word command, void* args){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}
errvt moduleFn(flush)(streamHandle handle){
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}
errvt moduleFn(sync)(streamHandle handle){ 
	File* file = Dev.Resource.getOne(
			WinRTDev.getManager(),
			WinRTDev.getIO(),
			(pntrval)handle
		)->data;
}
