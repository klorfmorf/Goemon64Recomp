// Prevent .rodata from being the very last thing in the patch binary so initialize a non-zero non-const dummy value.
unsigned long long g_dummy = 0x0123456789ABCDEFllu;
