#define module XC, Dev

enum{
	XC_Dev_Attrib_PRIVATE = 0,
	XC_Dev_Attrib_PUBLIC  = 1,
};


enum{
	XC_Dev_ID_IO,
	XC_Dev_ID_Local,
	XC_Dev_ID_Sys,
};

#ifdef __PKG
	#include "Stream.c"
	#include "Register.c"

	#define module XC, Dev

	import(XC)	

	moduleValues(Attrib,
	      	.PUBLIC  = XC_Dev_Attrib_PUBLIC,
	      	.PRIVATE = XC_Dev_Attrib_PRIVATE
	);

	moduleValues(ID,
	      	.IO    = XC_Dev_ID_IO,
	      	.Local = XC_Dev_ID_Local,
	      	.Sys   = XC_Dev_ID_Sys
	);

	importFn(open, fetch, stdHandle)

	export(Attrib, ID, Stream, open, fetch, stdHandle);

#else
#include "../../pkg.h"

import(env)
import(XC)
import(std)

from(env_Common,
	Devices_ID as devID
)

devHandle moduleFn(open)(const char* name, word attributes){
ERR(ERR_NOTIMPLEM, 
	"This feature is not currently avalible in "
	"this version of the Linux XC Implementation"
);

return NULL;
}
devHandle moduleFn(fetch)(const char* name){
ERR(ERR_NOTIMPLEM, 
	"This feature is not currently avalible in "
	"this version of the Linux XC Implementation"
);

return NULL;
}

devHandle moduleFn(stdHandle)(word id){

	switch(id){
	case XC_Dev_ID_IO:{
		return (devHandle)(len_t)env.Linux.Runtime.Devices.getIO();
	break;}
	case XC_Dev_ID_Local:{
		return (devHandle)(len_t)env.Linux.Runtime.Devices.getLocal();
	break;}
	case XC_Dev_ID_Sys:{
		return (devHandle)(len_t)env.Linux.Runtime.Devices.getSys();
	break;}
	default: {
		ERR(ERR_INVALID, "invalid std device handle id");
		return NULL;
	}
	}
}

#endif
#undef module
