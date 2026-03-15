#define __ENV_COMMON_DEVICES__
#include "pkg.h"

#ifdef PKG_C
	#define module env, Devices

	#define DevTree(...) export(			\
	SUBMODULE(__VA_ARGS__),				\
	)


	#define stream(...)				\
	exportFrom(PATH(__VA_ARGS__),			\
	SUBMODULE(),					\
	VALUES(),					\
	    	open, close, delete, edit,		\
		writeTo, readFrom, watch,  shift, sync, \
		control, info, flush, isModified	\
	)
	
	#define register(...)				\
	exportFrom(PATH(__VA_ARGS__),			\
	SUBMODULE(),					\
	VALUES(),					\
	    	open, close, delete, edit,		\
		writeTo, readFrom, setTo, watch,  	\
		access, info, isModified		\
	)
	
	#define Device(device, ...)			\
	exportFrom(PATH(device, Interface),		\
	SUBMODULE(),					\
	VALUES(),					\
		init, info, close, delete 		\
	)						\
	exportFrom(PATH(device),			\
	SUBMODULE(Interface __VA_OPT__(, __VA_ARGS__)),, getHandle)
#else
	#define DevTree(...) typedef struct env_Devices_Interface {__VA_ARGS__} env_Devices_Interface;
	
	#define Device(name, ...)			\
	    submodule(name,				\
		devHandle fn(getHandle)(strc8 name);	\
		interface(device) Interface;		\
		__VA_ARGS__				\
	    )
	
	#define stream   interface(stream)
	#define register interface(register)
#endif
