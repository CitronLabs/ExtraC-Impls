#include "../../../../Devices.h"
#define module env, Devices, XC, Storage, Filesys, File

pntr moduleFn(open)(devHandle dev, const char* key, word attributes, bool create){



}

errvt moduleFn(close)(streamHandle handle){



}

errvt moduleFn(delete)(streamHandle handle){



}

errvt moduleFn(edit)(streamHandle handle, const char* name, word attributes){



}
errvt moduleFn(watch)(streamHandle handle){



}

len_t moduleFn(isModified)(streamHandle handle){



}

len_t moduleFn(shift)(streamHandle handle, word offset, len_t from){



}

len_t moduleFn(readFrom)(streamHandle handle, void* buffer, len_t size){



}

len_t moduleFn(writeTo)(streamHandle handle, const void* buffer, len_t size){



}

streamInfo moduleFn(info)(streamHandle handle){



}

errvt moduleFn(control)(streamHandle handle, word command, void* args){



}

errvt moduleFn(flush)(streamHandle handle){



}

errvt moduleFn(sync)(streamHandle handle){


}
