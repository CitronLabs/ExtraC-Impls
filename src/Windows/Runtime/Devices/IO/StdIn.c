#include "../Device.h"

from(env_Windows_Lib, 
     	use(Console)
);

static struct {
	DWORD type;
	LONGLONG lastFilePos; // Only used for when StdIn is FILE_TYPE_DISK
	Console* console;
} StdIn;


errvt moduleFn(Resource_StdIn_watch)(streamHandle handle){
	if(!StdIn.console) mod(Resource_StdIn_sync)(handle);

	HANDLE stdInHandle = WinLib.Console.getHandle(
    	    StdIn.console, 
    	    WinLib.Console.Stream.INPUT  
    	);

    	DWORD mode;
    	if (GetConsoleMode(stdInHandle, &mode)) {
    	    // 1. Disable Line Input (raw mode)
    	    // 2. Disable Echo (don't print keys automatically)
    	    // 3. Disable QuickEdit (prevent mouse clicks from freezing the app)
    	    // 4. Enable Extended Flags (required to modify QuickEdit)
    	    
    	    DWORD newMode = mode;
    	    newMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_QUICK_EDIT_MODE);
    	    newMode |= (ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT);

    	    SetConsoleMode(stdInHandle, newMode);
    	}

    	// Optional: Clear any junk currently in the buffer so isModified starts at 0
    	FlushConsoleInputBuffer(stdInHandle);

    	// StdIn.type should be cached here if sync didn't do it
    	if (!StdIn.type) {
    	    StdIn.type = GetFileType(stdInHandle);
    	}

    	return OK;
}
len_t moduleFn(Resource_StdIn_isModified)(streamHandle handle){
	
	if(!StdIn.console) mod(Resource_StdIn_sync)(handle);

	if(!StdIn.type){ 
		ERR(ERR.INVALID, "XC.IO:/Console/StdIn is not being watched");
		return 0; 
	}

	HANDLE stdInHandle = WinLib.Console.getHandle(
		StdIn.console,
		WinLib.Console.Stream.INPUT
	);

    	switch (StdIn.type) {
    	case FILE_TYPE_CHAR: { // Console
		len_t byteCount = 0;
    		DWORD numEvents = 0;

           	if (GetNumberOfConsoleInputEvents(stdInHandle, &numEvents) && numEvents > 0) {
                    DWORD 	  eventsPeeked = 0;
		    len_t 	  eventsToPeek = (numEvents > 1024 ? 1024 : numEvents);
                    INPUT_RECORD* eventBuffer  = alloca(sizeof(INPUT_RECORD) * eventsToPeek);

                    if (!PeekConsoleInputW(stdInHandle, eventBuffer, eventsToPeek, &eventsPeeked))
		    	break;

                    loop(o, eventsPeeked){
                        if (eventBuffer[o].EventType != KEY_EVENT || 
			    !eventBuffer[o].Event.KeyEvent.bKeyDown)
				continue;

		    	c16 c  = eventBuffer[o].Event.KeyEvent.uChar.UnicodeChar;
			rune r = c;

			if(c == '\0') continue;

			// Windows puts low and high UTF16 surrogate pairs in seperate input events
			if(std.String.Encoding.UTF16.isHighSurrogate(c) && (o + 1 < eventsPeeked)){
			    c16 nextC = eventBuffer[o + 1].Event.KeyEvent.uChar.UnicodeChar;

			    if (std.String.Encoding.UTF16.isLowSurrogate(nextC)) {
            			r = std.String.Encoding.UTF16.mergeSurrogates(c, nextC);
            			o++; // Consume the low surrogate
        		    }

			}

			byteCount += std.String.Encoding.UTF8.charSize(r);
		    }
		}
        	return byteCount;
	}
    	case FILE_TYPE_PIPE: { // Pipes/Anonymous Pipes (e.g. "cat file | app")
            DWORD bytes = 0;

            if (PeekNamedPipe(stdInHandle, NULL, 0, NULL, &bytes, NULL)) {
                return bytes;
            }

            return 0;
        }
        case FILE_TYPE_DISK: { // Files (e.g. "app < input.txt")
            LARGE_INTEGER fileSize, currentPos;
            
            // Get total size of the file
            if (GetFileSizeEx(stdInHandle, &fileSize)) {
                LARGE_INTEGER zero = {0};
                // Get current read position without moving it (FILE_CURRENT with 0 offset)
                if (SetFilePointerEx(stdInHandle, zero, &currentPos, FILE_CURRENT)) 
                    if (currentPos.QuadPart < fileSize.QuadPart) 
                        return fileSize.QuadPart - currentPos.QuadPart;
                    
                
            }
            return 0;    	
	}
	}

return 0;
}

len_t moduleFn(Resource_StdIn_shift)(streamHandle handle, word offset, len_t from){
	if(offset < 0){
		ERR(ERR.INVALID, "Cannot rewind XC.IO:/Console/StdIn"); 
		return 0;
	}

	len_t bytesRead = 0;

	u8 buffer[250] = {};

	do {
	    len_t 
		bytesToRead = (offset -= 250) > 250 ? 250 : offset,

	    	iter_bytesRead = WinLib.Console.readIn(StdIn.console, buffer, bytesToRead);

	    bytesRead += iter_bytesRead;
	} 
	while(offset > 250);

return bytesRead;
}
len_t moduleFn(Resource_StdIn_readFrom)(streamHandle handle, void* buffer, len_t size){
return WinLib.Console.readIn(StdIn.console, buffer, size);
}

len_t moduleFn(Resource_StdIn_writeTo)(streamHandle handle, const void* buffer, len_t size){
	ERR(ERR.INVALID, "XC.IO:/Console/StdIn cannot be written to");
	return 0;
}


streamInfo moduleFn(Resource_StdIn_info)(streamHandle handle){
return (streamInfo){
.name 		= "StdIn",
.path 		= "Console/StdIn",
.attributes 	= core.Device.Stream.Attrib.READ,
.type 		= nil,
.currentPos    	= 0,
.time_created  	= 0,
.time_modified 	= 0,
.size 		= 0
};
}

errvt moduleFn(Resource_StdIn_control)(streamHandle handle, word command, void* args){ return OK; }
errvt moduleFn(Resource_StdIn_flush)(streamHandle handle){ return OK; }
errvt moduleFn(Resource_StdIn_sync)(streamHandle handle){ 
	
	var stdInResource = Dev.Resource.getOne(
		WinRTDev.getManager(),
		WinRTDev.getIO(),
		(pntrval)handle
	);

	if(!stdInResource){
		ERR(ERR.FAIL, "Failed to access XC.IO:/Console/StdIn");
		return 0;
	}

	StdIn.console = stdInResource->data;

return OK; 
}
