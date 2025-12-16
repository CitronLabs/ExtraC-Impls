#pragma once
#include "Resource/pkg.c"	

#define module env, Common, Devices, Manager

export(
SUBMODULE(Resource),
VALUES(),
	getOne, getAll, add, find, 
	remove, isConnected, disconnect, 
	grab, release);


#undef module
