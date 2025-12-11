#pragma once
#include <Core/pkg.c>
#include <XC/pkg.h>

/*--------------------------------------|
 *					|
 *	   XC.Dev.Stream Module		|
 *					|
 *------------------------------------*/
#define module XC, Dev, Stream

moduleValues(ID,
	In  as 0,
	Out as 1,
	Err as 2,
);

moduleValues(Attrib,
      	READ  as (1 << 0), 
      	WRITE as (1 << 1),
      	DIR   as (1 << 2),  
        LINK  as (1 << 3),
);

importFn(
	writeTo, readFrom, open, 
  	fetch, modify, watch, isModified, 
  	close, drop, stdHandle, shift, info, 
  	control, flush, sync
)

export(
SUBMODULE(),
VALUES(Attrib, ID),
	writeTo, readFrom, open, 
  	fetch, modify, watch, isModified, 
  	close, drop, stdHandle, shift, info, 
  	control, flush, sync
);


#undef module
/*--------------------------------------|
 *					|
 *	      XC.Dev Module		|
 *					|
 *------------------------------------*/
#define module XC, Dev


moduleValues(Attrib,
	      	PRIVATE,,
	      	PUBLIC,,
	);

moduleValues(ID,
     		IO,,
	      	Local,,
	      	Sys,,   
	);


importFn(open, fetch, stdHandle)

export(
SUBMODULE(Stream),
VALUES(Attrib, ID),
	open, fetch, stdHandle);

#undef module

