#include "../../../../Devices.h"
#define module env, Devices, XC, Storage, Filesys, WorkDir

pntr moduleFn(open)(devHandle dev, strc8 name, word attributes, bool create){}	

len_t moduleFn(readFrom)(registerHandle handle, const void* buffer, len_t settingID){}
registerInfo moduleFn(info)(registerHandle handle){}

errvt moduleFn(close)(registerHandle handle){}
errvt moduleFn(delete)(registerHandle handle){}

errvt moduleFn(edit)(registerHandle handle, const char* name, word attributes){}
errvt moduleFn(watch)(registerHandle handle){}
len_t moduleFn(isModified)(registerHandle handle){}
len_t moduleFn(writeTo)(registerHandle handle, const void* buffer, len_t size){}
len_t moduleFn(setTo)(registerHandle handle, const void* buffer, len_t size){}
void* moduleFn(access)(registerHandle handle){}
