#include <errno.h>
#include <stdarg.h>
#include <unistd.h>

#include "../pkg.h"

import(Linux)
import(XC)
import(std)

void* lin_Lib_XC_Mem_alloc(len_t num_pages){
	lin_Memory mem = {0};

	create(lin_Memory, &mem, 
		.size = num_pages * XC.Mem.getPageSize()
	);
	
	if(!mem.address){
		ERR(ERR_FAIL, "failed to allocate memory");
		return null;
	}

	iferr(Linux.OS.Mem.commit(&mem)){
		
	}

return mem.address;
}


errvt lin_Lib_XC_Mem_dealloc(void* ptr, len_t num_pages){
	lin_Memory mem = {
		.address = ptr,
		.userFlags = 0,
		.__private.size = num_pages * XC.Mem.getPageSize()
	};

return pop(&mem);
}

len_t lin_Lib_XC_Mem_getPageSize(){
	static len_t pageSize = 0;

	if(!pageSize){
		i32 result = -1;
		if((result = sysconf(_SC_PAGESIZE)) == -1) {
			switch (errno) {
		    
			};

			result = 0;
		}
		pageSize = (u32)result;
	}

return pageSize;
}
enum{
	lin_Lib_XC_Mem_Perms_READ  = (1 << 0),
	lin_Lib_XC_Mem_Perms_WRITE = (1 << 1),
	lin_Lib_XC_Mem_Perms_EXEC  = (1 << 2),
};

errvt lin_Lib_XC_Mem_protect(void* ptr, len_t num_pages, word permissions){
	lin_Memory mem = {
		.address = ptr,
		.userFlags = 0,
		.__private.size = num_pages
	};
	
	if(permissions & XC.Mem.Perms.READ)  mem.__private.prot |= Linux.OS.Mem.Flag.READ;
	if(permissions & XC.Mem.Perms.WRITE) mem.__private.prot |= Linux.OS.Mem.Flag.WRITE;
	if(permissions & XC.Mem.Perms.EXEC)  mem.__private.prot |= Linux.OS.Mem.Flag.EXECUTE;

return Linux.OS.Mem.setProt(&mem, mem.__private.prot);
}

