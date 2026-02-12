#include "patches.h"

void* func_801CF57C_66242C(void* arg0, s32 index, s32 fb_ulx, s32 fb_uly, s32 width, s32 height); /* extern */

extern Gfx D_8006D898[];
extern Gfx D_801D33B0_666260[];
extern u8  D_80261000[];

static u16 g_menu_framebuffer_left[8][120];
static u16 g_menu_framebuffer_right[8][120];
static u16 g_menu_framebuffer_top[256][8];
static u16 g_menu_framebuffer_bottom[256][8];

RECOMP_PATCH void* func_801CF748_6625F8(Gfx* gfx, Vtx* vtx, s32 fb_ulx, s32 fb_uly, s32 x_off, s32 y_off, s32 fb) {
    u32 color_image_addr;
    u32 framebuffer_addr;
    u32 temp_t0;
    Gfx* dl;
    Gfx* temp_v0_2_1;
    Gfx* temp_v0_2_2;
    Gfx* temp_v0_3_1;
    Gfx* temp_v0_3_2;

    if (vtx == 0) {
        gSPEndDisplayList(gfx);
        return gfx;
    }

    gSPDisplayList(gfx, D_801D33B0_666260);

    temp_t0 = (u32)fb + 0x80000000u;
    color_image_addr = temp_t0;
    gDPSetColorImage(
        gfx + 1,
        G_IM_FMT_RGBA,
        D_8015C5C8_15D1C8->frame_buffer_bits_per_pixel & 3,
        8,
        (void*)g_menu_framebuffer_left);

    recomp_printf("------------------------\n");
    recomp_printf("left:   x: %03d, y: %03d\n", fb_ulx, fb_uly);
    recomp_printf("right:  x: %03d, y: %03d\n", (fb_ulx + x_off) - 4, fb_uly);
    recomp_printf("top:    x: %03d, y: %03d\n", fb_ulx, fb_uly);
    recomp_printf("bottom: x: %03d, y: %03d\n", fb_ulx, (fb_uly + y_off) - 8);
    recomp_printf("------------------------\n");

    // Render left texture
    temp_v0_2_1 = (Gfx*)func_801CF57C_66242C(
        (void*)(gfx + 2), 
        0, 
        fb_ulx, 
        fb_uly, 
        8, 
        120);

    gDPSetColorImage(
        temp_v0_2_1,
        G_IM_FMT_RGBA,
        D_8015C5C8_15D1C8->frame_buffer_bits_per_pixel & 3,
        8,
        (void*)g_menu_framebuffer_right);

    // Render right texture
    temp_v0_2_2 = (Gfx*)func_801CF57C_66242C(
        (void*)(temp_v0_2_1 + 1),
        0,
        (fb_ulx + x_off) - 4,
        fb_uly,
        8,
        120);

    gDPSetColorImage(
        temp_v0_2_2,
        G_IM_FMT_RGBA,
        D_8015C5C8_15D1C8->frame_buffer_bits_per_pixel & 3,
        256,
        (void*)g_menu_framebuffer_top);
    
    // Render top texture
    temp_v0_3_1 = (Gfx*)func_801CF57C_66242C(
        (void*)(temp_v0_2_2 + 1), 
        0, 
        fb_ulx, 
        fb_uly, 
        256, 
        8);

    gDPSetColorImage(
        temp_v0_3_1,
        G_IM_FMT_RGBA,
        D_8015C5C8_15D1C8->frame_buffer_bits_per_pixel & 3,
        256,
        (void*)g_menu_framebuffer_bottom);
    
    // Render bottom texture
    temp_v0_3_2 = (Gfx*)func_801CF57C_66242C(
        (void*)(temp_v0_3_1 + 1),
        0,
        fb_ulx,
        (fb_uly + y_off) - 8,
        256,
        8);

    framebuffer_addr = (u32)(D_8015C5C8_15D1C8->current_frame_buffer * 0x25800) + 0x80000000u + (u32)D_80261000;

    dl = temp_v0_3_2;

    gSPDisplayList(dl++, D_8006D898);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gDPSetColorImage(dl++, G_IM_FMT_RGBA, D_8015C5C8_15D1C8->frame_buffer_bits_per_pixel & 3, 320, (void*)framebuffer_addr);
    gSPClearGeometryMode(dl++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
    gSPSetGeometryMode(dl++, G_CULL_BACK | G_LIGHTING);
    gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLOD(dl++, G_TL_TILE);
    gDPSetTextureDetail(dl++, G_TD_CLAMP);
    gDPSetTextureLUT(dl++, G_TT_NONE);
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    gDPSetCombineLERP(dl++, PRIMITIVE, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0);
    gDPSetPrimColor(dl++, 0, 0, 16, 16, 16, 255);

    // Right
    gDPPipeSync(dl++);
    gDPSetTextureImage(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (void*)((u32)g_menu_framebuffer_right));
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(dl++);
    gDPLoadBlock(dl++, G_TX_LOADTILE, 0, 0, 959, 1024);
    gDPPipeSync(dl++);
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(dl++, G_TX_RENDERTILE, 0, 0, 28, 476);
    gSPVertex(dl++, vtx + 8, 4, 0);
    gSP2Triangles(dl++, 2, 1, 0, 0, 3, 2, 0, 0);

    // Top
    gDPPipeSync(dl++);
    gDPSetTextureImage(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (void*)((u32)g_menu_framebuffer_top));
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(dl++);
    gDPLoadBlock(dl++, G_TX_LOADTILE, 0, 0, 2047, 32);
    gDPPipeSync(dl++);
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(dl++, G_TX_RENDERTILE, 0, 0, 1020, 28);
    gSPVertex(dl++, vtx + 4, 4, 0);
    gSP2Triangles(dl++, 2, 1, 0, 0, 3, 2, 0, 0);

    gDPSetCombineMode(dl++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);

    // Left
    gDPPipeSync(dl++);
    gDPSetTextureImage(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (void*)(u32)g_menu_framebuffer_left);
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(dl++);
    gDPLoadBlock(dl++, G_TX_LOADTILE, 0, 0, 959, 1024);
    gDPPipeSync(dl++);
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(dl++, G_TX_RENDERTILE, 0, 0, 28, 476);
    gSPVertex(dl++, vtx, 4, 0);
    gSP2Triangles(dl++, 2, 1, 0, 0, 3, 2, 0, 0);

    // Bottom
    gDPPipeSync(dl++);
    gDPSetTextureImage(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (void*)((u32)g_menu_framebuffer_bottom));
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(dl++);
    gDPLoadBlock(dl++, G_TX_LOADTILE, 0, 0, 2047, 32);
    gDPPipeSync(dl++);
    gDPSetTile(dl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(dl++, G_TX_RENDERTILE, 0, 0, 1020, 28);
    gSPVertex(dl++, vtx + 12, 4, 0);
    gSP2Triangles(dl++, 2, 1, 0, 0, 3, 2, 0, 0);

    gSPEndDisplayList(dl++);

    return dl - 1;
}
