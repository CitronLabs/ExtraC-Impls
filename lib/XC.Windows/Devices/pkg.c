#include <Env.pkg.h>

#define PKG_C
#include <XC.Common/Devices/__DevTree_Start.h>

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*    --- Storage Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    	stream(XC, Storage, Filesys, File);
    	stream(XC, Storage, Filesys, Dir);

    	register(XC, Storage, Filesys, WorkDir);
    
    Device(PATH(XC, Storage, Filesys),
    	File, Dir, WorkDir
    )

Device(PATH(XC, Storage),
	Filesys
)

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*	--- IO Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    	stream(XC, IO, Console, Buffer);
    	register(XC, IO, Console, Args)
    
    Device(PATH(XC, IO, Console),
    	Buffer, Args
    )

Device(PATH(XC, IO),
	Console
)

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*	--- Sys Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    stream(XC, Sys, Clock);

    register(XC, Sys, Locale);

Device(PATH(XC, Sys),
	Locale, Clock
)

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*    --- Memory Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

	register(XC, Memory, Loader, Module);

    Device(PATH(XC, Memory, Loader),
	Module
    )

	register(XC, Memory, Mapper, Block);

    Device(PATH(XC, Memory, Mapper),
	Block
    )

Device(PATH(XC, Memory),
	Loader, Mapper
)

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*   --- Scheduler Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Device(PATH(XC, Scheduler, Process),

    )
	register(XC, Scheduler, Thread, State)

    Device(PATH(XC, Scheduler, Thread),
	State
    );

Device(PATH(XC, Scheduler),
	Thread, Process
)

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*   	--- XC Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    register(XC, Implementation);

Device(XC,
	Implementation,
	Memory, Scheduler, Sys, IO, Storage
)

DevTree(XC)

#include <XC.Common/Devices/__DevTree_End.h>
