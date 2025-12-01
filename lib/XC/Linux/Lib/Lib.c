#include "Mem.c"

Impl(XC){
  .Mem = {
    .Perms = {
	.READ  = lin_Lib_XC_Mem_Perms_READ,
	.WRITE = lin_Lib_XC_Mem_Perms_WRITE,
	.EXEC  = lin_Lib_XC_Mem_Perms_EXEC,
    },
	.alloc = lin_Lib_XC_Mem_alloc,
	.dealloc = lin_Lib_XC_Mem_dealloc,
	.protect = lin_Lib_XC_Mem_protect,
	.getPageSize = lin_Lib_XC_Mem_getPageSize,
  },
  .Dev = {

  }


};
