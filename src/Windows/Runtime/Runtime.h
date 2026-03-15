#pragma once
#include <Env.pkg.c>
#include <XC.pkg.c>

from(env_Common_Devices,
     	use(Manager),
	ID 		as devID,
     	ResourceID 	as rsrcID,
	Entry 		as devEntry,
	ResourceInfo	as rsrcInfo,
	Resource	as rsrcEntry
)

alias(env.Windows.Runtime,  	   WinRT)
alias(env.Windows.Lib, 	   	   WinLib)
alias(env.Common.Devices.Manager,  Dev)
alias(sys.Device.Attrib, 	   DevAttrib)
alias(sys.Stream.Attrib,   	   StrmAttrib)
alias(sys.Register.Attrib, 	   RegAttrib)
alias(std.String.Utils.Str, 	   str);
alias(std.String.Encoding,  	   encoding);


