#include "pkg.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

import(std)

int vmethodimpl(PosixIO, open, std_FSPath path, int flags){
	
	int fd = -1;

	if(getbitflag(flags, O_WRONLY) && getbitflag(flags, O_RDONLY)){
		flags ^= O_WRONLY;
		flags ^= O_RDONLY;
		flags |= O_RDWR;
	}

	if((fd = open(path, flags)) == -1){
		switch (errno) {
		
		}
	}

return fd;
}

errvt vmethodimpl(PosixIO, fs_search, std_FSPath path, std_FSEntry* entry){
	nonull(path, return err);

	struct stat statbuf;
	if(stat(path, &statbuf) == -1){
		switch (errno) {
		
		}
	}

	if(entry == null) return OK;

	entry->type.is.dir = S_ISDIR(statbuf.st_mode);
	
	entry->time_created = statbuf.st_ctim.tv_sec;
	entry->time_modified = statbuf.st_mtim.tv_sec;

	u32 nameoffset = 0, pathlen = strnlen(path, 255);
	
	loop(i, pathlen){
	   if(path[pathlen - i] == '/'){
		nameoffset = pathlen - i + 1;
		break;
	   }
	}
	loop(i, pathlen - nameoffset)
		entry->name[i] = path[nameoffset + i];
return OK;
}

errvt vmethodimpl(PosixIO, fs_delete, fsPath path){
	nonull(path, return err)	
	if(-1 == remove(path)){
		switch (errno) {
		
		}	
	}
return OK;
}
i64 vmethodimpl(PosixIO, read, storageHandle handle, void* buff, u64 size){
	nonull(buff, return err)
	u64 bytesread = 0;
	if(-1 == (bytesread = read(addrasval(handle), buff, size))){
		switch (errno) {
		
		}	
	}
return bytesread;
}





i64 vmethodimpl(PosixIO, write, storageHandle handle, void* buff, u64 size){
	nonull(buff, return err)
	u64 byteswritten = 0;
	if(-1 == (byteswritten = write(addrasval(handle), buff, size))){
		switch (errno) {
		
		}	
	}
return byteswritten;
}
errvt vmethodimpl(PosixIO, fs_chdir, fsPath path){
	nonull(path, return err)
	if(-1 == chdir(path)){
		switch (errno) {
		
		}	
	}
return OK;
}

errvt vmethodimpl(PosixIO, close, storageHandle handle){
	if(handle == (storageHandle)0 || handle == (storageHandle)1 || handle == (storageHandle)2) 
		return ERR(ERR_INVALID, "cannot close the stdout, stdin, or stderr");
	if((close(addrasval(handle))) == -1){
		switch (errno) {
		
		}
	}
return OK;
}
