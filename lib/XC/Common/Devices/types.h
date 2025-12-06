#pragma once
#define __ENV_COMMON_DEVICES__
#include "pkg.h"

#define package env_Common_Devices


typefrom(uword, ID);
typefrom(uword, Resource_ID);
typefrom(uword, Stream_ID);
typefrom(uword, Register_ID);

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


Interface(Resource,
	errvt fn(onInit)(env_Common_Devices_ID device);
	errvt fn(onExit)(env_Common_Devices_ID device);

	union {
	    struct {
		errvt fn(open)();
		errvt fn(writeTo)();
		errvt fn(readFrom)();
		errvt fn(close)();
	    } Stream;
	    struct {
		errvt fn(open)();
		errvt fn(writeTo)();
		errvt fn(readFrom)();
		errvt fn(close)();
	    } Register;
	} interface;
)

typedef ifob(env_Common_Devices_Resource) env_Common_Devices_ResourceData;
asXCType(env_Common_Devices_ResourceData);


#undef package
