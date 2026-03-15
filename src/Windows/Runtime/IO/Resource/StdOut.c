#include "../IO.h"

static struct {	
	Console* console;
} StdOut;

errvt moduleFn(Resource_StdOut_watch)(streamHandle handle){
	return ERR(ERR.INVALID, "Cannot watch XC.IO:/Console/StdOut"); 
}

len_t moduleFn(Resource_StdOut_isModified)(streamHandle handle){
	ERR(ERR.INVALID, "Cannot watch XC.IO:/Console/StdOut"); 
	return 0;
}

len_t moduleFn(Resource_StdOut_shift)(streamHandle handle, word offset, len_t from){
	ERR(ERR.INVALID, "Cannot shift XC.IO:/Console/StdOut"); 
	return 0;
}

len_t moduleFn(Resource_StdOut_readFrom)(streamHandle handle, void* buffer, len_t size){
	ERR(ERR.INVALID, "XC.IO:/Console/StdOut cannot be read from");
	return 0;
}

len_t moduleFn(Resource_StdOut_writeTo)(streamHandle handle, const void* buffer, len_t size){
	
	if(!StdOut.console) mod(Resource_StdOut_sync)(handle);

return WinLib.Console.writeOut(StdOut.console, buffer, size);
}

streamInfo moduleFn(Resource_StdOut_info)(streamHandle handle){
return (streamInfo){
.name 		= "StdOut",
.path 		= "Console/StdOut",
.attributes 	= core.Device.Stream.Attrib.READ,
.type 		= nil,
.currentPos    	= 0,
.time_created  	= 0,
.time_modified 	= 0,
.size 		= 0,
.valid 		= true
};
}

errvt moduleFn(Resource_StdOut_control)(streamHandle handle, word command, void* args){ return OK; }
errvt moduleFn(Resource_StdOut_flush)(streamHandle handle){ return OK; }
errvt moduleFn(Resource_StdOut_sync)(streamHandle handle){ 

	var stdOutResource = Dev.Resource.getOne(
		WinRT.Resource.getManager(),
		WinRT.IO.getID(),
		(pntrval)handle
	);

	if(!stdOutResource){
		ERR(ERR.FAIL, "Failed to access XC.IO:/Console/StdOut");
		return 0;
	}

	StdOut.console = stdOutResource->data;

return OK; 
}
