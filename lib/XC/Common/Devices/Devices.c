#include "pkg.h"


import(std)
use(Common, 
    Devices_ID, 
    Devices_Data, 
    Devices_User
);


typedef struct {
	Devices_Data* info;
	std_ArrayList streams, registers;
	len_t numReferences;
	byte isConnected : 1;
	


} Registered_Device;





Devices_Data* methodimpl(Common_Devices, getOne, Devices_ID id);
errvt methodimpl(Common_Devices, getAll, std_ArrayBuffer* envDevices);




Devices_ID methodimpl(Common_Devices, add, 
	Devices_Data* data, 
	Array(ifob(Common_Stream)) streams,
	Array(ifob(Common_Register)) registers
){
	
	Devices_ID result;
	Registered_Device* dev_data;

	if(elements(&priv.freedDevices)){
		read(&priv.freedDevices, &result);

		dev_data = index(&priv.registeredDevices, result);

	} else {
		result = elements(&priv.registeredDevices);

		write(&priv.registeredDevices, &(Registered_Device){0});

		dev_data = index(&priv.registeredDevices, result);
	}

	dev_data->info = data;

	if(streams.data)
		copy(&streams, &priv.registeredDevices);
	

	if(registers.data)
		copy(&streams, &priv.registeredDevices);

return result;
}

Devices_ID methodimpl(Common_Devices, find, strc8 path){}
errvt methodimpl(Common_Devices, remove, Devices_ID id){}
bool methodimpl(Common_Devices, isConnected, Devices_ID id){}
errvt methodimpl(Common_Devices, disconnect, Devices_ID id){}
errvt methodimpl(Common_Devices, grab, Devices_ID id){}
errvt methodimpl(Common_Devices, release, Devices_ID id);

errvt methodimpl(Common_Devices, addStreams, Devices_ID id, Array(ifob(Common_Stream)) streams);
errvt methodimpl(Common_Devices, addRegisters, Devices_ID id, Array(ifob(Common_Register)) registers);
	
construct(Common_Devices,
FMT(),
DEF(),
	
){
	create(std_ArrayList, &priv.registeredDevices,
		.typeSize = sizeof(ifob(Common_Devices_Stream)),
		.initSize = 10
	);

	create(std_ArrayStack, &priv.freedDevices,
		.typeSize = sizeof(Devices_ID),
		.initSize = 5
	);
};

defTypeID(Common_Devices_ID);
defTypeID(Common_Devices_Data);
