#include <ultra64.h>

typedef struct {
    Gfx display_lists[10640];
    Mtx matrices[540];
    Vp viewports[4];
    u8 unk_1d3c0[600];
    u8 unk_1d618[128];
    u8 unk_1d698[64];
} GraphicsPool;

typedef struct {
    u16 status;
    u16 button_held_down;
    u16 button_pressed;
    s16 stick_raw_x;
    s16 stick_raw_y;
    u8 unknown[2];
    f32 stick_x;
    f32 stick_y;
    f32 stick_magnitude;
} Controller;

typedef struct {
    GraphicsPool graphics_pools[2];
    s16 current_frame_buffer;
    s16 current_graphics_pool;
    s16 file_loader_working_graphics_pool;
    s16 disable_graphics_tasks;
    s16 frames_elapsed;
    u16 fill_color_red;
    u16 fill_color_green;
    u16 fill_color_blue;
    u16 fill_color_alpha;
    u16 frame_buffer_bits_per_pixel;
    s16 clear_depth_buffer;
    u8 unk_3adc6[2];
    s16 dont_process_draw_lists;
    u8 retraces_per_game_step;
    u8 unk_3adcb;
    u16 retrace_count;
    s16 game_loops_count;
    u16 attrack_demo_frames_elapsed;
    u16 unk_3add2;
    u8 mode;
    u8 unk_3add5[0x2A3];
    Controller controllers[4];
} System;
