#include "Sys.h"

static inline pntr moduleFn(Sys_Open_Register)(const char* name, word attributes, void* interface, bool create){

	var type = ((register_Interface*)interface)->type;

	if(
	   type != &system.Device.Register.Type.ENV_VAR || 
	   type != &system.Device.Register.Type.MODULE
	){
		ERR(ERR.FAIL, "Invalid stream type for XC.Sys device, can only ENV_VAR or MODULE");
		return nil;
	}

	var devManager     = WinRT.Resource.getManager();
	var IO_DevID       = WinRT.Sys.getID();
	rsrcID   result    = -1;
	rsrcID*  foundFile = std.Map.Search(&System.envVarLookup, asString(name, 255));

	if(foundFile){
		result = *foundFile;

		Dev.Resource.grab(devManager, IO_DevID, result);
	} else {

		rsrcInfo varInfo = {
			.attributes = attributes,
			.interface  = interface,
			.type 	    = Dev.Resource.Type.REGISTER
		};

		rsrcID varID = Dev.Resource.add(devManager, IO_DevID, varInfo);

		if(varID == -1 || Dev.Resource.init(devManager, IO_DevID, varID, create) != OK){
			ERR(ERR.FAIL, "Failed initialize file resource to IO device");
			return nil;
		}

		Dev.Resource.grab(devManager, IO_DevID, varID);

		result = varID;
	}
	
return (pntr)(pntrval)result;

}

static inline errvt moduleFn(Sys_InitStdResources)(){
	var devManager = WinRT.Resource.getManager();
	var Sys_DevID   = WinRT.Sys.getID();

	System.cliargsID = Dev.Resource.add(devManager, Sys_DevID, CliArgs_Info);

	if(System.cliargsID == -1)
		return ERR(ERR.INIT, "Failed to initialize CliArgs resource");

	System.localeID = Dev.Resource.add(devManager, Sys_DevID, Locale_Info);

	if(System.localeID == -1)
		return ERR(ERR.INIT, "Failed to initialize Locale resource");

return OK;
}

pntr moduleFn(Sys_Open)(word resource, const char* name, word attributes, void* type){
	nonull(name) return nil;
	
	Manager* devManager = WinRT.Resource.getManager();

	switchV(resource){
	caseV(system.Device.Resource.Device){

		if(create(std_Map, &System.envVarLookup,
			.key  = T(std_String),
	    		.data = T(rsrcID),
	 	) == nil){
			ERR(ERR.INIT, "Failed to create file cache for the XC.IO device");
			return nil;
		}
		
		iferr(mod(Sys_InitStdResources)()){
			ERR(ERR.INIT, "Failed to initliaze standard resources for the XC.IO device");
			return nil;
		}

		return &System;
	}
	caseV(system.Device.Resource.Register){ return mod(Sys_Open_EnvVar)(name, attributes, type, true); }
	defaultV{
		ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"of any streams by users"
		);
		return nil;

	}
	}

ERR(ERR.NOTIMPLEM, "unreachable code reached");
return nil;
}


errvt moduleFn(Sys_Close)(word resource, pntr handle){
	switchV(resource){
	caseV(system.Device.Resource.Device){
		return ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"itself by users"
		);
	}
	caseV(system.Device.Resource.Register){
		iferr(Dev.Resource.remove(
			WinRT.Resource.getManager(),
			WinRT.Sys.getID(),
			pntr_asVal(handle)
		)){
		    return ERR(ERR.FAIL, 
		 	"Failed to close the "
		 	"environment variable resource"
		    );
		}

		return OK;
	}
	defaultV{
		return ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"of any streams by users"
		);
	}
	}
return ERR(ERR.NOTIMPLEM, "unreachable code reached");
}

errvt moduleFn(Sys_Edit)(word resourceType, pntr handle, const char* name, word attributes){
	switchV(resourceType){
	caseV(system.Device.Resource.Device){
		return ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"itself by users"
		);
	}
	caseV(system.Device.Resource.Register){
		var streamInfo = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.Sys.getID(),
			(pntrval)handle
		)->info;

		iferr(((stream_Interface*)streamInfo.interface)
			->edit(handle, name, attributes)
		){ return err; }

		return OK;
	}
	defaultV{
		return ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"of any streams by users"
		);
	}
	}
return ERR(ERR.NOTIMPLEM, "unreachable code reached");
}

pntr moduleFn(Sys_Fetch)(word resourceType, const char* name, word attributes, void* type){
	switchV(resourceType){
	caseV(system.Device.Resource.Device){
	    ERR(ERR.INVALID, 
      	    	"XC.Sys device does not "
      	    	"allow multiple handles "
      	    	"to be opened"
      	    );
	    return nil;
	}
	caseV(system.Device.Resource.Register){ return mod(Sys_Open_EnvVar)(name, attributes, type, false); }
	defaultV{
		ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"of any streams by users"
		);
		return nil;
	}
	}
ERR(ERR.NOTIMPLEM, "unreachable code reached");
return nil;
}

errvt moduleFn(Sys_Delete)(word resourceType, pntr handle){
	switchV(resourceType){
	caseV(system.Device.Resource.Device){
		return ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"itself by users"
		);
	}
	caseV(system.Device.Resource.Register){
		var streamInfo = Dev.Resource.getOne(
			WinRT.Resource.getManager(),
			WinRT.Sys.getID(),
			(pntrval)handle
		)->info;

		iferr(((stream_Interface*)streamInfo.interface)
			->delete(handle)
		){ return err; }

		return OK;
	}
	defaultV{
		return ERR(ERR.INVALID, 
      			"XC.Sys device does not allow "
      			"creation, deletion, or modification "
      			"of any streams by users"
		);
	}
	}
return ERR(ERR.NOTIMPLEM, "unreachable code reached");
}

deviceInfo moduleFn(Sys_Info)(devHandle handle){
return Dev.getOne(WinRT.Resource.getManager(), WinRT.Sys.getID())->info;
}




