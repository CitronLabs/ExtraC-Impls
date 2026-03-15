#pragma once
#define __ENV_PYTHON__
#include "../pkg.h"
#include <XC.Common/Devices/__DevTree_Start.h>

DevTree(
    Device(XC,
	register Implementation;

	Device(IO,
	  Device(Console,
		register Args;
	  	stream Buffer;
	  )
	)

	Device(Storage,
	  Device(Filesys,
	      register WorkDir, Caps;
	      stream File, Dir;
	  )
	)

	Device(Scheduler,
	  Device(Thread,
		register State;
	  )
	)

	Device(Memory,
	  Device(Loader,
		register Module;
	  );
	  Device(Mapper,
		register Block;
	  );
	)
    )
)

#include <XC.Common/Devices/__DevTree_End.h>
