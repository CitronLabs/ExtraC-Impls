#include <errno.h>
#include <stdarg.h>
#include <unistd.h>

#define __XC_ENV_LIB_XC_IMPLEM_LIBC__

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
		.userFlags = Linux.OS.Mem.Flag.READ | Linux.OS.Mem.Flag.WRITE,
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
	

}

errvt lin_Lib_XC_Mem_zero(void* ptr, len_t num_pages){


}

errvt lin_Lib_XC_Meme_syncCache(void* ptr, len_t size, word flags){


}
