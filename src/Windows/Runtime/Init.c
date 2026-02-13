#include <XC.pkg.c>
#define module env, Windows, Runtime

/* --- SECTION 1: PE/COFF CONTRACT SYMBOLS --- */
int _fltused = 0x9875;
u64 _tls_index = 0;

extern byte __tls_start__;
extern byte __tls_end__;

[[gnu::section(".rdata$T")]]
const IMAGE_TLS_DIRECTORY64 _tls_used = {
    (ULONGLONG)&__tls_start__, (ULONGLONG)&__tls_end__,
    (ULONGLONG)&_tls_index,    (ULONGLONG)0, 0, 0
};

/* --- SECTION 2: BRACKETED CONSTRUCTORS --- */
[[gnu::section(".CRT$XCA")]] void (*__xc_init_start[0])();
[[gnu::section(".CRT$XCZ")]] void (*__xc_init_end[0])();

static void moduleFn(runConstructors)() {
    void (**ptr)() = __xc_init_start;
    void (**end)() = __xc_init_end;

    while (ptr < end) {
        if (ptr[0]) ptr[0]();
        pntr_shift(ptr, sizeof(*ptr));
    }

}

/* --- SECTION 3: ENTRY POINT --- */

void moduleFn(init)(){
	int argCount;
	
	iferr(env.Windows.Runtime.Memory.init())
		printlnErr("Failed to initialize runtime device system:");

	iferr(env.Windows.Runtime.Device.init())
		printlnErr("Failed to initialize runtime device system:");
	

	errvt exitcode = 
		__MAIN_APP.start(args());
	
	if(exitcode != OK)
		printlnErr("Process Exited with error:");
	else 
		printlnErr("Process Exited OK");
	

	ExitProcess(exitcode);
}

void moduleFn(fpuSetup)(){
    u16   x87_cw    = 0x037F; // Standard: Mask exceptions, 64-bit precision
    uword sse_mxcsr = 0x1F80; // Standard: Mask exceptions, round to nearest

    __asm__ volatile(
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

static void moduleFn(start_Stage2)() {
    
    mod(fpuSetup)();
    mod(runConstructors)();
    mod(init)();
    
    ExitProcess(-1);
}

[[gnu::naked]] void mainCRTStartup(void) {
     __asm__ volatile(
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
