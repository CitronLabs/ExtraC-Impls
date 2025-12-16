#pragma once
#define __ENV_COMMON_POSIX_THREAD__
#include "pkg.h"

#define package env_Common_Posix_Thread

Class(Local,
INIT(),
FMT(),
){
	interface(env_Common_Devices_Manager_Resource) Register;

};

#undef package
