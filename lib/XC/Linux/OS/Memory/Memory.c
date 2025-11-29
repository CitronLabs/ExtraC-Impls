#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define __XC_ENV_LIB_XC_IMPLEM_LIBC__

#include "../../pkg.h"

import(std)
import(XC)
import(Linux)

errvt methodimpl(lin_Memory, open, std_FSPath memObjPath){
	nonull(memObjPath, return null);

	priv.fd = shm_open(memObjPath, O_RDWR, 0666);
	
	if(priv.fd == -1)
		return ERR(ERR_FAIL, "failed to open memory object");

return OK;
}

errvt methodimpl(lin_Memory, setProt, u16 flags){
	nonull(self, return err);

	if (flags & Linux.OS.Mem.Flag.READ)    { priv.prot |= PROT_READ;  }
	if (flags & Linux.OS.Mem.Flag.WRITE)   { priv.prot |= PROT_WRITE; }
	if (flags & Linux.OS.Mem.Flag.EXECUTE) { priv.prot |= PROT_EXEC;  }

	if(this.address){
	    if(mprotect(this.address, priv.size, priv.prot) == -1)
		return ERR(ERR_FAIL, "failed to set memory");
	}
	
return OK;
}

errvt methodimpl(lin_Memory, setSwappable, bool swappable){
	nonull(self, return err);
	
	if(!this.address)
		return ERR(ERR_INVALID, "memory not committed yet");

	if(swappable){
		if(munlock(this.address, priv.size) == -1)
			return ERR(ERR_FAIL, "failed to set memory to swappable");
	}else{ 
		if(mlock(this.address, priv.size) == -1)
			return ERR(ERR_FAIL, "failed to unset memory to swappable");
	}
	
return OK;
}

errvt methodimpl(lin_Memory, commit){
	nonull(self, return err);
	
	this.address = mmap(
		this.address,
		priv.size,
		priv.prot,
		priv.memFlags,
		priv.fd, 0
	);

	if (this.address == MAP_FAILED) {
		this.address = null;
	    	return ERR(ERR_FAIL, "failed to map memory");
	}

return OK;
}

DESTROY(lin_Memory){
	nonull(self, return err);

	if(this.address)
	    if (munmap(this.address, priv.size) == -1) 
	    	return ERR(ERR_FAIL, "failed to unmap memory");

return OK;
}

SIZE(lin_Memory){
	nonull(self, return 0);
return elements ? priv.size : priv.size & XC.Mem.getPageSize();
}

SET(lin_Memory){
	nonull(self, return err);
	Linux.OS.Mem.setProt(self, *(u16*)value);
}

enum {
	MEM_READ 	= (1 << 0),
	MEM_WRITE	= (1 << 1),
	MEM_EXECUTE	= (1 << 2),
	MEM_SHARED	= (1 << 3),
	MEM_COMMIT	= (1 << 4),
};

construct(lin_Memory,
FMT(),
DEF(
.size = 1, 
.flags = MEM_READ | MEM_WRITE
),
	.Create = lin_Memory_Op_Create
){
	if (arg.flags & Linux.OS.Mem.Flag.READ)    { priv.prot |= PROT_READ;  }
	if (arg.flags & Linux.OS.Mem.Flag.WRITE)   { priv.prot |= PROT_WRITE; }
	if (arg.flags & Linux.OS.Mem.Flag.EXECUTE) { priv.prot |= PROT_EXEC;  }

	priv.size = size / XC.Mem.getPageSize();
	
	if(size % XC.Mem.getPageSize()){
		priv.size++;
	}

	if(getbitflag(arg.flags, Linux.OS.Mem.Flag.SHARE)){
		nonull(arg.atAddress, return nil);
		
		priv.memFlags = MAP_SHARED;

		priv.fd = shm_open(arg.atAddress, O_CREAT | O_RDWR, 0666);

		if(priv.fd == -1){
			ERR(ERR_FAIL, "failed to create shared memory");
			return null;
		}

		ftruncate(priv.fd, priv.size);
	}else{
		priv.memFlags = MAP_PRIVATE | MAP_ANONYMOUS;

		if (arg.atAddress) 
		    	priv.memFlags |= MAP_FIXED;
		

		this.address = arg.atAddress;

		priv.fd = -1;
	}
	
	if(getbitflag(arg.flags, Linux.OS.Mem.Flag.COMMIT)){
		this.address = mmap(
			getbitflag(arg.flags, Linux.OS.Mem.Flag.SHARE) ? null : arg.atAddress,
			arg.size,
			priv.prot,
			priv.memFlags,
			priv.fd, 0
		);

		if (this.address == MAP_FAILED) 
			this.address = null;
		    	ERR(ERR_FAIL, "failed to map memory");
	}

return OK;
}
