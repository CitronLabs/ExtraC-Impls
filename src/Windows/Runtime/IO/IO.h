#include "../Runtime.h"
#define module env, Windows, Runtime, IO

from(env_Windows_Lib, 
	FS_File as File,
	FS_Dir  as Dir,
     	use(Console)

);


static const deviceInfo 
IO_Info = {
.name 		= "Windows_XC_IO",
.vendorName 	= "CitronLabs",
.productName  	= "Windows_XC_IO_Interface",
.path		= "XC.IO",
.attributes 	= DevAttrib.PRIVATE 		| 
		  DevAttrib.STREAM_CREATE 	| 
		  DevAttrib.REGISTER_CREATE,
.valid 		= true
};

static const rsrcInfo 
Terminal_Info = {
.name 		= "Terminal",
.path 		= "Console/Terminal",
.interface 	= &WinRT.IO.Resource.Console,
.type 		= core.Device.Resource.Register,
.attributes 	= StrmAttrib.READ | StrmAttrib.READ
},
FileSys_Info = {
.name 		= "FileSys",
.path 		= "XC.IO.FileSys",
.interface 	= &WinRT.IO.Resource.Console,
.type 		= core.Device.Resource.Device,
.attributes 	= DevAttrib.PRIVATE | DevAttrib.STREAM_CREATE
},
Console_Info = {
.name 		= "Console",
.path 		= "Console",
.interface 	= &WinRT.IO.Resource.Console,
.type 		= core.Device.Resource.Stream,
.attributes 	= StrmAttrib.READ | StrmAttrib.WRITE
},
StdIn_Info = {
.name 		= "StdIn",
.path 		= "Console/StdIn",
.interface 	= &WinRT.IO.Resource.StdIn,
.type 		= core.Device.Resource.Stream,
.attributes 	= StrmAttrib.READ 
},
StdOut_Info = {
.name 		= "StdOut",
.path 		= "Console/StdOut",
.interface 	= &WinRT.IO.Resource.StdOut,
.type 		= core.Device.Resource.Stream,
.attributes 	= StrmAttrib.WRITE
},
StdErr_Info = {
.name 		= "StdErr",
.path 		= "Console/StdErr",
.interface 	= &WinRT.IO.Resource.StdErr,
.type 		= core.Device.Resource.Stream,
.attributes 	= StrmAttrib.WRITE
},
WorkDir_Info = {
.name 		= "WorkDir",
.path 		= "WorkDir",
.interface 	= &WinRT.IO.Resource.WorkDir,
.type 		= core.Device.Resource.Stream,
.attributes 	= RegAttrib.WRITE | RegAttrib.READ
};
