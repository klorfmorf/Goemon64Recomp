#ifndef GAME_VARS_H
#define GAME_VARS_H

#include "types.h"
#include "macros.h"

extern Object *D_801684A0_1690A0;
extern MtxF D_801684B0_1690B0;
extern void *D_801684F0_1690F0;
extern f32 D_80168510_169110;
extern f32 D_80168514_169114;
extern f32 D_80168518_169118;
extern s32 D_8016851C_16911C;
extern void *D_80168520_169120;
extern s32 D_80168524_169124;
extern u8 D_8016852C_16912C;
extern u8 D_8016852D_16912D;
extern MtxF *D_80168530_169130;
extern FileSegment D_80054ACC_556CC[FILE_MAX]; // g_file_segments
extern u32 D_800573D8_57FD8[FILE_MAX]; // g_file_rom_addrs
extern u8 D_8015C5D4_15D1D4; // g_is_loading_file
extern SYS_W D_8008CCC0_8D8C0; // g_system
extern SYS_W* D_8015C5C8_15D1C8; // g_system_p
extern Gfx *D_8015C5CC_15D1CC; // g_display_list_head
extern Gfx D_8006D4E0_6E0E0[5]; // ?
extern Object D_8005B974_5C574;
extern f32 D_8020B834_5C7744;
extern PlayerTask *D_801FC604_5B8514; // g_player_1_task
extern PlayerTask *D_801FC608; // g_player_2_task
extern Object *D_801FC60C_5B851C; // g_player_1_object
extern Object *D_801FC610_5B8520; // g_player_2_object
extern Object *D_801FC614_5B8524; // g_player_1_root_object
extern Object *D_801FC618_5B8528; // g_player_2_root_object
extern Object *D_801FC61C_5B852C; // g_player_1_shadow_object
extern Object *D_801FC620_5B8530; // g_player_2_shadow_object
extern DummyTask *D_801FC624_5B8534; // g_camera_task
extern UnknownPlayerTask *D_801FC638_5B8548; // g_unknown_player_task_1
extern UnknownPlayerTask *D_801FC63C_5B854C; // g_unknown_player_task_2
extern u16 D_80204020_5BFF30[4]; // g_character_graphics_file_ids
extern f32 D_8020A6DC_5C65EC; // g_player_default_scale
extern void *D_8020D220_5C9130[2]; // g_player_graphics_buffers
extern u8 D_8020D260_5C9170[2];
extern u8 D_8020C860_5C8770[0x1C0];
extern u8 D_801FC640_5B8550[0x20];
extern u32 D_8015C5DC_15D1DC; // g_current_player_character_id
extern f64 D_801D42E0_667190; // g_rippling_hikimaku_coefficient
extern f64 D_80217938_6768E8; // g_rippling_karakusa_coefficient

#endif // GAME_VARS_H
