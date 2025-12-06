#pragma once
#define __ENV_COMMON__
#include "../pkg.h"
#include "../Devices/pkg.h"



#ifndef __ENV_COMMON_POSIX__

#include "types.h"

#define package env_Common


Interface(Posix,
  interface(env_Common_Posix_IO) IO;
  interface(env_Common_Posix_Thread) Thread;
)


#undef package
#endif
