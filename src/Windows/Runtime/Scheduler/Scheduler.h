#include "../Runtime.h"
#define module env, Windows, Runtime, Scheduler


from(env_Windows_Lib, 
	Exec_Thread  as Thread,
);

static struct {
     struct {
        PTP_POOL 	    pool;
	PTP_CLEANUP_GROUP   cleanupGroup;
	TP_CALLBACK_ENVIRON callbackEnviron;
     } Thread;
} Scheduler;

static const deviceInfo 
IO_Info = {
.name 		= "Windows_XC_Scheduler",
.vendorName 	= "CitronLabs",
.productName  	= "Windows_XC_Scheduler_Interface",
.path		= "XC.Scheduler",
.attributes 	= DevAttrib.PRIVATE | DevAttrib.STREAM_CREATE,
.valid 		= true
};

