#include "../Runtime.h"
#define module env, Windows, Runtime, Scheduler


from(env_Windows_Lib, 
	Exec_Thread  as Thread,
);

static struct {

} Memory;

static const deviceInfo 
IO_Info = {
.name 		= "Windows_XC_Memory",
.vendorName 	= "CitronLabs",
.productName  	= "Windows_XC_Memory_Interface",
.path		= "XC.Memory",
.attributes 	= DevAttrib.PRIVATE | DevAttrib.REGISTER_CREATE,
.valid 		= true
};

