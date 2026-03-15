#include "../Scheduler.h"


errvt moduleFn(Resource_Process_watch)(streamHandle handle){
}

len_t moduleFn(Resource_Process_isModified)(streamHandle handle){
}

len_t moduleFn(Resource_Process_shift)(streamHandle handle, word offset, len_t from){
}

len_t moduleFn(Resource_Process_readFrom)(streamHandle handle, void* buffer, len_t size){
}

len_t moduleFn(Resource_Process_writeTo)(streamHandle handle, const void* buffer, len_t size){
}

streamInfo moduleFn(Resource_Process_info)(streamHandle handle){
return (streamInfo){
.name 		= "Process",
.path 		= "Process",
.attributes 	= core.Device.Stream.Attrib.READ,
.type 		= nil,
.currentPos    	= 0,
.time_created  	= 0,
.time_modified 	= 0,
.size 		= 0,
.valid 		= true
};
}

errvt moduleFn(Resource_Process_control)(streamHandle handle, word command, void* args){ return OK; }
errvt moduleFn(Resource_Process_flush)(streamHandle handle){ }
errvt moduleFn(Resource_Process_sync)(streamHandle handle){}
