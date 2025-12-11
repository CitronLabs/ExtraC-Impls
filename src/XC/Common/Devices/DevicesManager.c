#include <XC/pkg.c>
#define module env, Common, Devices

from(env_Common, 
    use(DevicesManager),
    Devices_ID      	as devID,
);

from(std,
	use(Map),
	use(String),
	use(List),
);


typedef struct {
	List resources;
	len_t numReferences;
	ubyte isConnected : 1;
	
	ifob(env_Common_Device) data;
} Device;

defTypeID(env_Common_Device_ID);
defTypeID(env_Common_Device_Data);

ifob(env_Common_Device)* moduleMethod(DevicesManager, getOne, devID id){
	nonull(self){ return nil; }
	if(!id)	    { nullerr(id); return nil; }

	Device* dev = index(&priv.registeredDevices, id);
	
	if(!dev){
		ERR(ERR.FAIL, "failed to find device from the device ID");
		return nil;
	}

return generic &dev->data;
}

errvt moduleMethod(DevicesManager, getAll, std_Array_Buffer* envDevices){
	nonull(self, envDevices){ return err; }

	foreach(&priv.registeredDevices, Device, dev)
		write(envDevices, &dev->data);
	
return OK;
}

devID   moduleMethod(DevicesManager, add, ifob(env_Common_Device) data){
	
	Device dev = {
		.isConnected = true,
	};

	memcpy(&data, &dev.data, sizeof(ifob(env_Common_Device)));

	devID result = std.List.FillSlot(&priv.registeredDevices, &dev);

return result;
}

devID moduleMethod(DevicesManager, find, strc8 path){
	nonull(path){ return -1; }

	devID* result = std.Map.Search(
		&priv.pathResolve, 
		asString(path, sizeof(std_FSPath))
	);

	if(result == nil){
		return -1;
	}

return *result;
}
errvt moduleMethod(DevicesManager, remove, devID id)
	{ return std.List.SetFree(&priv.registeredDevices, id); }

bool  moduleMethod(DevicesManager, isConnected, devID id)
	{ return ((Device*)index(&priv.registeredDevices, id))->isConnected;}

errvt moduleMethod(DevicesManager, disconnect, devID id){
	nonull(self){ return err; }
	if(!id)	    { return nullerr(id); }

	Device* dev = index(&priv.registeredDevices, id);
	
	if(!dev)
		return ERR(ERR.FAIL, "failed to find device from the device ID");
	
	
	dev->isConnected = false;

return OK;
}
errvt moduleMethod(DevicesManager, grab, devID id){
	nonull(self){ return err; }
	if(!id)	    { return nullerr(id); }


	Device* dev = index(&priv.registeredDevices, id);
	
	if(!dev)
		return ERR(ERR.FAIL, "failed to find device from the device ID");
	
	
	dev->numReferences++;
return OK;
}
errvt moduleMethod(DevicesManager, release, devID id){
	nonull(self){ return err; }
	if(!id)	    { return nullerr(id); }

	Device* dev = index(&priv.registeredDevices, id);
	
	if(!dev)
		return ERR(ERR.FAIL, "failed to find device from the device ID");
	
	
	dev->numReferences--;
return OK;
}

errvt moduleMethod(DevicesManager, addResource, 
	devID id, 
	ifob(env_Common_Devices_Resource) resource
){
	nonull(self, resource.interface, resource.object){ return err; }
	if(!id)	    { return nullerr(id); }

	Device* dev = index(&priv.registeredDevices, id);
	
	if(!dev)
		return ERR(ERR.FAIL, "failed to find device from the device ID");
	
	if(dev->resources.__type)
		if(create(List, &dev->resources,
			.type = cT(ifob(env_Common_Devices_Resource))
	    	) == nil)
			return ERR(ERR.INIT, "failed to initalize device resources list");
	
	if(!write(&dev->resources, &resource)){
		return ERR(ERR.FAIL, "failed to add resources to device");
	}

return OK;
}


errvt moduleMethod(DevicesManager, removeResource, 
	devID id, 
	env_Common_Devices_Resource_ID resource
){
	nonull(self)		{ return err; }
	if(!id || !resource)    { return nullerr(id); }

	Device* dev = index(&priv.registeredDevices, id);
	
	if(!dev)
		return ERR(ERR.FAIL, "failed to find device from the device ID");
	
	if(dev->resources.__type)
		if(create(List, &dev->resources,
			.type = cT(ifob(env_Common_Devices_Resource))
	    	) == nil)
			return ERR(ERR.INIT, "failed to initalize device resources list");
	
	if(!write(&dev->resources, &resource)){
		return ERR(ERR.FAIL, "failed to add resources to device");
	}

return OK;
}
	
construct(env_Common_DevicesManager,
FMT(),
DEF(),
	
){
	create(List, &priv.registeredDevices,
		.type 	   = cT(Device),
		.init_size = 10
	);


	create(Map, &priv.pathResolve,
		.key  		= T(String),
		.data 	 	= T(devID),
		.init_size 	= 5
	);

return self;
};


