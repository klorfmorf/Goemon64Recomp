#ifndef PATCHES_H
#define PATCHES_H

#define osCreateMesgQueue osCreateMesgQueue_recomp
#define osCreateThread osCreateThread_recomp
#define osCreateViManager osCreateViManager_recomp
#define osDpSetNextBuffer osDpSetNextBuffer_recomp
#define osGetTime osGetTime_recomp
#define osRecvMesg osRecvMesg_recomp
#define osSendMesg osSendMesg_recomp
#define osSetEventMesg osSetEventMesg_recomp
#define osSetIntMask osSetIntMask_recomp
#define osSpTaskLoad osSpTaskLoad_recomp
#define osSpTaskStartGo osSpTaskStartGo_recomp
#define osSpTaskYield osSpTaskYield_recomp
#define osSpTaskYielded osSpTaskYielded_recomp
#define osStartThread osStartThread_recomp
#define osViBlack osViBlack_recomp
#define osViGetCurrentFramebuffer osViGetCurrentFramebuffer_recomp
#define osViGetNextFramebuffer osViGetNextFramebuffer_recomp
#define osViSetEvent osViSetEvent_recomp
#define osViSetMode osViSetMode_recomp
#define osViSwapBuffer osViSwapBuffer_recomp
#define osWritebackDCacheAll osWritebackDCacheAll_recomp

#include <ultra64.h>
#include "rt64_extended_gbi.h"

#define RECOMP_EXPORT      __attribute__((section(".recomp_export")))
#define RECOMP_PATCH       __attribute__((section(".recomp_patch")))
#define RECOMP_FORCE_PATCH __attribute__((section(".recomp_force_patch")))

#include "patch_helpers.h"
#include "patch_api_funcs.h"

#include "types.h"
#include "structs.h"
#include "macros.h"
#include "functions.h"
#include "variables.h"

#define true 1
#define false 0

typedef _Bool bool;

static inline void* memcpy(void* s1, const void* s2, size_t n) {
    char* su1 = (char*)s1;
    const char* su2 = (const char*)s2;
    
    while (n > 0) {
        *su1 = *su2;
        su1++;
        su2++;
        n--;
    }
    
    return (void*)s1;
}

int recomp_printf(const char* fmt, ...);

#endif // PATCHES_H
