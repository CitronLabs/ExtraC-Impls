#include <stdlib.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <sys/stat.h>

#include "../../pkg.h"

import(std)

from(env_Linux_OS,
     use(Dynlib)
)

void* moduleMethod(Dynlib, findSymbol, strc8 symbol) {
	nonull(self){ return nil; }

	void* result = dlsym(priv.handle, symbol);
	
	if(!result)
		ERR(ERR_INVALID, "could not find symbol");

return result;    
}

DESTROY(Dynlib){
	nonull(self, return OK);

	if (dlclose(priv.handle) != 0) 
		return ERR(ERR_FAIL, "failed to close dynamic library");
return OK;
}


construct(env_Linux_OS_Dynlib,
FMT(), 
DEF(), 
){
	void* dynlib = dlopen(arg.path, RTLD_LAZY);

	if(!dynlib){
	    struct stat temp = {0};

	    if(stat(arg.path, &temp) == -1){
	    	ERR(ERR_INVALID, "invalid dynamic lib path");}
	    else
		ERR(ERR_FAIL, "failed to load dynamic lib");
	    
	    return nil;
	}

return self;
}
