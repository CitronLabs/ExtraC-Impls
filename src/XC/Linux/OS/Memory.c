#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <XC/pkg.c>

from(env_Linux_OS,
	use(Memory)
)

#define module env, Linux, OS, Memory

errvt moduleMethod(Memory, open, std_FSPath memObjPath){
	nonull(memObjPath){ return err; }

	priv.fd = shm_open(memObjPath, O_RDWR, 0666);
	
	if(priv.fd == -1)
		return ERR(ERR.FAIL, "failed to open memory object");

return OK;
}

errvt moduleMethod(Memory, setProt, u16 flags){
	nonull(self){ return err; }

	int prot = 0;

	if (flags & env.Linux.OS.Mem.Flag.READ)    { prot |= PROT_READ;  }
	if (flags & env.Linux.OS.Mem.Flag.WRITE)   { prot |= PROT_WRITE; }
	if (flags & env.Linux.OS.Mem.Flag.EXECUTE) { prot |= PROT_EXEC;  }

	if(this.address){
	    if(mprotect(this.address, priv.size, priv.prot) == -1)
		return ERR(ERR.FAIL, "failed to set memory");
	}

	priv.prot = prot;
	
return OK;
}

errvt moduleMethod(Memory, setSwappable, bool swappable){
	nonull(self){ return err; }
	
	if(this.address == nil)
		return ERR(ERR.INVALID, "memory not committed yet");

	if(swappable){
		if(munlock(this.address, priv.size) == -1)
			return ERR(ERR.FAIL, "failed to set memory to swappable");
	}else{ 
		if(mlock(this.address, priv.size) == -1)
			return ERR(ERR.FAIL, "failed to unset memory to swappable");
	}
	
return OK;
}

errvt moduleMethod(Memory, commit){
	nonull(self){ return err; }
	
	this.address = mmap(
		this.address,
		priv.size,
		priv.prot,
		priv.memFlags,
		priv.fd, 0
	);

	if (this.address == MAP_FAILED) {
		this.address = nil;
	    	return ERR(ERR.FAIL, "failed to map memory");
	}

return OK;
}

DESTROY(Memory){
	nonull(self){ return err; }

	if(this.address)
	    if (munmap(this.address, priv.size) == -1) 
	    	return ERR(ERR.FAIL, "failed to unmap memory");

return OK;
}

SIZE(Memory){
	nonull(self){ return 0; }
return elements ? priv.size : priv.size & XC.Mem.getPageSize();
}

SET(Memory){
	nonull(self){ return err; }

return env.Linux.OS.Mem.setProt(self, *(u16*)value);
}

construct(env_Linux_OS_Memory,
FMT(),
DEF(
.size = 1, 
.flags = XC_Mem_Perms_READ | XC_Mem_Perms_WRITE
),
	.Create  = env_Linux_OS_Memory_Op_Create,
	.Destroy = env_Linux_OS_Memory_Op_Destroy,
	.Set 	 = env_Linux_OS_Memory_Op_Set,
	.Size 	 = env_Linux_OS_Memory_Op_Size
){
	if (arg.flags & env.Linux.OS.Mem.Flag.READ)    { priv.prot |= PROT_READ;  }
	if (arg.flags & env.Linux.OS.Mem.Flag.WRITE)   { priv.prot |= PROT_WRITE; }
	if (arg.flags & env.Linux.OS.Mem.Flag.EXECUTE) { priv.prot |= PROT_EXEC;  }

	priv.size = size / XC.Mem.getPageSize();
	
	if(size % XC.Mem.getPageSize()){
		priv.size++;
	}

	if(getbitflag(arg.flags, env.Linux.OS.Mem.Flag.SHARE)){
		nonull(arg.atAddress){ return nil; }
		
		priv.memFlags = MAP_SHARED;

		priv.fd = shm_open(arg.atAddress, O_CREAT | O_RDWR, 0666);

		if(priv.fd == -1){
			ERR(ERR.FAIL, "failed to create shared memory");
			return nil;
		}
	
		ftruncate(priv.fd, priv.size);
	}else{
		priv.memFlags = MAP_PRIVATE | MAP_ANONYMOUS;

		if (arg.atAddress) 
		    	priv.memFlags |= MAP_FIXED;
		

		this.address = arg.atAddress;

		priv.fd = -1;
	}
	
	if(getbitflag(arg.flags, env.Linux.OS.Mem.Flag.COMMIT)){
		this.address = mmap(
			getbitflag(arg.flags, env.Linux.OS.Mem.Flag.SHARE) ? NULL : arg.atAddress,
			arg.size,
			priv.prot,
			priv.memFlags,
			priv.fd, 0
		);

		if (this.address == MAP_FAILED) 
			this.address = nil;
		    	ERR(ERR.FAIL, "failed to map memory");
	}

return self;
}
