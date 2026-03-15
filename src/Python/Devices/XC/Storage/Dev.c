#include "../../Devices.h"
#define module env, Devices, XC, Storage, Interface

Device_Storage Storage  = {
.info = {
    .valid 		= true,
    .name 		= "Python_XC_Storage",
    .vendorName 	= "CitronLabs",
    .productName  	= "Python_XC_Storage_Interface",
    .path		= "XC.Storage",
}};

devHandle moduleFn(getHandle)(strc8 override){
	static devHandle StorageHandle = nil;
	
	if(override)
		return sys.Device.fetch("XC.Storage", override);

	elif(StorageHandle is nil){

		StorageHandle = sys.Device.init("XC.Storage", "Python_XC_Storage", env.Devices.XC.Interface);

		if(StorageHandle is nil){
			ERR(ERR.FAIL, "Failed to initialize XC.Storage[Python_XC_Storage] device");
			return nil;
		}
	}

return StorageHandle;
};

pntr moduleFn(Interface_init)(devHandle handle){

	errvt err = OK;

	// Initialize sub-devices
	var Filesys = env.Devices.XC.Storage.Filesys.getHandle(nil);
	
	if(not Filesys) 
	    err = ERR(ERR.FAIL, "Failed to initialize XC.Storage.Filesys device");

return err is OK ? &Storage : nil;
}

errvt moduleFn(Interface_close)(devHandle handle){

	errvt err = OK;

	// Initialize sub-devices
	var Filesys = env.Devices.XC.Storage.Filesys.getHandle(nil);
	
	iferr(sys.Device.close(Filesys))
	    err = ERR(ERR.FAIL, "Failed to initialize XC.Storage.Filesys device");

return err;
}

errvt moduleFn(Interface_delete)(devHandle handle){
	return mod(Interface_close)(handle);
}

deviceInfo moduleFn(Interface_Info)(devHandle handle){ return Storage.info; }

