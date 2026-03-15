#include "IO.h"

static struct IODevice {
	struct {
	    Console object;

    	    rsrcID ID,
    		stdErr,
          	stdOut,
          	stdIn;
	} console;
	struct {
	    rsrcID
		ID,
      		workDir;
	} filesys;
} IO;


static inline errvt moduleFn(initStdResources)(){
	var devManager = WinRT.Resource.getManager();
	var IO_DevID   = WinRT.IO.getID();
	

	// Console Setup (without Console/Terminal lazy loaded)

	if(!create(Console, &IO.console, .outBuffSize = 1024)){
		return ERR(ERR.INIT, "Failed to initialize XC.IO:/Console");
	}

	IO.console.ID = Dev.Resource.add(devManager, IO_DevID, Console_Info, &IO.console);

	if(IO.console.ID == -1)
		return ERR(ERR.INIT, "Failed to initialize XC.IO:/Console resource");

	IO.console.stdIn = Dev.Resource.add(devManager, IO_DevID, StdIn_Info, &IO.console);

	if(IO.console.stdIn == -1)
		return ERR(ERR.INIT, "Failed to initialize XC.IO:/Console/StdIn resource");

	IO.console.stdErr = Dev.Resource.add(devManager, IO_DevID, StdErr_Info, &IO.console);

	if(IO.console.stdErr == -1)
		return ERR(ERR.INIT, "Failed to initialize XC.IO:/Console/StdErr resource");

	IO.console.stdOut = Dev.Resource.add(devManager, IO_DevID, StdOut_Info, &IO.console);

	if(IO.console.stdOut == -1)
		return ERR(ERR.INIT, "Failed to initialize XC.IO:/Console/StdOut resource");



	// FileSys setup



	IO.filesys.workDir = Dev.Resource.add(devManager, IO_DevID, WorkDir_Info, &IO.console);

	if(IO.filesys.workDir == -1)
		return ERR(ERR.INIT, "Failed to initialize WorkDir resource");

return OK;
}

devID moduleFn(getID)(){
	static devID IOHandle = -1;
	
	if(IOHandle == -1){

		pntr IODevData = mod(Interface_open)(core.Device.Resource.Self, nil, 0, nil);

		if(IODevData == nil){
			ERR(ERR.INIT, "Failed to create XC.IO device");
			return -1;
		}
		
	    	IOHandle = Dev.add(WinRT.Resource.getManager(), IO_Info, WinRT.IO.Interface, IODevData);

		if(IOHandle == -1){
			ERR(ERR.INIT, "Failed to register XC.IO device");
			return -1;
		}

	}

return IOHandle;
};

pntr moduleFn(Interface_open)(word resource, const char* name, word attributes, void* type){
	nonull(name) return nil;

	switchV(resource){
	caseV(core.Device.Resource.Self){

		iferr(mod(initStdResources)()){
			ERR(ERR.INIT, "Failed to initliaze standard resources for the XC.IO device");
			return nil;
		}

		return &IO;
	}
	caseV(core.Device.Resource.Stream){ return mod(openStream)(name, attributes, type, true); }
	defaultV {
		ERR(ERR.INVALID, "Invalid resource type");
		return nil;
	}
	}

ERR(ERR.NOTIMPLEM, "unreachable code reached");
return nil;
}

errvt moduleFn(Interface_Close)(word resource, pntr handle){
	nonull(handle) return err;

	Manager* devManager 	= WinRT.Resource.getManager();
	devID 	 IO_DevID 	= WinRT.IO.getID();

	switchV(resource){
	caseV(core.Device.Resource.Device){

	    var IOEntry = Dev.getOne(devManager, IO_DevID);

	    loop(i, len(&IOEntry->resources))
	    	Dev.Resource.remove(devManager, IO_DevID, i);		
	    
	    return OK;
	}
	caseV(core.Device.Resource.Stream){ 
	    Dev.Resource.release(
	        devManager,
	        IO_DevID,
	        pntr_asVal(handle)
	    );

	    if(!Dev.Resource.usage(devManager, IO_DevID, pntr_asVal(handle)))
	    	Dev.Resource.remove(devManager, IO_DevID, pntr_asVal(handle));

	    return OK;
	}
	defaultV {
		return ERR(ERR.INVALID, "Invalid resource type");
	}
	}

return ERR(ERR.NOTIMPLEM, "unreachable code reached");
}

errvt moduleFn(Interface_Edit)(word resourceType, pntr handle, const char* name, word attributes){
	switchV(resourceType){
	caseV(core.Device.Resource.Device){
	   return ERR(ERR.INVALID, 
      	    	"XC.IO device is not"
      	    	"allowed to be edited"
      	    );
	}
	caseV(core.Device.Resource.Stream){
		var streamInfo = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		)->info;

		iferr(((stream_Interface*)streamInfo.interface)
			->edit(handle, name, attributes)
		){ return err; }

		return OK;
	}
	defaultV{
		return ERR(ERR.INVALID, "Invalid resource type");
	}
	}

return ERR(ERR.NOTIMPLEM, "unreachable code reached");
}

pntr moduleFn(Interface_Fetch)(word resourceType, const char* name, word attributes, void* type){
	switchV(resourceType){
	caseV(core.Device.Resource.Device){
	    ERR(ERR.INVALID, 
      	    	"XC.IO device does not "
      	    	"allow multiple handles "
      	    	"to itself to be opened"
      	    );
	    return nil;
	}
	caseV(core.Device.Resource.Stream){ return mod(openStream)(name, attributes, type, false); }
	defaultV{
		ERR(ERR.INVALID, "Invalid resource type");
		return nil;
	}
	}

ERR(ERR.NOTIMPLEM, "unreachable code reached");
return nil;
}
errvt moduleFn(Interface_Delete)(word resourceType, pntr handle){
	switchV(resourceType){
	caseV(core.Device.Resource.Device){
	   return ERR(ERR.INVALID, 
      	    	"XC.IO device is not"
      	    	"allowed to be deleted"
      	    );
	}
	caseV(core.Device.Resource.Stream){

		var stream = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.IO.getID(),
			(pntrval)handle
		);

		del(stream->data);

		return OK;
		

	}
	defaultV{
		return ERR(ERR.INVALID, "Invalid resource type");
	}
	}
return ERR(ERR.NOTIMPLEM, "unreachable code reached");
}

deviceInfo moduleFn(Interface_Info)(devHandle handle){

return Dev.getOne(WinRT.Resource.getManager(), WinRT.IO.getID())->info;
}

