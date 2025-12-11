#pragma once

#include <XC/pkg.h>
#include <Core/pkg.h>

#include "OS/pkg.c"
#include "Runtime/pkg.c"
#include "Lib/pkg.c"

#include "./pkg.h"
#define module env, Linux


moduleValues(Version,
	MAJOR, 0,
	MINOR, 1,
	PATCH, 0,
)

export(
SUBMODULE(OS),
VALUES(Version), 
);


#undef module

