#undef module
#include <XC/pkg.c>

import(std)
import(env)

enum {
	env_Common_Devices_Resouce_Type_GENERIC,
	env_Common_Devices_Resouce_Type_STREAM,
	env_Common_Devices_Resouce_Type_REGISTER
};


	#define module env, Common, Devices, Resource

	importFn(add, remove, getInterface);

	moduleValues(Type,
		.GENERIC  = env_Common_Devices_Resouce_Type_GENERIC,
		.REGISTER = env_Common_Devices_Resouce_Type_REGISTER,
		.STREAM   = env_Common_Devices_Resouce_Type_STREAM,
	);

	export(Type, add, remove, getInterface);

#else 

#endif
