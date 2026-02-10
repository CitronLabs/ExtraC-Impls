#include "../Device.h"

from(env_Windows_Lib, 
     	use(Console)
);

static struct {
	Console* console;
} ConsoleInfo;

errvt moduleFn(Resource_Console_watch)(streamHandle handle){
	return ERR(ERR.INVALID, "Cannot watch XC.IO:/Console"); 
}

len_t moduleFn(Resource_Console_isModified)(streamHandle handle){
	ERR(ERR.INVALID, "Cannot watch XC.IO:/Console"); 
	return 0;
}

len_t moduleFn(Resource_Console_shift)(streamHandle handle, word offset, len_t from){
	ERR(ERR.INVALID, "Cannot shift XC.IO:/Console"); 
	return 0;
}

len_t moduleFn(Resource_Console_readFrom)(streamHandle handle, void* buffer, len_t size){
	if(!ConsoleInfo.console) mod(Resource_Console_sync)(handle);

return WinLib.Console.readIn(ConsoleInfo.console, buffer, size);
}

len_t moduleFn(Resource_Console_writeTo)(streamHandle handle, const void* buffer, len_t size){
	if(!ConsoleInfo.console) mod(Resource_Console_sync)(handle);

return WinLib.Console.writeOut(ConsoleInfo.console, buffer, size);
}

streamInfo moduleFn(Resource_Console_info)(streamHandle handle){
return (streamInfo){
.name 		= "Console",
.path 		= "Console",
.attributes 	= core.Device.Stream.Attrib.READ,
.type 		= nil,
.currentPos    	= 0,
.time_created  	= 0,
.time_modified 	= 0,
.size 		= 0,
.valid 		= true
};
}

errvt moduleFn(Resource_Console_control)(streamHandle handle, word command, void* args){ return OK; }
errvt moduleFn(Resource_Console_flush)(streamHandle handle){ return OK; }
errvt moduleFn(Resource_Console_sync)(streamHandle handle){ 

}
