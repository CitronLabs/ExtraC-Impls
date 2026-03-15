#pragma once
#include <Env.pkg.h>

#include "Runtime/pkg.c"
#include "Devices/pkg.c"

#define module env, Python


moduleValues(Version,
	MAJOR, 0,
	MINOR, 1,
	PATCH, 0,
)

export(
SUBMODULE(),
VALUES(Version), 
)

#undef module
