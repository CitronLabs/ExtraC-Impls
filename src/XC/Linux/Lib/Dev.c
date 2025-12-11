#pragma once
#include <Core/pkg.c>
#include <XC/pkg.c>

#define module XC, Dev

moduleValues(Attrib,
	      	PRIVATE,,
	      	PUBLIC,,
	);

moduleValues(ID,
     		IO,,
	      	Local,,
	      	Sys,,   
	);

#ifdef __PKG
	#include "Stream.c"
	#include "Register.c"

	#define module XC, Dev



	importFn(open, fetch, stdHandle)

	export(Attrib, ID, Stream, open, fetch, stdHandle);

#else


from(env_Common,
	Devices_ID as devID
)

devHandle moduleFn(open)(const char* name, word attributes){
ERR(ERR_NOTIMPLEM, 
	"This feature is not currently avalible in "
	"this version of the Linux XC Implementation"
);

return nil;
}
devHandle moduleFn(fetch)(const char* name){
ERR(ERR_NOTIMPLEM, 
	"This feature is not currently avalible in "
	"this version of the Linux XC Implementation"
);

return nil;
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
		return nil;
	}
	}
}

#endif
#undef module
