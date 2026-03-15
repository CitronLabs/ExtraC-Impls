#define __PYTHON__
#define USE_PYTHON
#include <Env.pkg.c>
#include <XC.pkg.c>
#undef main

from(env_Common_Devices,
	ID 		as devID,
     	ResourceID 	as rsrcID,
	Entry 		as devEntry,
	ResourceInfo	as rsrcInfo,
	Resource	as rsrcEntry
)

alias(env.Python.Runtime,  	   PyRT)
alias(env.Common.Devices.Manager,  Dev)
alias(sys.Stream.Attrib,   	   StrmAttrib)
alias(sys.Register.Attrib, 	   RegAttrib)

alias(env.Python.Lib, py)

typedef struct {
    deviceInfo info;
    struct{ registerHandle handle; } implementation;
} Device_XC;


typedef struct {


} Device_IO;

typedef struct {


} Device_Console;






typedef struct {


} Device_Scheduler;

typedef struct {


} Device_Thread;







typedef struct {
    deviceInfo info;
} Device_Storage;

typedef struct {
    deviceInfo info;
    struct {
	streamHandle 
	    calling, app, 
	    local, temp;
    } standard_dirs;

    registerHandle capabilities, workdir;

} Device_Filesys;





typedef struct {
	deviceInfo info;
	struct {
	    registerHandle handle;
	} data;
} Device_Memory;

typedef struct {
	deviceInfo info;
} Device_MemLoader;

typedef struct {
	deviceInfo info;
} Device_MemMapper;
