#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _WIN32_WINNT 0x0601
#define byte win_byte
#define system win_system
#define std win_std
#include <windows.h>
#undef std
#undef system
#undef byte
#undef DELETE
#undef NEWFRAME
#undef SPACE
#undef ERROR
