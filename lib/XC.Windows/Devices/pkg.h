#pragma once
#define __ENV_WINDOWS__
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
	  Device(Input,
		stream Button, Position, Key;
	  )
	  Device(Network,
	    Device(Socket,
		stream Connection;
	    )
	    Device(Object,
		register Method, Field;
	    )
	  )
	)

	Device(Audio,
	  Device(Microphone,
		
	  )
	  Device(Player,
		
	  )
	  Device(Processor,
		
	  )
	)

	Device(Graphics,
	  Device(Camera,
		
	  )
	  Device(Screen,
		
	  )
	  Device(Window,
		
	  )
	  Device(Render,
		
	  )
	  Device(Terminal,

	  )
	)
	Device(Scheduler,
	  Device(Thread,
		register State;
	  )
	  Device(Process,
		
	  )
	)

	Device(Storage,
	  Device(Filesys,
	      register WorkDir;
	      stream File, Dir;
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

	Device(Sys, 
	  stream Clock;
	  register Locale;
	)
    )
)

#include <XC.Common/Devices/__DevTree_End.h>
