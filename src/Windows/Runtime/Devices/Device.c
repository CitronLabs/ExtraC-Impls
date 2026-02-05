#include "Device.h"

errvt moduleFn(init)(){

	if(WinRTDev.getManager() == nil)
		return ERR(ERR.INIT, "Failed to initialize device manager");
	

	if(WinRTDev.getIO() == -1)
		return ERR(ERR.INIT, "Failed to initialize XC.IO device");


	if(WinRTDev.getSys() == -1)
		return ERR(ERR.INIT, "Failed to initialize XC.Sys device");

return OK;
};

devID moduleFn(getIO)(){
	static devID IOHandle = -1;
	
	if(IOHandle == -1){

		pntr IODevData = WinRTDev.IO.open(core.Device.Resource.Self, nil, 0, nil);

		if(IODevData == nil){
			ERR(ERR.INIT, "Failed to create XC.IO device");
			return -1;
		}
		
	    	IOHandle = Dev.add(WinRTDev.getManager(), IODeviceInfo, WinRTDev.IO, IODevData);

		if(IOHandle == -1){
			ERR(ERR.INIT, "Failed to register XC.IO device");
			return -1;
		}

	}

return IOHandle;
};

devID moduleFn(getSys)(){
	static devID SysHandle = -1;

	if(SysHandle == -1){

		pntr SysDevData = WinRTDev.Sys.open(core.Device.Resource.Self, nil, 0, nil);

		if(SysDevData == nil){
			ERR(ERR.INIT, "Failed to create XC.IO device");
			return -1;
		}

	    	SysHandle = Dev.add(WinRTDev.getManager(), SysDeviceInfo, WinRTDev.Sys, SysDevData);

		if(SysHandle == -1){
			ERR(ERR.INIT, "Failed to create XC.IO device");
			return -1;
		}
	}

return SysHandle;
};

Manager* moduleFn(getManager)(){
	static Manager* RTDev_Manager = nil;
	
	if(RTDev_Manager == nil){
		RTDev_Manager = new(Manager);

		if(RTDev_Manager == nil){
			ERR(ERR.INIT, "Failed to intialize device manager");
			return nil;
		}
	}

return RTDev_Manager;
};
