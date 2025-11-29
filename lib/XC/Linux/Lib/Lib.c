#include "../pkg.h"

#include "Mem.c"

Impl(XC){
  .Mem = {
    .Perms = {
	.READ  = lin_Lib_XC_Mem_Perms_READ,
	.WRITE = lin_Lib_XC_Mem_Perms_WRITE,
	.EXEC  = lin_Lib_XC_Mem_Perms_EXEC,
    },
	.alloc = lin_Lib_XC_Mem_alloc
  }


};
