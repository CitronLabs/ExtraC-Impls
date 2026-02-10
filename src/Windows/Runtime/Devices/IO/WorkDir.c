#include "../Device.h"

static struct { WCHAR path[MAX_PATH]; } WorkDir;

errvt moduleFn(Resource_WorkDir_watch)(registerHandle handle){
	GetCurrentDirectoryW(MAX_PATH, WorkDir.path);
return OK;
}
len_t moduleFn(Resource_WorkDir_isModified)(registerHandle handle){
	WCHAR newPath[MAX_PATH] = {};
	bool result = true;
	
	GetCurrentDirectoryW(MAX_PATH, newPath);

return !strncmp((strc16)WorkDir.path, (strc16)newPath, MAX_PATH);
}

len_t moduleFn(Resource_WorkDir_readFrom)(registerHandle handle, const void* buffer, len_t size){
	nonull(buffer) return err;

	if(size > MAX_PATH) size = MAX_PATH;

	memcpy(generic buffer, WorkDir.path, size);

return size;
}
len_t moduleFn(Resource_WorkDir_writeTo)(registerHandle handle, const void* buffer, len_t size){
	nonull(buffer) return err;

	if(size > MAX_PATH) size = MAX_PATH;

	memcpy(WorkDir.path, generic buffer, size);

return size;
}
len_t moduleFn(Resource_WorkDir_setTo)(registerHandle handle, const void* buffer, len_t size){
	nonull(buffer) return err;

	if(size > MAX_PATH) size = MAX_PATH;

	memcpy(WorkDir.path, generic buffer, size);

return size;
}
void* moduleFn(Resource_WorkDir_access)(registerHandle handle){
	ERR(ERR.INVALID, "Direct access not allowed for XC.IO:/WorkDir"); 
return nil;
}

registerInfo moduleFn(Resource_WorkDir_info)(registerHandle handle){
return (registerInfo){
.name 		= "WorkDir",
.path 		= "XC.IO:/WorkDir",
.attributes 	= core.Device.Register.Attrib.READ | core.Device.Register.Attrib.WRITE,
.type 		= nil,
.time_created 	= 0,
.time_modified 	= 0,
.currentPos 	= 0,
.size 		= strnlen((strc16)WorkDir.path, MAX_PATH),
.valid 		= true
};
}
