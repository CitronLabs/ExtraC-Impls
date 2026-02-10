#pragma once
#include <XC.pkg.h>
#include <XC.Common/pkg.c>

#define module env, Windows, Runtime

exportFrom(PATH(Device, IO),
SUBMODULE(),
VALUES(),
	fetch, info, close, delete, edit, open
)

exportFrom(PATH(Device, Sys),
SUBMODULE(),
VALUES(),
	fetch, info, close, delete, edit, open
)

exportFrom(PATH(Device, Resource, StdErr),
SUBMODULE(),
VALUES(),
	writeTo, readFrom, watch,  shift, sync, 
	control, info, flush, isModified
)

exportFrom(PATH(Device, Resource, StdOut),
SUBMODULE(),
VALUES(),
	writeTo, readFrom, watch,  shift, sync, 
	control, info, flush, isModified
)

exportFrom(PATH(Device, Resource, StdIn),
SUBMODULE(),
VALUES(),
	writeTo, readFrom, watch,  shift, sync, 
	control, info, flush, isModified
)

exportFrom(PATH(Device, Resource, Console),
SUBMODULE(),
VALUES(),
	writeTo, readFrom, watch,  shift, sync, 
	control, info, flush, isModified
)

exportFrom(PATH(Device, Resource, Locale),
SUBMODULE(),
VALUES(),
	writeTo, readFrom, setTo, watch,  
	access, info, isModified
)

exportFrom(PATH(Device, Resource, WorkDir),
SUBMODULE(),
VALUES(),
	writeTo, readFrom, setTo, watch,  
	access, info, isModified
)

exportFrom(PATH(Device, Resource, CliArgs),
SUBMODULE(),
VALUES(),
	writeTo, readFrom, setTo, watch,  
	access, info, isModified
)

exportFrom(PATH(Device, Resource),
SUBMODULE(StdIn, StdOut, StdErr, Console, Locale, CliArgs),
VALUES(),
)

exportFrom(Device,
SUBMODULE(IO, Sys, Resource),
VALUES(),
	getManager, getIO, getSys, init
)

exportFrom(Memory,
SUBMODULE(),
VALUES(),
	init 
)

export(
SUBMODULE(Device, Memory),
VALUES(),
	init
)

#undef module
