#pragma once
#define __ENV_COMMON_POSIX__
#include "pkg.h"

#define package env_Common_Posix_IO

Class(File,
INIT(const char* path; 
     	struct {
	    u8 
     	    create : 1,
     	    read   : 1,
     	    write  : 1;
        } flags;
),
FMT(),
){
	interface(env_Common_Devices_Resource) 	Stream;
};

Class(Dir,
INIT(const char* path;
     	struct {
	    u8 
     	    create : 1,
     	    read   : 1,
     	    write  : 1;
        } flags;
),
FMT(),
){
	interface(env_Common_Devices_Resource) 	Stream;
};

#undef package
#define package env_Common_Posix_Thread

Class(Local,
INIT(),
FMT(),
){
	interface(env_Common_Devices_Resource) Register;

};


#undef package
#define package env_Common_Posix

Class(IO,
INIT(),
FMT(),
	deviceInfo info;      
){
	interface(env_Common_Posix_IO_File)	File;
	interface(env_Common_Posix_IO_Dir)	Dir;
	interface(env_Common_Device)   		Device;
};

Class(Thread,
INIT(),
FMT(),

){
    	interface(env_Common_Posix_Thread_Local) Local;

};

#undef package
