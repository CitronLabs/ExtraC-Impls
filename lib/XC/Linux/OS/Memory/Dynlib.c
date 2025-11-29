#include <stdlib.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <sys/stat.h>

#define __XC_ENV_LIB_XC_IMPLEM_LIBC__

#include "../../pkg.h"

import(std)


void* methodimpl(lin_Dynlib, findSymbol, strc8 symbol) {
	nonull(self, return null);

	void* result = dlsym(priv.handle, symbol);
	
	if(result == null)
		ERR(ERR_INVALID, "could not find symbol");

return result;    
}

DESTROY(lin_Dynlib){
	nonull(self, return null);

	if (dlclose(priv.handle) != 0) 
		return ERR(ERR_FAIL, "failed to close dynamic library");
return OK;
}


construct(lin_Dynlib,
FMT(), 
DEF(), 
){
	void* dynlib = dlopen(arg.path, RTLD_LAZY);

	if(dynlib == null){
	    struct stat temp;
	    if(stat(arg.path, &temp) == -1)
	    	ERR(ERR_INVALID, "invalid dynamic lib path");
	    else
		ERR(ERR_FAIL, "failed to load dynamic lib");
	}

return self;
}
