#pragma once
#define __ENV_COMMON__
#include "../pkg.h"

#ifndef __ENV_COMMON_DEVICES__

#include "types.h"

#define package env_Common

Interface(Device,
	

)



Class(DevicesManager,
INIT(),
FMT(),


private(
	std_List  	registeredDevices;
      	std_Map 	pathResolve;

)
){
	ifob(env_Common_Device)* method(DevicesManager, getOne, 	env_Common_Devices_ID id);
	errvt 	  		 method(DevicesManager, getAll, 	std_Array_Buffer* envDevices);
	env_Common_Devices_ID 	 method(DevicesManager, add,   		ifob(env_Common_Device) data);

	env_Common_Devices_ID 	 method(DevicesManager, find, 		strc8 path);
	errvt 	  		 method(DevicesManager, remove, 	env_Common_Devices_ID id);
	bool 	  		 method(DevicesManager, isConnected, 	env_Common_Devices_ID id);
	errvt 	  		 method(DevicesManager, disconnect, 	env_Common_Devices_ID id);
	errvt 	  		 method(DevicesManager, grab, 		env_Common_Devices_ID id);
	errvt 	  		 method(DevicesManager, release, 	env_Common_Devices_ID id);

	submodule(Resource,
	   	values(Type, word,
	    		GENERIC,
			STREAM,
	    		REGISTER
	    	);

		env_Common_Devices_Resource_ID 
	  		method(DevicesManager, add,  	
				env_Common_Devices_ID id, word type,
				env_Common_Devices_ResourceData resource
		  	);

		intf(env_Common_Devices_Resource)
	  		method(DevicesManager, getInterface,  	
				env_Common_Devices_ID id, 
				env_Common_Devices_Resource_ID resource
		  	);

		errvt	method(DevicesManager, remove,
				env_Common_Devices_ID id, 
				env_Common_Devices_Resource_ID resource
			);
	)
      	
};

#undef package
#define package env_Common_Devices


#undef package
#endif



