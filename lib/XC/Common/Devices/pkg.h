#pragma once
#define __XC_IMPL_COMMON__
#include "../pkg.h"

#ifndef __XC_IMPL_COMMON_DEVICES__

#include "types.h"

#define package Common

Class(Devices,
INIT(),
FMT(),


private(
	std_ArrayList  registeredDevices;
	std_ArrayStack freedDevices;

)
){
	Common_Devices_Data*	method(Devices, getOne, 	Common_Devices_ID id);
	errvt 	  		method(Devices, getAll, 	std_ArrayBuffer* envDevices);
	Common_Devices_ID 	method(Devices, add,    	
			   		Common_Devices_Data* data, 
			   		Array(ifob(Common_Devices_Stream)) streams,
			   		Array(ifob(Common_Devices_Register)) registers
			   	);

	Common_Devices_ID 	method(Devices, find, 		strc8 path);
	errvt 	  		method(Devices, remove, 	Common_Devices_ID id);
	bool 	  		method(Devices, isConnected, 	Common_Devices_ID id);
	errvt 	  		method(Devices, disconnect, 	Common_Devices_ID id);
	errvt 	  		method(Devices, grab, 		Common_Devices_ID id);
	errvt 	  		method(Devices, release, 	Common_Devices_ID id);

	errvt 			method(Devices, addStreams,   	Common_Devices_ID id, Array(ifob(Common_Devices_Stream)) streams);
	errvt 			method(Devices, addRegisters,   Common_Devices_ID id, Array(ifob(Common_Devices_Register)) registers);
      	
};

#undef package
#endif



