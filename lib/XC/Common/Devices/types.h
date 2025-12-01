#pragma once
#define __XC_IMPL_COMMON_DEVICES__
#include "pkg.h"

#define package Common_Devices


typefrom(uword, ID);
typefrom(std_Object, Data);

type(Info,
	const c8
     	* name,
     	* vendorName,
     	* productName,
     	* serialCode,
     	* devPath;
)

Data(User,
INIT(strc8 name, path; void* additionalData),
FMT(),
     	Common_Devices_Info info;
	void* userInfo; 
);

Interface(Stream,
	errvt fn(open)();

)

Interface(Register,


)

#undef package
