#pragma once
#define __ENV_COMMON_DEVICES__
#include "../pkg.h"
#include "../types.h"


#ifndef __ENV_COMMON_DEVICES_MANAGER__
#define package env_Common_Devices

Interface(Manager,
	errvt fn(init)(ifob(std_Allocator) allocator);

	pntr fn(getResource)(pntr handle);
/*
	pkg(Entry)* 	fn(getOne)(pkg(ID) id);
	errvt 	  	fn(getAll)(std_Array_Buffer* envDevices);
	pkg(ID) 	fn(add)(deviceInfo info, intf(device) type, void* data);

	pkg(ID) 	method(Manager, find, 		fmtStr name);
	errvt 	  	method(Manager, remove, 	pkg(ID) id);
	bool 	  	method(Manager, isConnected, 	pkg(ID) id);
	errvt 	  	method(Manager, disconnect, 	pkg(ID) id);
	errvt 	  	method(Manager, grab, 		pkg(ID) id);
	errvt 	  	method(Manager, release, 	pkg(ID) id);

  submodule(Resource,

	errvt 		method(Manager, grab, 	 pkg(ID) id, pkg(ResourceID) resource);
	errvt 		method(Manager, release, pkg(ID) id, pkg(ResourceID) resource);
	len_t 		method(Manager, usage,   pkg(ID) id, pkg(ResourceID) resource);

	pkg(ResourceID)	method(Manager, find, 	 pkg(ID) id, strc8 path);
	pkg(ResourceID)	method(Manager, add,     pkg(ID) id, pkg(ResourceInfo) info, void* data);
	pkg(Resource)* 	method(Manager, getOne,  pkg(ID) id, pkg(ResourceID) resource);

	errvt		method(Manager, remove,	 pkg(ID) id, pkg(ResourceID) resource);
  )
*/
);

#undef package
#endif
