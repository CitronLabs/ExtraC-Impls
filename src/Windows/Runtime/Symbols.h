#include <Env.pkg.h>

/* --- PE/COFF CONTRACT SYMBOLS --- */
int _fltused = 0x9875;
u64 _tls_index = 0;




extern byte __tls_start__;
extern byte __tls_end__;

[[gnu::section(".rdata$T")]]
const IMAGE_TLS_DIRECTORY64 _tls_used = {
    (ULONGLONG)&__tls_start__, (ULONGLONG)&__tls_end__,
    (ULONGLONG)&_tls_index,    (ULONGLONG)0, 0, 0
};





/* --- BRACKETED CONSTRUCTORS --- */
[[gnu::section(".CRT$XCA")]] void (*__xc_init_start[0])();
[[gnu::section(".CRT$XCZ")]] void (*__xc_init_end[0])();
