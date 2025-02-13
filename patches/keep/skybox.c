#include "patches.h"

/*
RECOMP_PATCH void func_80022500_23100(u32 ulx, u32 uly, u32 scroll_x, u32 scroll_y, s32 rectangle_width, s32 rectangle_height, Skybox *skybox) {
    u16 flags;
    s32 image_format;

    flags = skybox->unknown_e;
    
    if (flags & 1) {
        image_format = G_IM_FMT_CI;
    } else if (flags & 2) {
        image_format = G_IM_FMT_IA;
    } else {
        image_format = G_IM_FMT_RGBA;
    }

    if (flags & 4) {
        gDPLoadTextureTile(D_8015C5CC_15D1CC++, skybox->texture, G_IM_FMT_CI, G_IM_SIZ_8b, skybox->texture_width, skybox->texture_height, scroll_x, scroll_y, (scroll_x + rectangle_width - 1), (scroll_y + rectangle_height - 1), 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else if (flags & 8) {
        gDPLoadTextureTile(
            D_8015C5CC_15D1CC++, 
            skybox->texture, 
            image_format, G_IM_SIZ_8b, 
            skybox->texture_width, skybox->texture_height, 
            scroll_x, scroll_y, 
            (scroll_x + rectangle_width - 1), (scroll_y + rectangle_height - 1), 
            0, 
            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
            G_TX_NOMASK, G_TX_NOMASK, 
            G_TX_NOLOD, G_TX_NOLOD
        );
    } else {
        gDPLoadTextureTile(D_8015C5CC_15D1CC++, skybox->texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, skybox->texture_width, skybox->texture_height, scroll_x, scroll_y, (scroll_x + rectangle_width - 1), (scroll_y + rectangle_height - 1), 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    gSPTextureRectangle(D_8015C5CC_15D1CC++, (ulx + rectangle_width) << 2, (uly + rectangle_height) << 2, ulx << 2, uly << 2, G_TX_RENDERTILE, scroll_x << 5, scroll_y << 5, 1 << 10, 1 << 10);
}
*/
