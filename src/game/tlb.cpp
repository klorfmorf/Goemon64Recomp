#include "recomp.h"
#include "librecomp/overlays.hpp"
#include "librecomp/helpers.hpp"
#include "ultramodern/ultramodern.hpp"

#define OS_PM_4K	0x0000000
#define OS_PM_16K	0x0006000
#define OS_PM_64K	0x001e000
#define OS_PM_256K	0x007e000
#define OS_PM_1M	0x01fe000
#define OS_PM_4M	0x07fe000
#define OS_PM_16M	0x1ffe000

typedef u32 OSPageMask;

extern "C" void osMapTLB_recomp(uint8_t* rdram, recomp_context* ctx) {
    s32 index = _arg<0, s32>(rdram, ctx);
    OSPageMask pm = _arg<1, OSPageMask>(rdram, ctx);
    PTR(void) vaddr = _arg<2, PTR(void)>(rdram, ctx);
    u32 evenpaddr = _arg<3, u32>(rdram, ctx);
    u32 oddpaddr = (u32)MEM_W(0x10, ctx->r29);
    u32 asid = (u32)MEM_W(0x14, ctx->r29);

    u32 page_size = 0;
    switch (pm) {
        case OS_PM_4K:
            page_size = 0x1000;
            break;
        case OS_PM_16K:
            page_size = 0x4000;
            break;
        case OS_PM_64K:
            page_size = 0x10000;
            break;
        case OS_PM_256K:
            page_size = 0x40000;
            break;
        case OS_PM_1M:
            page_size = 0x100000;
            break;
        case OS_PM_4M:
            page_size = 0x400000;
            break;
        case OS_PM_16M:
            page_size = 0x1000000;
            break;
    }

    map_tlb_overlays(index, evenpaddr, oddpaddr, vaddr, page_size);
}

extern "C" void osUnmapTLB_recomp(uint8_t* rdram, recomp_context* ctx) {
    s32 index = _arg<0, s32>(rdram, ctx);

    unmap_tlb_overlays(index);
}

extern "C" void osUnmapTLBAll_recomp(uint8_t* rdram, recomp_context* ctx) {
    for (size_t i = 0; i < 32; i++) {
        unmap_tlb_overlays(i);
    }
}