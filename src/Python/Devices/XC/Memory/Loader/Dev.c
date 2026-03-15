#include "../../../Devices.h"

Device_MemLoader Loader = {
.info = {
    .valid 		= true,
    .name 		= "Python_XC_Memory_Loader",
    .vendorName 	= "CitronLabs",
    .productName  	= "Python_XC_Memory_Loader_Interface",
    .path		= "XC.Memory.Loader",
}};

devHandle moduleFn(getHandle)(strc8 override){
	static devHandle XCHandle = nil;
	
	if(override)
		return sys.Device.fetch("XC", override);

	elif(XCHandle is nil){

		XCHandle = sys.Device.init("XC", "Python_XC", env.Devices.XC.Interface);

		if(XCHandle is nil){
			ERR(ERR.FAIL, "Failed to initialize XC[Python_XC] device");
			return nil;
		}
	}

return XCHandle;
};

pntr moduleFn(Interface_init)(devHandle handle){

	errvt err = OK;

	// Initialize Resources
	
	// Initialize sub-devices

return err is OK ? &Loader : nil;
}

errvt moduleFn(Interface_close)(devHandle handle){

	errvt err = OK;

	// Close Resources

	// Close sub-devices

return err;
}

errvt moduleFn(Interface_delete)(devHandle handle){
	return mod(Interface_close)(handle);
}

deviceInfo moduleFn(Interface_Info)(devHandle handle){ return Loader.info; }

