#include <Env.pkg.h>

#define PKG_C
#include <XC.Common/Devices/__DevTree_Start.h>

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*    --- Storage Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    	stream(XC, Storage, Filesys, File);
    	stream(XC, Storage, Filesys, Dir);

    	register(XC, Storage, Filesys, WorkDir);
    	register(XC, Storage, Filesys, Caps);
    
    Device(PATH(XC, Storage, Filesys),
    	File, Dir, WorkDir, Caps
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
/*    --- Memory Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

	register(XC, Memory, Mapper, Block);

    Device(PATH(XC, Memory, Mapper),
	Block
    )

	register(XC, Memory, Loader, Module);

    Device(PATH(XC, Memory, Loader),
	Module
    )

Device(PATH(XC, Memory),
	Loader
)

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*   --- Scheduler Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

	register(XC, Scheduler, Thread, State)

    Device(PATH(XC, Scheduler, Thread),
	State
    );

Device(PATH(XC, Scheduler),
	Thread
)

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*   	--- XC Device ---	*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    register(XC, Implementation);

Device(XC,
	Implementation,
	Memory, IO, Storage, Scheduler
)

DevTree(XC)

#include <XC.Common/Devices/__DevTree_End.h>
