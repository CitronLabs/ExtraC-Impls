#pragma once

#include <XC/pkg.h>
#include <Core/pkg.c>

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
SUBMODULE(),
VALUES(Version), 
)

#undef module

#undef module

