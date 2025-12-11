#pragma once
#include "./pkg.h"

#include "Common/pkg.c"
#include "Linux/pkg.c"
#include "Windows/pkg.c"


#define module env

exportModule(
SUBMODULE(Linux),
VALUES(), 
);

#undef module

