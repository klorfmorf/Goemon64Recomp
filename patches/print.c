#include "patches.h"
#include "misc_funcs.h"

// Manual definitions for variadic arguments since stdarg.h is not available
typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v) __builtin_va_end(v)

// Forward declaration of _Printf function
int _Printf(void *(*put)(void *, const char *, size_t), void *arg, const char *fmt, va_list ap);

void* proutPrintf(void* dst, const char* fmt, size_t size) {
    recomp_puts(fmt, size);
    return (void*)1;
}

RECOMP_EXPORT int recomp_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = _Printf(&proutPrintf, NULL, fmt, args);

    va_end(args);

    return ret;
}