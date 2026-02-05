#pragma once
#define __ENV_WINDOWS__
#include "../../pkg.h"


#ifndef __ENV_WINDOWS_RUNTIME__
#define package env_Windows_Lib_Console

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
	len_t fn(writeErr)(constpntr buffer, len_t len);
	len_t fn(readIn)(pntr buffer, len_t len);

	len_t fn(writeOut)(constpntr buffer, len_t len);
	len_t fn(flush)();
};


#undef package
#endif
