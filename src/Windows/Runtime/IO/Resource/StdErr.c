#include "../IO.h"

static struct {
	Console* console;
} StdErr;

errvt moduleFn(Resource_StdErr_watch)(streamHandle handle){
	return ERR(ERR.INVALID, "Cannot watch XC.IO:/Console/StdErr"); 
}

len_t moduleFn(Resource_StdErr_isModified)(streamHandle handle){
	ERR(ERR.INVALID, "Cannot watch XC.IO:/Console/StdErr"); 
	return 0;
}

len_t moduleFn(Resource_StdErr_shift)(streamHandle handle, word offset, len_t from){
	ERR(ERR.INVALID, "Cannot shift XC.IO:/Console/StdErr"); 
	return 0;
}

len_t moduleFn(Resource_StdErr_readFrom)(streamHandle handle, void* buffer, len_t size){
	ERR(ERR.INVALID, "XC.IO:/Console/StdErr cannot be read from");
	return 0;
}

len_t moduleFn(Resource_StdErr_writeTo)(streamHandle handle, const void* buffer, len_t size){
	
	if(!StdErr.console) mod(Resource_StdErr_sync)(handle);

return WinLib.Console.writeErr(StdErr.console, buffer, size);
}

streamInfo moduleFn(Resource_StdErr_info)(streamHandle handle){
return (streamInfo){
.name 		= "StdErr",
.path 		= "Console/StdErr",
.attributes 	= core.Device.Stream.Attrib.READ,
.type 		= nil,
.currentPos    	= 0,
.time_created  	= 0,
.time_modified 	= 0,
.size 		= 0,
.valid 		= true
};
}

errvt moduleFn(Resource_StdErr_control)(streamHandle handle, word command, void* args){ return OK; }
errvt moduleFn(Resource_StdErr_flush)(streamHandle handle){ return OK; }
errvt moduleFn(Resource_StdErr_sync)(streamHandle handle){ 

	var stdErrResource = Dev.Resource.getOne(
		WinRT.Resource.getManager(),
		WinRT.IO.getID(),
		(pntrval)handle
	);

	if(!stdErrResource){
		ERR(ERR.FAIL, "Failed to access XC.IO:/Console/StdErr");
		return 0;
	}

	StdErr.console = stdErrResource->data;

return OK; 
}
