#pragma once
#define __ENV_COMMON_DEVICES_MANAGER__
#include "../pkg.h"


#ifndef __ENV_COMMON_DEVICES_MANAGER_RESOURCE__
#define package env_Common_Devices_Manager

typefrom(word, Resource_ID);
typefrom(word, Stream_ID);
typefrom(word, Register_ID);

type(ResourceMethods, 
	word 		type;
	union {
	    struct {
		errvt fn(writeTo)();
		errvt fn(readFrom)();
	    } Stream;
	    struct {
		len_t fn(getSize)();
		errvt fn(getData)(void* to);
		errvt fn(setData)(void* to);
	    } Register;
	} interface;
)

Interface(Resource,
	const strc8 	name;

	errvt fn(onInit)(env_Common_Devices_ID device);
	errvt fn(onExit)(env_Common_Devices_ID device);

	env_Common_Devices_Manager_ResourceMethods interface;

)

typedef ifob(env_Common_Devices_Manager_Resource) env_Common_Devices_Manager_ResourceData;
asXCType(env_Common_Devices_Manager_ResourceData);

#undef package
#endif
