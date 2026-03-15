#include "Runtime.h"
#define module env, Windows, Runtime, Resource

#define INIT_MEM_NUM_PAGES 5

alias(std.Memory.Allocator, Alloc)

static Manager 	  ResourceManager = {};
static std_Memory ResourceMemory  = {};


Manager* moduleFn(getManager)(){
return ResourceManager.__type == nil ? nil : &ResourceManager;
}


errvt moduleFn(init)(){
	
	SYSTEM_INFO si = {};

	GetSystemInfo(&si);


	ResourceMemory.pointer = VirtualAlloc(
		nil, 					//Address
		si.dwPageSize *	INIT_MEM_NUM_PAGES,	//Size, 
		MEM_COMMIT,				//AllocationType, 
		PAGE_READWRITE				//Protect
	);

	if(ResourceMemory.pointer == NULL)
		return ERR(ERR.FAIL, "Failed to allocate memory for initialization");
	
	
	var settings = Alloc.optimizeSettings(Alloc.Optimize.SIZE);

	iferr(Alloc.setup(&ResourceMemory, settings)) 
		return err; 

	if(nil == create(Manager, &ResourceManager, 
    		.allocator = with(&Alloc.Interface, &ResourceMemory)
    	))
		return ERR(ERR.INIT, "Failed to initialize runtime resource manager");
	
return OK;
}

