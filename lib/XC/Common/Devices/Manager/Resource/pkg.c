#pragma once
#include <XC/pkg.h>

#define module env, Common, Devices, Manager, Resource

moduleValues(Type,
	GENERIC,,  
	REGISTER,, 
	STREAM,,   
);

export(
SUBMODULE(),
VALUES(Type),
	add, remove, getInterface
);

#undef module


