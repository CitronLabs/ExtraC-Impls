#pragma once
#define __ENV_COMMON_DEVICES__
#include "pkg.h"

#define package env_Common


Interface(Device,
	
)


#undef package

#define package env_Common_Devices


typefrom(word, ID);

#define DEVICE_ID_INVALID -1

type(Info,
	const c8
     	* name,
     	* vendorName,
     	* productName,
     	* serialCode,
     	* devPath;

     	len_t 
	    num_streams, 
	    num_registers, 
	    num_resources;
)




#undef package
