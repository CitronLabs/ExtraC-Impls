#include "../Dev.h"
#define module core, Device, Stream, Type, File

typedef struct {
	HFILE handle;
} File;


File* moduleFn(init)(streamHandle handle, const char* path, word attributes){

	LPOFSTRUCT fileInfo  =  0;
	int	   fileFlags =  0;

	if(attributes & core.Device.Stream.Attrib.READ)
		fileFlags = OF_READ;

	if(attributes & core.Device.Stream.Attrib.WRITE){
	    if(!fileFlags)
		fileFlags = OF_WRITE;
	    else
		fileFlags = OF_READWRITE;
	}

	if(fileFlags == 0){
		ERR(ERR.INVALID, "IO stream is neither being opened for write or read");
		return nil;
	}

	HFILE fileHandle = OpenFile(path, fileInfo, fileFlags | OF_CREATE);

	if(fileHandle == HFILE_ERROR){
		DWORD errval = GetLastError();
		

		strc16 errmsg = WinLib.Error.getMsg(errval);

		ERR(ERR.FAIL, "Failed to open IO stream");
		printlnErr("Reason: ", $(errmsg));

		WinLib.Error.freeMsg(errmsg);
		return nil;
	}

	File* result 	= malloc(sizeof(File));

	result->handle   = fileHandle;

return result;
}

errvt moduleFn(Resource_StdOut_open)(streamHandle handle, bool create){

}

errvt moduleFn(Resource_StdOut_close)(streamHandle handle){ 
}

errvt moduleFn(Resource_StdOut_delete)(streamHandle handle){ 
}

errvt moduleFn(Resource_StdOut_edit)(streamHandle handle, const char* name, word attributes){
}

errvt moduleFn(Resource_StdOut_watch)(streamHandle handle){
}

len_t moduleFn(Resource_StdOut_isModified)(streamHandle handle){
}

len_t moduleFn(Resource_StdOut_shift)(streamHandle handle, word offset, len_t from){
}

len_t moduleFn(Resource_StdOut_readFrom)(streamHandle handle, void* buffer, len_t size){
}

len_t moduleFn(Resource_StdOut_writeTo)(streamHandle handle, const void* buffer, len_t size){
}

streamInfo moduleFn(Resource_StdOut_info)(streamHandle handle){
}

errvt moduleFn(Resource_StdOut_control)(streamHandle handle, word command, void* args){
}
errvt moduleFn(Resource_StdOut_flush)(streamHandle handle){
}
errvt moduleFn(Resource_StdOut_sync)(streamHandle handle){ 
}
