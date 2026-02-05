#pragma once
#define __ENV_WINDOWS__
#include "../../pkg.h"


#ifndef __ENV_WINDOWS_RUNTIME__
#define package env_Windows_Lib_FS

Class(File,
INIT(const c8* path; word attributes),
FMT(),

){

};

Class(Dir,
INIT(const c8* path; word attributes),
FMT(),

){


};

type(Entry,
     	bool exists;
	u32  type;
)

Interface_Pkg(
	interface(pkg(File)) File;
	interface(pkg(Dir)) Dir;

	values(Type, u32,
		FILE,
		DIR
	)

	pkg(Entry) fn(info)(const c8* path);
	bool 	   fn(delete)(const c8* path);
)

#undef package
#endif
