#include "../Device.h"

errvt moduleFn(Resource_CliArgs_edit)(registerHandle handle, const char* name, word attributes);
errvt moduleFn(Resource_CliArgs_watch)(registerHandle handle);
len_t moduleFn(Resource_CliArgs_isModified)(registerHandle handle);

len_t moduleFn(Resource_CliArgs_readFrom)(registerHandle handle, const void* buffer, len_t size);
len_t moduleFn(Resource_CliArgs_writeTo) (registerHandle handle, const void* buffer, len_t size);
len_t moduleFn(Resource_CliArgs_setTo)   (registerHandle handle, const void* buffer, len_t size);
void* moduleFn(Resource_CliArgs_access)  (registerHandle handle);

registerInfo moduleFn(Resource_CliArgs_info)(registerHandle handle);
