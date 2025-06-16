#include <stdio.h>

#define TRACE_ENTRY() \
    static int was_called = 0; \
    if (was_called == 0) { \
        was_called = 1; \
    } \

#define TRACE_RETURN() \
    return; \
