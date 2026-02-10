#pragma once
#define __ENV_WINDOWS__
#include "../../pkg.h"


#ifndef __ENV_WINDOWS_RUNTIME__
#define package env_Windows_Lib

Class(Console,
INIT(len_t outBuffSize),
FMT(),
private(
    struct{
	HANDLE handle; 
    } input;
    struct{
	HANDLE handle; 
      	std_Array_Buffer buffer;
    } output;
    struct{
	HANDLE handle; 
    } error;
)
){
	values(Stream, uword,
		INPUT,
		OUTPUT,
		ERROR
	)
	len_t method(Console, writeErr, constpntr buffer, len_t len);
	len_t method(Console, readIn, pntr buffer, len_t len);

	len_t method(Console, writeOut, constpntr buffer, len_t len);
	len_t method(Console, flush);

	HANDLE method(Console, getHandle, uword stream);
};


#undef package
#endif
