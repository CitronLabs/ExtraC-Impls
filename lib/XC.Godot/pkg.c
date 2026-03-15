#pragma once
#include <Env.pkg.h>

#define module env, Godot


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
