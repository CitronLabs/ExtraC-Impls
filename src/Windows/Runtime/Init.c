#include "Runtime.h"
#include "Symbols.h"
#define module env, Windows, Runtime

static void moduleFn(runConstructors)() {
    void (**ptr)() = __xc_init_start;
    void (**end)() = __xc_init_end;

    while (ptr < end) {
        if (ptr[0]) ptr[0]();
        pntr_shift(ptr, sizeof(*ptr));
    }

}

static void moduleFn(setupFPU)(){
    unsigned short x87_cw = 0x037F; // Standard: Mask exceptions, 64-bit precision
    unsigned int sse_mxcsr = 0x1F80; // Standard: Mask exceptions, round to nearest

    __asm__ __volatile__ (
        ".intel_syntax noprefix\n"
        "finit\n"                 /* Reset x87 FPU to default state */
        "fldcw [%0]\n"            /* Load x87 Control Word */
        "ldmxcsr [%1]\n"          /* Load SSE Control/Status Register */
        ".att_syntax prefix\n"
        : 
        : "r"(&x87_cw), "r"(&sse_mxcsr)
        : "memory"
    );
}


void moduleFn(init)(){
	
	iferr(env.Windows.Runtime.Resource.init()){
		printlnErr("Failed to initialize XC resource system");
		ExitProcess(-1);
	}

	if(env.Windows.Runtime.Memory.getID() == -1){
		printlnErr("Failed to initialize XC.Memory device");
		ExitProcess(-1);
	}

	if(env.Windows.Runtime.IO.getID() == -1){
		printlnErr("Failed to initialize XC.IO device");
		ExitProcess(-1);
	}

	if(env.Windows.Runtime.Scheduler.getID() == -1){
		printlnErr("Failed to initialize XC.Scheduler device");
		ExitProcess(-1);
	}

	if(env.Windows.Runtime.Sys.getID() == -1){
		printlnErr("Failed to initialize XC.Sys device");
		ExitProcess(-1);
	}
	
	errvt exitcode = 
		__MAIN_APP.start(args());
	
	if(exitcode != OK)
		printlnErr("Process Exited with error:");
	else 
		printlnErr("Process Exited OK");
	

	ExitProcess(exitcode);
}

static void moduleFn(start_Stage2)() {
    

    mod(setupFPU)();
    mod(runConstructors)();
    mod(init)();
    
    ExitProcess(-1);
}

[[gnu::naked]] void _start(void) {
    __asm__ __volatile__ (
        ".intel_syntax noprefix\n"
        "xor rbp, rbp\n"          /* Clear frame pointer */
        "mov rdx, rsp\n"          /* Capture current stack pointer */
        "and rsp, -16\n"          /* Align stack to 16 bytes */
        "sub rsp, 40\n"           /* 32 bytes shadow space + 8 bytes to maintain alignment */
        "call %0\n"               /* Jump to Stage 2 */
        "hlt\n"                   /* Safety trap */
        ".att_syntax prefix\n"
        : : "i"(env_Windows_Runtime_start_Stage2) : "memory"
    );
}
