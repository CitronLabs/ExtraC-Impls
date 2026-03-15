#include <Env.pkg.c>
#include <XC.pkg.c>
#undef main
#undef malloc


from(env_Common_Devices,
	ID 		as devID,
     	ResourceID 	as rsrcID,
	Entry 		as devEntry,
	ResourceInfo	as rsrcInfo,
	Resource	as rsrcEntry
)

alias(env.Common.Devices.Manager,  Dev)
alias(sys.Stream.Attrib,   	   StrmAttrib)
alias(sys.Register.Attrib, 	   RegAttrib)

alias(env.Python.Lib, py)
alias(std.Memory.Allocator, Alloc)
