#include "Runtime.h"
#define module env, Python, Runtime

#define LOGGER_TEMP 	true
#define LOGGER_FINAL 	false

#define INIT_MEM (2048 * 5)

static std_Memory Memory = {};
static std_Stream Logger = {};
static var 	  MemAlloc = with(&Alloc.Interface, &Memory);

errvt moduleFn(initMemory)(){

	Memory.pointer = malloc(INIT_MEM);

	if(Memory.pointer == NULL) return ({
		PyErr_SetString(PyExc_RuntimeError,  "Failed to allocate memory for initialization");
  		PyErr_Print();
  		ERR.FAIL;
	});
	
	
	var settings = Alloc.optimizeSettings(Alloc.Optimize.SIZE);

	iferr(Alloc.setup(&Memory, settings)) return ({
		PyErr_SetString(PyExc_RuntimeError, "Failed to setup allocator for resource memory");
  		PyErr_Print();
  		ERR.FAIL;
	});
	
return OK;
}

errvt moduleFn(initLogger)(bool temp){
	static std_Array_List* tempBuffer = nil;

	if(temp){ // Temp Logger setup
	    tempBuffer = new_use(std_Array_List, MemAlloc,
		.initSize 	= 1048,
		.typeSize 	= sizeof(byte),
		.allocator 	= MemAlloc
	    );

	    if(!tempBuffer) return ({
		PyErr_SetString(PyExc_RuntimeError, "Failed to setup temporary buffer for runtime error logging");
  		PyErr_Print();
  		ERR.FAIL;
	    });
	
	    if(!create_with(std_Stream, fromArray, &Logger, 
		.maxSize = (INIT_MEM / 2), 
		.array   = generic tempBuffer
		
	    )) return ({
		PyErr_SetString(PyExc_RuntimeError, "Failed to setup stream for runtime error logging");
  		PyErr_Print();
  		ERR.FAIL;
	    });

	    std.Error.SetLog(&Logger); // shouldnt fail

	} else { // Final Logger setup
	    pop(&Logger); del(tempBuffer);

	    var consoleErrHandle = sys.Stream.fetch(
		env.Devices.XC.IO.Console.getHandle(nil),
		"StdErr",
		StrmAttrib.WRITE
	    );

	    if(consoleErrHandle is nil) return ({
		PyErr_SetString(PyExc_RuntimeError, "Failed to fetch XC.IO.Console:StdErr stream for runtime error logging");
  		PyErr_Print();
  		ERR.FAIL;
	    });

	    if(!create_with(std_Stream, fromHandle, &Logger, consoleErrHandle)) return ({
		PyErr_SetString(PyExc_RuntimeError, "Failed to setup final stream for runtime error logging");
  		PyErr_Print();
  		ERR.FAIL;
	    });
	}

return OK;
}

void moduleFn(init)(){

	// Initialize runtime memory
	iferr(mod(initMemory)()){
		PyErr_SetString(PyExc_RuntimeError,  "Failed to initialize runtime memory");
  		PyErr_Print();
	}

	// Initialize temp error logger
	iferr(mod(initLogger)(LOGGER_TEMP)){
		PyErr_SetString(PyExc_RuntimeError,  "Failed to initialize temp runtime error logger");
  		PyErr_Print();
	}

	// Initialize the python interpreter
	py.init();

	// Initialize the device tree
	iferr(Dev.init(MemAlloc)){
	    ERR(ERR.INIT, "Failed to initialize runtime device tree manager");
	}
	
	// Initialize devices
	if(env.Devices.XC.getHandle(nil) is nil){
	    ERR(ERR.INIT, "Failed to initialize standard devices");
	    return;
	}

	// Initialize final error logger
	iferr(mod(initLogger)(LOGGER_FINAL)){
		PyErr_SetString(PyExc_RuntimeError,  "Failed to initialize final runtime error logger");
  		PyErr_Print();
	}

	errvt err = __MAIN_APP.start(args());

	if(err is_not OK){
	    ERR(ERR.FAIL, "Process exited with an error");
	}

exit(err);
}

int main(){
	env.Python.Runtime.init(); // Should never return
return EXIT_FAILURE;
}
