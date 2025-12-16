#pragma once
#define __ENV_COMMON_DEVICES__
#include "../pkg.h"
#include "../types.h"


#ifndef __ENV_COMMON_DEVICES_MANAGER__
#include "Resource/pkg.h"

#define package env_Common_Devices


Class(Manager,
INIT(),
FMT(),


private(
	std_List  	registeredDevices;
      	std_Map 	pathResolve;

)
){
	ifob(env_Common_Device)* method(Manager, getOne, 	env_Common_Devices_ID id);
	errvt 	  		 method(Manager, getAll, 	std_Array_Buffer* envDevices);
	env_Common_Devices_ID 	 method(Manager, add,   	ifob(env_Common_Device) data);

	env_Common_Devices_ID 	 method(Manager, find, 		strc8 path);
	errvt 	  		 method(Manager, remove, 	env_Common_Devices_ID id);
	bool 	  		 method(Manager, isConnected, 	env_Common_Devices_ID id);
	errvt 	  		 method(Manager, disconnect, 	env_Common_Devices_ID id);
	errvt 	  		 method(Manager, grab, 		env_Common_Devices_ID id);
	errvt 	  		 method(Manager, release, 	env_Common_Devices_ID id);

	submodule(Resource,
	   	values(Type, word,
	    		GENERIC,
			STREAM,
	    		REGISTER
	    	);

		env_Common_Devices_Manager_Resource_ID 
	  		method(Manager, add,  	
				env_Common_Devices_ID id,
				env_Common_Devices_Manager_ResourceData resource
		  	);

		intf(env_Common_Devices_Manager_Resource)
	  		method(Manager, getInterface,  	
				env_Common_Devices_ID id, 
				env_Common_Devices_Manager_Resource_ID resource
		  	);

		errvt	method(Manager, remove,
				env_Common_Devices_ID id, 
				env_Common_Devices_Manager_Resource_ID resource
			);
	)
      	
};

#undef package
#endif
