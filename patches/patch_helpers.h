#ifndef PATCH_HELPERS_H
#define PATCH_HELPERS_H

#ifdef MIPS
#include <ultra64.h>
#else
#include "recomp.h"
#endif

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#ifdef MIPS
#define DECLARE_FUNC(type, name, ...) \
        EXTERNC type name(__VA_ARGS__)
#else // MIPS
#define DECLARE_FUNC(type, name, ...) \
        EXTERNC void name(uint8_t *rdram, recomp_context *ctx)
#endif

#endif // PATCH_HELPERS_H
