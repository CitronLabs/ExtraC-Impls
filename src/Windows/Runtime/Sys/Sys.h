#include "../Runtime.h"
#define module env, Windows, Runtime, Scheduler


from(env_Windows_Lib, 
	Exec_Thread  as Thread,
);

static struct {
	std_Map envVarLookup;
	rsrcID
       		cliargsID,
       		localeID;
} System = {};


static const deviceInfo 
SysDeviceInfo = {
	.name 		= "Windows_XC_Sys",
    	.vendorName 	= "CitronLabs",
    	.productName  	= "Windows_XC_Sys_Interface",
    	.path		= "XC.Sys",
    	.attributes 	= DevAttrib.PRIVATE 		| 
			  DevAttrib.STREAM_CREATE 	| 
			  DevAttrib.REGISTER_CREATE,
    	.valid 		= true
};

static const rsrcInfo 
Shell_Info = {
.name 		= "Shell",
.path 		= "Shell",
.interface 	= &WinRT.Sys.Resource.Locale,
.type 		= system.Device.Resource.Stream,
.attributes 	= StrmAttrib.WRITE | StrmAttrib.READ 
},
CliArgs_Info = {
.name 		= "CliArgs",
.path 		= "CliArgs",
.interface 	= &WinRT.Sys.Resource.Locale,
.type 		= system.Device.Resource.Register,
.attributes 	= RegAttrib.READ | RegAttrib.DIRECT_ACCESS 
},
Locale_Info = {
.name 		= "Locale",
.path 		= "Locale",
.interface 	= &WinRT.Sys.Resource.CliArgs,
.type 		= system.Device.Resource.Register,
.attributes 	= RegAttrib.READ | RegAttrib.WRITE 
};
