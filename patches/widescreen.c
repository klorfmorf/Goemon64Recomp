#include "patches.h"

static const f32 g_original_aspect_ratio = (f32)SCREEN_WIDTH / (f32)SCREEN_HEIGHT;
static f32 g_previous_aspect_ratio = 0.0f;

// @recomp Patched to accomodate the spinning sun effect for widescreen.
RECOMP_PATCH void func_80214530_69BF30(SpinningSunTask *task, Object *object) {
    f32 current_aspect_ratio = patch_api_get_aspect_ratio(g_original_aspect_ratio);
    if ((current_aspect_ratio != g_previous_aspect_ratio || task->initialized == FALSE) && current_aspect_ratio != 0.0f) {
        object->scale.x = 1.0f * (current_aspect_ratio / g_original_aspect_ratio);
        object->scale.z = 1.0f * (current_aspect_ratio / g_original_aspect_ratio);

        g_previous_aspect_ratio = current_aspect_ratio;
        task->initialized = TRUE;
    }

    object->rotation.z -= 2;
    object->rotation.z &= 0x3FF;
}
