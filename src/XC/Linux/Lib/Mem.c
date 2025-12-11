#pragma once
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#undef std 

#include <Core/pkg.c>
#include <XC/pkg.c>

#define module XC, Mem

from(env_Linux_OS, 
     use(Memory)
)

void* moduleFn(alloc)(len_t num_pages){
	Memory mem = {0};

	create(Memory, &mem, 
		.size = num_pages * XC.Mem.getPageSize()
	);
	
	if(mem.address == nil){
		ERR(ERR.FAIL, "failed to allocate memory");
		return nil;
	}

	iferr(env.Linux.OS.Mem.commit(&mem)){
		
	}

return mem.address;
}


errvt moduleFn(dealloc)(void* ptr, len_t num_pages){
	Memory mem = {
		.address = ptr,
		.userFlags = 0,
		.__private.size = num_pages * XC.Mem.getPageSize()
	};

return pop(&mem);
}

len_t moduleFn(getPageSize)(){
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

errvt moduleFn(protect)(
	void* ptr, 
	len_t num_pages, 
	errvt fn(fault_callback)(void*, len_t), 
	word permissions
){
	Memory mem = {
		.address = ptr,
		.userFlags = 0,
		.__private.size = num_pages
	};
	
	if(permissions & XC.Mem.Perms.READ)  mem.__private.prot |= env.Linux.OS.Mem.Flag.READ;
	if(permissions & XC.Mem.Perms.WRITE) mem.__private.prot |= env.Linux.OS.Mem.Flag.WRITE;
	if(permissions & XC.Mem.Perms.EXEC)  mem.__private.prot |= env.Linux.OS.Mem.Flag.EXECUTE;

return env.Linux.OS.Mem.setProt(&mem, mem.__private.prot);
}

