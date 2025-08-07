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

/*
extern Object *func_800119D4_125D4(Task *task, u8 draw_layer);
extern void *func_80014840_15440(void *virtual_address, u32 file_id);
extern void func_80024160_24D60(RipplingBackgroundTask *task, Object *object);
extern RipplingBackground *func_80024670_25270();
extern void func_80035020_35C20();
extern void func_801CC710_65F5C0(RipplingHikimakuTask *task, Object *object);

extern f32 D_801D42E8_667198;
extern f32 D_801D42EC_66719C;
extern f32 D_801D42F0_6671A0;
extern RipplingHikimakuTask *D_801E8704_67B5B4;

RECOMP_PATCH void func_801CC978_65F828(RipplingHikimakuTask *task, Object *object) {
    RipplingBackground *rippling_background = func_80024670_25270();
    Object *child_object; 

    if (rippling_background == NULL) {
        func_80035020_35C20();
        return;
    }

    D_801E8704_67B5B4 = task;

    task->rippling_background = rippling_background;

    rippling_background->unknown_4 = 15;
    rippling_background->unknown_8 = 15;
    rippling_background->unknown_c = 2000;
    rippling_background->unknown_10 = 2000;
    rippling_background->unknown_0 = 3587;
    rippling_background->unknown_30 = func_80014840_15440((void *)(0x08001D10), 1229);
    rippling_background->unknown_38 = 5.0f;
    rippling_background->unknown_14 = D_801D42E8_667198;
    rippling_background->unknown_18 = D_801D42EC_66719C;

    child_object = func_800119D4_125D4((Task *)task, 9);
    child_object->rotation.x = 0x100;
    child_object->rotation.y = 0;
    child_object->rotation.z = 0;
    child_object->heap_element.flags = 3;
    child_object->scale.x = D_801D42F0_6671A0;
    child_object->scale.y = D_801D42F0_6671A0;
    child_object->scale.z = D_801D42F0_6671A0;
    child_object->position.x = 10.0f;
    child_object->position.y = 0.0f;
    child_object->position.z = -300.0f;

    task->unknown_8a = 0;
    // task->unknown_8b = 0;

    rippling_background->unknown_1c = 0;
    rippling_background->displacement_map_function = (void (*)(Task *, Object *))&func_801CC710_65F5C0;

    func_8003521C_35E1C((void (*)(Task *, Object *))&func_80024160_24D60);
}
*/

static f32 g_rippling_hikimaku_previous_aspect_ratio = 0.0f;

// @recomp Patched to accomodate the rippling hikimaku background for widescreen.
RECOMP_PATCH void func_801CC710_65F5C0(RipplingHikimakuTask *task, Object *object) {
    f32 current_aspect_ratio = patch_api_get_aspect_ratio(g_original_aspect_ratio);
    RipplingBackground *rippling_background = task->rippling_background;
    s32 row, column;
    s32 grid_width = rippling_background->unknown_4 + 2;
    s32 grid_height = rippling_background->unknown_8 + 2;
    u16 game_loops_ran;
    f64 phase_1;
    f32 wave_x;
    f64 phase_2;
    f32 wave_y;

    if ((current_aspect_ratio != g_rippling_hikimaku_previous_aspect_ratio || task->initialized == FALSE) && current_aspect_ratio != 0.0f) {
        object->scale.x = 0.2f * (current_aspect_ratio / g_original_aspect_ratio);
        object->scale.z = 0.2f * (current_aspect_ratio / g_original_aspect_ratio);

        g_rippling_hikimaku_previous_aspect_ratio = current_aspect_ratio;
        task->initialized = TRUE;
    }

    TAGGING_OBJECT_SET_INTERPOLATE_VERTICES(object);

    for (row = 0; row < grid_height; row++) {
        for (column = 0; column < grid_width; column++) {
            game_loops_ran = D_8015C5C8_15D1C8->game_loops_count;

            phase_1 = (game_loops_ran * D_801D42E0_667190 * 2.0) + (column * 5.0) + (rippling_background->unknown_8 - row) * 5.0 + 5.0;
            wave_x = func_80003E10_4A10((s32)(phase_1 * 9.0) & 0x3FF);

            phase_2 = (game_loops_ran * D_801D42E0_667190 * 2.0) + (column * 8.0) + (rippling_background->unknown_8 - row) * 8.0 + 8.0;
            wave_y = func_80003E10_4A10((s32)(phase_2 * 14.0) & 0x3FF);

            rippling_background->unknown_58[row * grid_width + column] = (wave_x + wave_y) * 200.0f;
        }
    }
}

static f32 g_rippling_karakusa_previous_aspect_ratio = 0.0f;

// @recomp Patched to accomodate the rippling karakusa background for widescreen.
RECOMP_PATCH void func_80213AC8_672A78(RipplingKarakusaTask *task, Object *object) {
    f32 current_aspect_ratio = patch_api_get_aspect_ratio(g_original_aspect_ratio);
    RipplingBackground *rippling_background = task->rippling_background;
    s32 row, column;
    s32 grid_width = rippling_background->unknown_4 + 2;
    s32 grid_height = rippling_background->unknown_8 + 2;
    u16 game_loops_ran;
    f64 phase_1;
    f32 wave_x;
    f64 phase_2;
    f32 wave_y;
    
    if ((current_aspect_ratio != g_rippling_hikimaku_previous_aspect_ratio || task->initialized == FALSE) && current_aspect_ratio != 0.0f) {
        object->scale.x = 0.2f * (current_aspect_ratio / g_original_aspect_ratio);
        object->scale.z = 0.2f * (current_aspect_ratio / g_original_aspect_ratio);

        g_rippling_hikimaku_previous_aspect_ratio = current_aspect_ratio;
        task->initialized = TRUE;
    }

    TAGGING_OBJECT_SET_INTERPOLATE_VERTICES(object);

    for (row = 0; row < grid_height; row++) {
        for (column = 0; column < grid_width; column++) {
            game_loops_ran = D_8015C5C8_15D1C8->game_loops_count;

            phase_1 = (game_loops_ran * D_80217938_6768E8 * 2.0) + (column * 5.0) + (rippling_background->unknown_8 - row) * 5.0 + 5.0;
            wave_x = func_80003E10_4A10((s32)(phase_1 * 9.0) & 0x3FF);

            phase_2 = (game_loops_ran * D_80217938_6768E8 * 2.0) + (column * 8.0) + (rippling_background->unknown_8 - row) * 8.0 + 8.0;
            wave_y = func_80003E10_4A10((s32)(phase_2 * 14.0) & 0x3FF);

            rippling_background->unknown_58[row * grid_width + column] = (wave_x + wave_y) * 200.0f;
        }
    }
}