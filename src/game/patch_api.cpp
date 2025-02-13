#include "recomp.h"
#include "recomp_ui.h"
#include "librecomp/overlays.hpp"
#include "librecomp/helpers.hpp"
#include "ultramodern/ultramodern.hpp"

extern "C" void patch_api_load_overlays(uint8_t *rdram, recomp_context *ctx) {
    u32 rom_addr = _arg<0, u32>(rdram, ctx);
    PTR(void) vram_addr = _arg<1, PTR(void)>(rdram, ctx);
    u32 size = _arg<2, u32>(rdram, ctx);

    load_overlays(rom_addr, vram_addr, size);
}

extern "C" void patch_api_unload_overlays(uint8_t *rdram, recomp_context *ctx) {
    PTR(void) vram_addr = _arg<0, PTR(void)>(rdram, ctx);
    u32 size = _arg<1, u32>(rdram, ctx);

    unload_overlays(vram_addr, size);
}

extern "C" void patch_api_get_aspect_ratio(uint8_t* rdram, recomp_context* ctx) {
    ultramodern::renderer::GraphicsConfig graphics_config = ultramodern::renderer::get_graphics_config();
    float original = _arg<0, float>(rdram, ctx);
    int width, height;
    recompui::get_window_size(width, height);

    switch (graphics_config.ar_option) {
        case ultramodern::renderer::AspectRatio::Original:
        default:
            _return(ctx, original);
            return;
        case ultramodern::renderer::AspectRatio::Expand:
            _return(ctx, std::max(static_cast<float>(width) / height, original));
            return;
    }
}
