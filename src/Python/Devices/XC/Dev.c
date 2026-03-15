#include "../Devices.h"
#define module env, Devices, XC, Interface

Device_XC XC  = {
.info = {
    .valid 	  = true,
    .name 	  = "Python_XC",
    .vendorName   = "CitronLabs",
    .productName  = "Python_XC_Interface",
    .path	  = "XC",
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
	XC.implementation.handle = sys.Register.open(
		handle,
		"Implementation",
		RegAttrib.READ | RegAttrib.WRITE,
		env.Devices.XC.Implementation
	);
	
	// Initialize sub-devices
	var 
	    IO 	   	= env.Devices.XC.IO.getHandle(nil),
	    Memory 	= env.Devices.XC.Memory.getHandle(nil),
	    Scheduler 	= env.Devices.XC.Scheduler.getHandle(nil),
	    Storage 	= env.Devices.XC.Storage.getHandle(nil)
	;
	
	if(not IO) 
	    err = ERR(ERR.FAIL, "Failed to initialize XC.IO device");

	if(not Memory)
	    err = ERR(ERR.FAIL, "Failed to initialize XC.Memory device");

	if(not Scheduler)
	    err = ERR(ERR.FAIL, "Failed to initialize XC.Scheduler device");

	if(not Storage)
	    err = ERR(ERR.FAIL, "Failed to initialize XC.Storage device");

return err is OK ? &XC : nil;
}

errvt moduleFn(Interface_close)(devHandle handle){

	errvt err = OK;

	// Close Resources
	iferr(sys.Register.close(XC.implementation.handle))
		err = ERR(ERR.FAIL, "Failed to close XC:Implementation resource");

	// Close sub-devices
	var 
	    IO 	   	= env.Devices.XC.IO.getHandle(nil),
	    Memory 	= env.Devices.XC.Memory.getHandle(nil),
	    Scheduler 	= env.Devices.XC.Scheduler.getHandle(nil),
	    Storage 	= env.Devices.XC.Storage.getHandle(nil)
	;

	iferr(sys.Device.close(IO))
	    err = ERR(ERR.FAIL, "Failed to close XC.IO device");

	iferr(sys.Device.close(Memory))
	    err = ERR(ERR.FAIL, "Failed to close XC.Memory device");

	iferr(sys.Device.close(Scheduler))
	    err = ERR(ERR.FAIL, "Failed to close XC.Scheduler device");

	iferr(sys.Device.close(Storage))
	    err = ERR(ERR.FAIL, "Failed to close XC.Storage device");

return err;
}

errvt moduleFn(Interface_delete)(devHandle handle){
	return mod(Interface_close)(handle);
}

deviceInfo moduleFn(Interface_Info)(devHandle handle){ return XC.info; }

