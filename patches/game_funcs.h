#ifndef GAME_FUNCS_H
#define GAME_FUNCS_H

#include "types.h"
#include "macros.h"

void func_80016AA4_176A4();
void func_800176F0_182F0(Skeleton *skeleton, MtxF *matrix);
void func_80017D8C_1898C(Camera *camera, MtxF *matrix);
void func_800182DC_18EDC(Skeleton *skeleton);
void func_800184B4_190B4(void *object_type_5);
void func_800185C8_191C8(MyLight *light);
void func_80018718_19318(Skeleton *skeleton, u32 object_type);
void func_80018908_19508(Skeleton *skeleton);
void func_80018B28_19728(Skeleton *skeleton, u32 object_type, Object *object);
Object *func_80018F3C_19B3C(Skeleton *skeleton, Object *object);
Object *func_8001904C_19C4C(Skeleton *skeleton, Object *object);
void func_800192D0_19ED0(Skeleton *skeleton, Object *object);
void func_800196A4_1A2A4();
void func_800196F0_1A2F0(Gfx *display_list);
void func_80019D40_1A940(Object *object);
void func_8001B6D4_1C2D4(Camera *camera);
void func_8001E380_1EF80(MtxF *matrix, Object *object);
s32 func_800364FC_370FC(Object *object);
s32 func_8003674C_3734C(Object *object);
s32 func_80036798_37398(Object *object);
void func_800042AC_4EAC(s16 entry, const char* string, s16 x, s16 y); // text_labels_add_ascii_entry
void func_800042F4_4EF4(s16 entry, u32 number, s16 x, s16 y); // text_labels_add_hexadecimal_entry
u8 *func_80001C00_2800(u32 file_id, u8 *buf_start); // file_load
u32 func_80001DF4_29F4(u32 file_id); // file_is_code_ovl
u32 func_80001EB0_2AB0(u32 file_id, u32 vram_addr); // file_map_tlb_ovl
void func_80001640_2240(u32 rom_addr, void *vram_addr, u32 size); // memory_dma_transfer_rom_to_ram
u8 *func_80005394_5F94(u32 rom_addr, u8 *vram_addr, u32 size); // memory_decompress
void func_800012FC_1EFC(); // main_initialize_display_lists
void func_801CB5D0_5874E0(DummyTask *player_manager_task);
void func_801CB800_587710(PlayerTask *player_task);
void func_801DAF54_596E64(PlayerTask *player_task);
void func_801E8EC4_5A4DD4(DummyTask *unknown_task);
void func_80013940_14540();
void *func_800141C4_14DC4(u32 file_id);
void func_8001C9BC_1D5BC(Object *object_1, Object *object_2);
HeapElement *func_80035EEC_36AEC(Task* task, s16 type, u8 count);
void func_801CB7D4_5876E4(DummyTask *task);
void func_801CBC40_587B50();
void func_801D23D4_58E2E4();
void func_801D9B78_595A88(Object *object);
void func_801DC9C8_5988D8(PlayerTask* task, u8 character_id);
void func_801DCA64_598974(PlayerTask* task, u32 something, u8 *something_else);
Task *func_80034E08_35A08(Task *task, void (*func)(Task *task), u16 overlay_file_id);
void func_8003521C_35E1C(void (*function)(Task *, Object *));
Task *func_800358E8_364E8(Task *task, void (*func)(Task *task), u32 graphics_1_vram_addr, u32 graphics_2_vram_addr, f32 pos_x, f32 pos_y, f32 pos_z, s16 rot_x, s16 rot_y, s16 rot_z, f32 scale_x, f32 scale_y, f32 scale_z, u16 overlay_file_id_1, u16 overlay_file_id_2);
void func_801E8858_5A4768(Object *object, u16 type);
void func_801ED420_5A9330(ProjectileTask *task);
HeapElement *func_80036158_36D58(Task* task, HeapElement *heap_element, s8 count);
HeapElement *func_80035FDC_36BDC(HeapElement *heap_element);
void func_80036308_36F08(HeapElement *heap_element);
s32 func_802192B4_5D4784(s32 seed);
u32 func_80023E94_24A94(u32 event_id);
f32 func_80003E10_4A10(s32 value); // math_sin

#endif // GAME_FUNCS_H
