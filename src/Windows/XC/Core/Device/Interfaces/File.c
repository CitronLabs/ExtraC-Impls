#include "../Dev.h"
#define module env, Windows, XC, Core, Device, Stream, Type, FILE

from(env_Windows_Lib, 
	FS_File as File,
	FS_Dir  as Dir,

);

errvt moduleFn(watch)(streamHandle handle){
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;


	iferr(WinLib.FS.File.watch(file)){
		return ERR(ERR.FAIL, "Failed to watch file");
	}

return OK;
}

len_t moduleFn(isModified)(streamHandle handle){
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;

return WinLib.FS.File.isModified(file);
}

len_t moduleFn(shift)(streamHandle handle, word offset, len_t from){
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;

	len_t filesize   = size(file);

	len_t currentOff = from == 0 ? len(file) : ({
		if(from > filesize){
		    ERR(ERR.INVALID, "cannot shift from beyond the current file size");
		    return 0;
		}	
		from;
	});

	len_t offsetPos = 0;

	if(offset > 0){
	     if(currentOff + offset > filesize){
		ERR(ERR.INVALID, "cannot shift to beyond the current file size");
		return 0;
	    }

	    offsetPos = currentOff + offset;

	} else {
	    offsetPos = (-offset) >= currentOff ? 0 : currentOff + offset;
	}


	set(file, &offsetPos);

return offsetPos;
}

len_t moduleFn(readFrom)(streamHandle handle, void* buffer, len_t size){
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;
	
return read(file, &arr_from(buffer, sizeof(byte), size));
}

len_t moduleFn(writeTo)(streamHandle handle, const void* buffer, len_t size){
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;

return write(file, &arr_from(generic buffer, sizeof(byte), size));
}

streamInfo moduleFn(info)(streamHandle handle){
	mod(sync)(handle);

	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;

return (streamInfo){
	
};
}

errvt moduleFn(control)(streamHandle handle, word command, void* args){
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;
}
errvt moduleFn(flush)(streamHandle handle){
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;
}
errvt moduleFn(sync)(streamHandle handle){ 
	File* file = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->data;

	WinLib.FS.File.sync(file);

}

