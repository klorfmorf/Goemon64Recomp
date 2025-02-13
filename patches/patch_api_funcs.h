#ifndef PATCH_API_FUNCS_H
#define PATCH_API_FUNCS_H

#include "patch_helpers.h"

DECLARE_FUNC(void, patch_api_load_overlays, u32 rom_addr, void *vram_addr, u32 size);
DECLARE_FUNC(void, patch_api_unload_overlays, void *vram_addr, u32 size);
DECLARE_FUNC(float, patch_api_get_aspect_ratio, float original);

#endif // PATCH_API_FUNCS_H
