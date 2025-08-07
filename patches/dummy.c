#include "patches.h"

// Prevent .rodata from being the very last thing in the patch binary so initialize a non-zero non-const dummy value.
u64 dummy = 0x0123456789ABCDEF;
