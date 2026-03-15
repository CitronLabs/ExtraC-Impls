#include "../../../Devices.h"
#define module env, Devices, XC, Filesys, Filesys, Interface

Device_Filesys Filesys  = {
.info = {
    .valid 		= true,
    .name 		= "Python_XC_Storage_Filesys",
    .vendorName 	= "CitronLabs",
    .productName  	= "Python_XC_Storage_Filesys_Interface",
    .path		= "XC.Storage.Filesys",
}};

devHandle moduleFn(getHandle)(strc8 override){
	static devHandle FilesysHandle = nil;
	
	if(override)
		return sys.Device.fetch("XC.Filesys", override);

	elif(FilesysHandle is nil){

		FilesysHandle = sys.Device.init("XC.Filesys", "Python_XC_Filesys", env.Devices.XC.Interface);

		if(FilesysHandle is nil){
			ERR(ERR.FAIL, "Failed to initialize XC.Filesys[Python_XC_Filesys] device");
			return nil;
		}
	}

return FilesysHandle;
};

pntr moduleFn(Interface_init)(devHandle handle){

	errvt errval = OK;

    // Initialize resources
	
    // --- Calling Directory ---
	Filesys.standard_dirs.calling = sys.Stream.open(
		handle,
		"Calling:",
		StrmAttrib.READ | StrmAttrib.WRITE,
		env.Devices.XC.Storage.Filesys.Dir
	); 
	check(){ 
		errval = ERR(ERR.FAIL, 
      		    "Failed to initialize XC.Storage.Filesys:Local "
	       	    "directory resource"
	        );
		goto fail; 
	};


    // --- App Directory ---
	Filesys.standard_dirs.app = sys.Stream.open(
		handle,
		"App:",
		StrmAttrib.READ | StrmAttrib.WRITE,
		env.Devices.XC.Storage.Filesys.Dir
	);
	check(){ 
		errval = ERR(ERR.FAIL, 
      		    "Failed to initialize XC.Storage.Filesys:Local "
	       	    "directory resource"
	        );
		goto fail; 
	};


    // --- Local Directory ---
	Filesys.standard_dirs.local = sys.Stream.open(
		handle,
		"Local:",
		StrmAttrib.READ | StrmAttrib.WRITE,
		env.Devices.XC.Storage.Filesys.Dir
	);
	check(){ 
		errval = ERR(ERR.FAIL, 
      		    "Failed to initialize XC.Storage.Filesys:Local "
	       	    "directory resource"
	        );
		goto fail; 
	};


    // --- Temp Directory ---
	Filesys.standard_dirs.temp = sys.Stream.open(
		handle,
		"Temp:",
		StrmAttrib.READ | StrmAttrib.WRITE,
		env.Devices.XC.Storage.Filesys.Dir
	);
	check(){ 
		errval = ERR(ERR.FAIL, 
      		    "Failed to initialize XC.Storage.Filesys:Local "
	       	    "directory resource"
	        );
		goto fail; 
	};


    // --- Capabilities ---
	Filesys.capabilities = sys.Register.open(
		handle,
		"Caps",
		RegAttrib.READ,
		env.Devices.XC.Storage.Filesys.Caps
	);
	check(){ 
		errval = ERR(ERR.FAIL, 
      		    "Failed to initialize XC.Storage.Filesys:Local "
	       	    "directory resource"
	        );
		goto fail; 
	};


    // --- Working Directory ---
	Filesys.workdir = sys.Register.open(
		handle,
		"WorkDir",
		RegAttrib.READ | RegAttrib.WRITE,
		env.Devices.XC.Storage.Filesys.WorkDir
	);
	check(){ 
		errval = ERR(ERR.FAIL, 
      		    "Failed to initialize XC.Storage.Filesys:Local "
	       	    "directory resource"
	        );
		goto fail; 
	};


    // --- Fail handling ---
	if(errval is_not OK){ fail:
	    if(Filesys.standard_dirs.local is_not nil)
		sys.Stream.close(Filesys.standard_dirs.local);
	    
	    if(Filesys.standard_dirs.calling is_not nil)
		sys.Stream.close(Filesys.standard_dirs.calling);

	    if(Filesys.standard_dirs.app is_not nil)
		sys.Stream.close(Filesys.standard_dirs.app);

	    if(Filesys.standard_dirs.temp is_not nil)
		sys.Stream.close(Filesys.standard_dirs.temp);

	    if(Filesys.capabilities is_not nil)
		sys.Register.close(Filesys.capabilities);
	   
	    if(Filesys.workdir is_not nil)
		sys.Register.close(Filesys.workdir);
	    
	    return nil;
	}

return &Filesys;
}

errvt moduleFn(Interface_close)(devHandle handle){

	errvt errval = OK;

	if(Filesys.standard_dirs.local is_not nil)
	    sys.Stream.close(Filesys.standard_dirs.local);
	    check(){
		errval = ERR(ERR.FAIL, 
      		    "Failed to close XC.Storage.Filesys:Local "
	       	    "directory resource"
	        );
	    }
	
	if(Filesys.standard_dirs.calling is_not nil)
	    sys.Stream.close(Filesys.standard_dirs.calling);
	    check(){
		errval = ERR(ERR.FAIL, 
      		    "Failed to close XC.Storage.Filesys:Calling "
	       	    "directory resource"
	        );
	    }

	if(Filesys.standard_dirs.app is_not nil)
	    sys.Stream.close(Filesys.standard_dirs.app);
	    check(){
		errval = ERR(ERR.FAIL, 
      		    "Failed to close XC.Storage.Filesys:App "
	       	    "directory resource"
	        );
	    }

	if(Filesys.standard_dirs.temp is_not nil)
	    sys.Stream.close(Filesys.standard_dirs.temp);
	    check(){
		errval = ERR(ERR.FAIL, 
      		    "Failed to close XC.Storage.Filesys:Temp "
	       	    "directory resource"
	        );
	    }

	if(Filesys.capabilities is_not nil)
	    sys.Register.close(Filesys.capabilities);
	    check(){
		errval = ERR(ERR.FAIL, 
      		    "Failed to close XC.Storage.Filesys:Caps "
	       	    "directory resource"
	        );
	    }
	
	if(Filesys.workdir is_not nil)
	    sys.Register.close(Filesys.workdir);
	    check(){
		errval = ERR(ERR.FAIL, 
      		    "Failed to close XC.Storage.Filesys:WorkDir "
	       	    "directory resource"
	        );
	    }
	
return errval;
}

errvt moduleFn(Interface_delete)(devHandle handle){
	return mod(Interface_close)(handle);
}

deviceInfo moduleFn(Interface_Info)(devHandle handle){ return Filesys.info; }

