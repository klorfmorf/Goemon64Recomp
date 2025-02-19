#include "patches.h"

static const f32 g_original_aspect_ratio = (f32)SCREEN_WIDTH / (f32)SCREEN_HEIGHT;

static f32 g_spinning_sun_previous_aspect_ratio = 0.0f;

// @recomp Patched to accomodate the spinning sun effect for widescreen.
RECOMP_PATCH void func_80214530_69BF30(SpinningSunTask *task, Object *object) {
    f32 current_aspect_ratio = patch_api_get_aspect_ratio(g_original_aspect_ratio);
    if ((current_aspect_ratio != g_spinning_sun_previous_aspect_ratio || task->initialized == FALSE) && current_aspect_ratio != 0.0f) {
        object->scale.x = 1.0f * (current_aspect_ratio / g_original_aspect_ratio);
        object->scale.z = 1.0f * (current_aspect_ratio / g_original_aspect_ratio);

        g_spinning_sun_previous_aspect_ratio = current_aspect_ratio;
        task->initialized = TRUE;
    }

    object->rotation.z -= 2;
    object->rotation.z &= 0x3FF;
}

static f32 g_rippling_hikimaku_previous_aspect_ratio = 0.0f;

// @recomp Patched to accomodate the rippling hikimaku background for widescreen.
RECOMP_PATCH void func_801CC710_65F5C0(RipplingHikimakuTask *task, Object *object) {
    f32 current_aspect_ratio = patch_api_get_aspect_ratio(g_original_aspect_ratio);

    if ((current_aspect_ratio != g_rippling_hikimaku_previous_aspect_ratio || task->initialized == FALSE) && current_aspect_ratio != 0.0f) {
        object->scale.x = 0.2f * (current_aspect_ratio / g_original_aspect_ratio);
        object->scale.z = 0.2f * (current_aspect_ratio / g_original_aspect_ratio);

        g_rippling_hikimaku_previous_aspect_ratio = current_aspect_ratio;
        task->initialized = TRUE;
    }

    RipplingBackground *rippling_background = task->rippling_background;
    s32 row, column;
    s32 grid_width = rippling_background->unknown_4 + 2;
    s32 grid_height = rippling_background->unknown_8 + 2;
    u16 game_loops_ran;
    f64 phase_1;
    f32 wave_x;
    f64 phase_2;
    f32 wave_y;

    for (row = 0; row < grid_height; row++) {
        for (column = 0; column < grid_width; column++) {
            game_loops_ran = *(u16 *)(&D_8015C5C8_15D1C8->unknown[0x3ADCE]);

            phase_1 = (game_loops_ran * D_801D42E0_667190 * 2.0) + (column * 5.0) + (rippling_background->unknown_8 - row) * 5.0 + 5.0;

            wave_x = func_80003E10_4A10((s32)(phase_1 * 9.0) & 0x3FF);

            phase_2 = (game_loops_ran * D_801D42E0_667190 * 2.0) + (column * 8.0) + (rippling_background->unknown_8 - row) * 8.0 + 8.0;

            wave_y = func_80003E10_4A10((s32)(phase_2 * 14.0) & 0x3FF);

            rippling_background->unknown_58[row * grid_width + column] = (wave_x + wave_y) * 200.0f;
        }
    }
}