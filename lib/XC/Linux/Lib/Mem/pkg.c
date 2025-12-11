#include <XC/pkg.h>

#define module XC, Mem

moduleValues(Perms,
      	READ  , (1 << 0),
      	WRITE , (1 << 1),
      	EXEC  , (1 << 2),
);

importFn(alloc, getPageSize, dealloc, protect)


export(
SUBMODULE(),
VALUES(Perms),
	alloc, getPageSize, dealloc, protect);

#undef module
