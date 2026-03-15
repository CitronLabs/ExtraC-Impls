#pragma once
#define __ENV_GODOT__
#include "../pkg.h"


#ifndef __ENV_GODOT_RUNTIME__
#define package env_Godot

Interface(Runtime,
	
	void fn(init)();
)

#undef package
#endif
