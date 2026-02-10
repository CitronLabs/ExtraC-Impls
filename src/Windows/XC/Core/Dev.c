#include <XC.pkg.c>

#define module XC, Dev

from(env_Common,
	Devices_ID as devID
)

devHandle moduleFn(open)(const char* name, word attributes){
ERR(ERR.NOTIMPLEM, 
	"This feature is not currently avalible in "
	"this version of the Windows XC Implementation"
);

return nil;
}
devHandle moduleFn(fetch)(const char* name){
ERR(ERR.NOTIMPLEM, 
	"This feature is not currently avalible in "
	"this version of the Windows XC Implementation"
);

return nil;
}

devHandle moduleFn(stdHandle)(word id){

	switchV(id){
	caseV(core.Device.ID.IO){
		return (devHandle)(pntrval)env.Windows.Runtime.Device.getIO();
	break;}
	caseV(core.Device.ID.Sys){
		return (devHandle)(pntrval)env.Windows.Runtime.Device.getSys();
	break;}
	}

ERR(ERR.INVALID, "invalid std device handle id");
return nil;
}

