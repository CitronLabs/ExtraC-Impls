#include "../../pkg.h"
#include "Resource_pkg.c"	

#define module env, Common, Devices

import(std)
import(env)


importFn(
	getOne, getAll, add, find, 
	remove, isConnected, disconnect, 
	grab, release
);

export(
	Resource, getOne, getAll, add, find, 
	remove, isConnected, disconnect, 
	grab, release);

#undef module
