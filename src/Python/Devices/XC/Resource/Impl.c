#include "../../Devices.h"
#define module env, Devices, XC, Implementation

typedef struct {
	u8 MAJOR;
	u8 MINOR;
	u8 MICRO;
	u8 RELEASE;
} Version;

alias(std.System.Capabilities, Caps)
alias(std.System.SettingID,    SettingID)


c8 	SystemName[64] = "Python";
c8 	ImplName[64]   = "CitronLabs.XC.Python";
Version SystemVersion  = {0}; // Loaded at runtime
Version ImplVersion    = {1,0,0,0xA};
u64 	CapsBitField   = 
		Caps.MODULE_LOADING |
		Caps.VIRTUAL_MEMORY |
		Caps.SHELL_ACCESS;



pntr moduleFn(open)(devHandle dev, strc8 name, word attributes, bool create){

	Device_XC* XC = dev;

	if(XC->implementation.handle is_not nil){
	    ERR(ERR.FAIL, "XC:Implementation resource can only be initialized once");
	    return nil;
	}

	if(attributes & RegAttrib.WRITE){
	    ERR(ERR.FAIL, "XC:Implementation is a read only resource");
	    return nil;
	}

	if(attributes & RegAttrib.DIRECT_ACCESS){
	    ERR(ERR.FAIL, "XC:Implementation resource direct access not allowed");
	    return nil;
	}

	SystemVersion.MAJOR   = (Py_Version & 0xFF'00'00'00) >> 24;
	SystemVersion.MINOR   = (Py_Version & 0x00'FF'00'00) >> 16;
	SystemVersion.MICRO   = (Py_Version & 0x00'00'FF'00) >> 8;
	SystemVersion.RELEASE = (Py_Version & 0x00'00'00'F0) >> 4;

	XC->info.num_registers++;
	XC->info.num_resources++;

return &XC->implementation;
}	

len_t moduleFn(readFrom)(registerHandle handle, const void* buffer, len_t settingID){
	if(buffer is nil) return ERR(ERR.FAIL, "buffer is nil");


	switchV(settingID){
	caseV(SettingID.IMPL_NAME){ 
	    copy(&ImplName, buffer); check(){
	    	ERR(ERR.FAIL, "Failed to copy Implementation name into buffer");
	    	return 0;
	    }

	    return settingID;
	}
	caseV(SettingID.IMPL_VERSION){ 
	    copy_use(u32_Type, &ImplVersion, buffer); check(){
	    	ERR(ERR.FAIL, "Failed to copy Implementation version into buffer");
	    	return 0;
	    }

	    return settingID;
	}
	caseV(SettingID.SYSTEM_NAME){ 
	    copy(&SystemName, buffer); check(){
	    	ERR(ERR.FAIL, "Failed to copy System name into buffer");
	    	return 0;
	    }

	    return settingID;
	}
	caseV(SettingID.SYSTEM_VERSION){ 
	    copy_use(u32_Type, &SystemVersion, buffer); check(){
	    	ERR(ERR.FAIL, "Failed to copy System version into buffer");
	    	return 0;
	    }

	    return settingID;
	}
	caseV(SettingID.CAPS_BITFIELD){ 
	    copy(&SystemName, buffer); check(){
	    	ERR(ERR.FAIL, "Failed to copy Capabilities bitfield into buffer");
	    	return 0;
	    }

	    return settingID;
	}
	}


ERR(ERR.FAIL, "Invalid settingID");
return 0;
}
registerInfo moduleFn(info)(registerHandle handle){
constexpr len_t regSize = 
		sizeof(SystemName) + 
		sizeof(SystemVersion) +
		sizeof(ImplName) +
		sizeof(ImplVersion) +
		sizeof(CapsBitField);

return (registerInfo){
	.name 		= "Implementation",
	.path 		= "XC:Implementation",
	.size 		= regSize,
	.attributes 	= RegAttrib.READ,
	.type 		= env.Devices.XC.Implementation.type,
	.valid 		= true
};
}

errvt moduleFn(close)(registerHandle handle){ return OK; }
errvt moduleFn(delete)(registerHandle handle){ return OK; }

errvt moduleFn(edit)(registerHandle handle, const char* name, word attributes){
return ERR(ERR.FAIL, "Runtime setting modification not allowed");
}
errvt moduleFn(watch)(registerHandle handle){
return ERR(ERR.FAIL, "Runtime setting modification not allowed, watching not implemented");
}
len_t moduleFn(isModified)(registerHandle handle){
ERR(ERR.FAIL, "Runtime setting modification not allowed, watching not implemented");
return 0;
}
len_t moduleFn(writeTo)(registerHandle handle, const void* buffer, len_t size){
return ERR(ERR.FAIL, "Runtime setting modification not allowed");
}
len_t moduleFn(setTo)(registerHandle handle, const void* buffer, len_t size){
return ERR(ERR.FAIL, "Runtime setting modification not allowed");
}
void* moduleFn(access)(registerHandle handle){
ERR(ERR.FAIL, "Direct access not allowed");
return nil;
}



