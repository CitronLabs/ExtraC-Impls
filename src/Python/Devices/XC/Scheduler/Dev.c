#include "../../Devices.h"
#define module env, Devices, XC, Scheduler, Interface


Device_Scheduler Scheduler = {
.info = {
    .valid 		= true,
    .name 		= "Python_XC_Scheduler",
    .vendorName 	= "Citronlabs",
    .productName  	= "Python_XC_Scheduler_Interface",
    .path		= "XC.Scheduler"
}
};
