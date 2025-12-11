#pragma once
#include <XC/pkg.h>

#define module env, Linux, OS, Mem

moduleValues(Flag,
	READ,    (1 << 0),
	WRITE,   (1 << 1),
	EXECUTE, (1 << 2),
	COMMIT,  (1 << 3),
	SHARE, 	 (1 << 4),
)

export(
SUBMODULE(), 
VALUES(Flag), 
	open, setProt, setSwappable, commit
)

#undef module
