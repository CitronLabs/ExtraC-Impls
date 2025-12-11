#pragma once
#include <Core/pkg.h>
#include "Dev/pkg.c"
#include "Mem/pkg.c"
#include "Sys/pkg.c"

#define module XC

moduleValues(Version,
	MAJOR, 0,
	MINOR, 1,
	PATCH, 0,
);


exportModule(
SUBMODULE(Dev, Mem, Sys),
VALUES(),
);

#undef module

