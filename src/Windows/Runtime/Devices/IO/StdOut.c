#include "../Device.h"

static struct {	
} StdOut;

errvt moduleFn(Resource_StdOut_open)(streamHandle handle, bool create){
	var StdOutResource = Dev.Resource.getOne(
		WinRTDev.getManager(),
		WinRTDev.getIO(),
		(pntrval)handle
	);

	if(StdOutResource == nil){
		return ERR(ERR.INVALID, "Invalid handle");
	}
	
	StdOut.handle = WinRTCon.getStream(WinRTCon.StreamType.ERR);

	StdOutResource->data = &StdOut;

return OK;
}

errvt moduleFn(Resource_StdOut_close)(streamHandle handle){ 
	return ERR(ERR.INVALID, "Cannot close XC.IO:/Console/StdOut"); 
}

errvt moduleFn(Resource_StdOut_delete)(streamHandle handle){ 
	return ERR(ERR.INVALID, "Cannot delete XC.IO:/Console/StdOut"); 
}

errvt moduleFn(Resource_StdOut_edit)(streamHandle handle, const char* name, word attributes){
	return ERR(ERR.INVALID, "Cannot edit XC.IO:/Console/StdOut"); 
}

errvt moduleFn(Resource_StdOut_watch)(streamHandle handle){

	mod(Resource_StdOut_sync)(handle);
	StdOut.lastSize  	= StdOut.currentSize;

return OK;
}

len_t moduleFn(Resource_StdOut_isModified)(streamHandle handle){
	
	mod(Resource_StdOut_sync)(handle);

return StdOut.currentSize - StdOut.lastSize;
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
	DWORD bytesWritten = 0;
	if(!WriteFile(StdOut.handle, buffer, size, &bytesWritten, NULL)){
		ERR(ERR.FAIL, "Failed to write to XC.IO:/Console/StdOut");
		return 0;
	}

return bytesWritten;
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
.size 		= StdOut.currentSize,
.valid 		= true
};
}

errvt moduleFn(Resource_StdOut_control)(streamHandle handle, word command, void* args){ return OK; }
errvt moduleFn(Resource_StdOut_flush)(streamHandle handle){ return OK; }
errvt moduleFn(Resource_StdOut_sync)(streamHandle handle){ 
}
