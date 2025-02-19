#ifndef TYPES_H
#define TYPES_H

#include <ultra64.h>

typedef struct FileSegment FileSegment;
struct FileSegment {
    u32 vram_start;
    u32 vram_end;
};

typedef struct System System;
struct System {
    u8 unknown[0xCF908];
};

typedef struct Vec2f Vec2f;
struct Vec2f {
    f32 x;
    f32 y;
};

typedef struct Vec3f Vec3f;
struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
};

typedef struct Vec3s Vec3s;
struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
};

typedef struct MtxF MtxF;
struct MtxF {
    f32 a[4][4];
};

typedef struct Player Player;
struct Player {
    u8 a[0x1c0];
};

typedef struct HeapElement HeapElement;
struct HeapElement {
    HeapElement* next;
    u8 flags;
    u8 unknown_6;
    u16 unknown_7;
};

typedef struct OverlayInfo OverlayInfo;
struct OverlayInfo {
    u16 file_id;
    u8 unknown_2[2];
    void *vram_addr;
};

typedef struct Object Object;
struct Object {
    HeapElement heap_element;
    Vec3f position;
    Vec3s rotation;
    u8 unknown_1a[2];
    Vec3f scale;
    f32 animation_progress;
    u32 graphics_1; // TODO: Find a better name.
    void *graphics_2; // TODO: Find a better name.
    OverlayInfo overlay_info[6];
    u8 unknown_64;
    s8 unknown_65;
    u8 unknown_66;
    u8 unknown_67;
    s32 unknown_68;
    s32 unknown_6c;
    f32 unknown_70;
    Object *left;
    Object *right;
    u8 unknown_7c[2];
    s16 unknown_7e;
    void *unknown_80;
    u16 unknown_84;
    u8 unknown_86;
    u8 unknown_87;
    Vec3f unknown_88;
    Object *prev;
};

typedef struct Skybox Skybox;
struct Skybox {
    HeapElement heap_element;
    u8 unknown_8[0x4];
    u16 unknown_c;
    u16 unknown_e;
    s16 texture_width;
    s16 texture_height;
    Vec2f start;
    Vec2f upper_left_corner;
    f32 rectangle_width;
    f32 rectangle_height;
    u8 unknown_2c[0x2];
    u16 unknown_2e;
    u16 unknown_30;
    u16 unknown_32;
    u16 unknown_34;
    u8 unknown_36[0x2];
    void *texture;
    void *palette;
    u16 unknown_40;
    u8 unknown_42[0x2];
};

typedef struct Animation Animation;
struct Animation {
    u8 a;
};

typedef struct Skeleton Skeleton;
struct Skeleton {
    u32 display_list_vram_addr;
    s8 offset_right;
    s8 offset_left;
    Vec3s scale;
    Vec3s rotation;
    Vec3s translation;
};

typedef struct AnimatedSkeleton AnimatedSkeleton;
struct AnimatedSkeleton {
    u32 flags;
    Animation *animation;
    Skeleton *skeletons[1]; // Variable size.
};

typedef struct Camera Camera;
struct Camera {
    Vec3f position;
    Vec3f look_at;
    s16 unknown_18;
    s16 unknown_1a;
    Vec3f unknown_1c;
    Vec3f unknown_28;
    f32 unknown_34;
    s32 unknown_38;
    s32 unknown_3c;
    Vp *vp;
    u32 unknown_44;
    u16 scissor_ulx;
    u16 scissor_uly;
    u16 scissor_lrx;
    u16 scissor_lry;
    f32 unknown_50;
    f32 unknown_54;
    f32 unknown_58;
    f32 unknown_5c;
};

typedef struct MyLight MyLight;
struct MyLight {
    u8 a;
};

typedef struct Task Task;
struct Task {
    Task *next;
    Task *previous;
    void (*function_1)(Task *);
    void (*function_2)(Task *);
    void (*function_3)(Task *);
    void (*previous_function)(Task *);
    HeapElement *heap_element;
    HeapElement *heap_element_2;
    u16 priority;
    u16 unknown_22;
    u16 timer;
    u8 unknown_26;
    u8 unknown_27;
    u16 overlay_file_id;
    u8 unknown_2a;
    u8 unknown_2b;
    void *overlay_vram_addr;
    u8 unknown_30;
    u8 unknown_31;
    u8 unknown_32;
    u8 unknown_33;
    u32 unknown_34;
    u32 unknown_38;
    u16 unknown_3c;
    u16 unknown_3e;
    u16 unknown_40;
    u16 unknown_42;
    u8 unknown_44;
    u8 unknown_45;
    u8 unknown_46;
    u8 unknown_47;
    u32 unknown_48;
    u8 unknown_4c;
    u8 unknown_4d;
    u16 unknown_4e;
    u16 unknown_50;
    u16 unknown_52;
    u32 unknown_54;
    u32 unknown_58;
};

typedef struct DummyTask DummyTask;
struct DummyTask {
    Task header;
    u8 padding[0x94];
};

typedef struct PlayerTask PlayerTask;

typedef struct UnknownPlayerTask UnknownPlayerTask;
struct UnknownPlayerTask {
    Task header;
    PlayerTask *player_task;
};

typedef struct PlayerTask PlayerTask;
struct PlayerTask {
    Task header;
    Player *player;
    u8 character_id;
    s8 unknown_61;
    u8 unknown[2];
    DummyTask *camera_task;
    f32 unknown_68;
    f32 unknown_6c;
    f32 unknown_70;
    f32 unknown_74;
    f32 unknown_78;
    f32 unknown_7c;
    u8 unknown_80[4];
    f32 unknown_84;
    f32 unknown_88;
    f32 unknown_8c;
    u8 player_id;
    u8 unknown_91;
    u8 unknown_92[2];
    u16 unknown_94;
    s16 unknown_96;
    s16 unknown_98;
    s16 unknown_9a;
    s32 unknown_9c;
    s32 unknown_a0;
    f32 unknown_a4;
    f32 unknown_a8;
    f32 unknown_ac;
    f32 unknown_b0;
    f32 unknown_b4;
    f32 unknown_b8;
    f32 unknown_bc;
    f32 unknown_c0;
    f32 unknown_c4;
    f32 unknown_c8;
    u8 action_id;
    u8 unknown_cd;
    u16 unknown_ce;
    f32 unknown_d0;
    s8 unknown_d4;
    u8 unknown_d5[6];
    u8 unknown_db;
    UnknownPlayerTask *unknown_player_task;
    u8 unknown_e0[4];
    s32 unknown_e4;
    s32 unknown_e8;
    u8 unknown_ec[2];
    s16 unknown_ee;
};

typedef struct ActorTask ActorTask;
struct ActorTask {
    Task header; // offset: 0x00, size: 0x5C
    u16 actor_id; // offset: 0x5C
    u16 model_id; // offset: 0x5E
    u8 pad[0x80]; // offset: 0x60, size: 0x80
};


typedef struct ProjectileTask ProjectileTask;
struct ProjectileTask {
    Task header; // offset: 0x00, size: 0x5C
    PlayerTask *player_task; // offset: 0x5C
    s8 unknown_60; // offset: 0x60
    s8 unknown_61; // offset: 0x61
    u16 unknown_62; // offset: 0x62
    u8 unknown_63; // offset: 0x63
    u8 unknown_64[0x38]; // offset: 0x64
    f32 unknown_9c; // offset: 0x9C
    f32 unknown_a0; // offset: 0xA0
    f32 unknown_a4; // offset: 0xA4
    u16 unknown_a8; // offset: 0xA8
    u16 unknown_aa; // offset: 0xAA
};

typedef struct SnowGeneratorTask SnowGeneratorTask;
struct SnowGeneratorTask {
    ActorTask actor_task; // offset: 0x00, size: 0xE0
    Vec3f center_position;
};

typedef struct SpinningSunTask SpinningSunTask;
struct SpinningSunTask {
    Task header; // offset: 0x00, size: 0x5C
    u8 unknown_5c[0x93]; // offset: 0x5C
    u8 initialized; // offset: 0xEF, @recomp Used to check if the widescreen patch has been initialized.
};

typedef struct RipplingBackground RipplingBackground;
struct RipplingBackground {
    u32 unknown_0; // offset: 0x00
    s32 unknown_4; // offset: 0x04
    s32 unknown_8; // offset: 0x08
    s32 unknown_c; // offset: 0x0C
    s32 unknown_10; // offset: 0x10
    f32 unknown_14; // offset: 0x14
    f32 unknown_18; // offset: 0x18
    s32 unknown_1c; // offset: 0x1C
    void (*displacement_map_function)(Task *, Object *); // offset: 0x20
    u8 unknown_24[0xC]; // offset: 0x24
    void *unknown_30; // offset: 0x30
    s32 unknown_34; // offset: 0x34
    f32 unknown_38; // offset: 0x38
    u8 unknown_3c[0x1C]; // offset: 0x3C
    f32 *unknown_58; // offset: 0x58
};

typedef struct RipplingBackgroundTask RipplingBackgroundTask;
typedef struct RipplingBackgroundTask RipplingHikimakuTask;
typedef struct RipplingBackgroundTask RipplingKarakusaTask;
struct RipplingBackgroundTask {
    Task header; // offset: 0x00, size: 0x5C
    u8 unknown_5c[0x2e]; // offset: 0x5C
    u8 unknown_8a; // offset: 0x8A
    u8 unknown_8b; // offset: 0x8B
    u8 unknown_8c[0x44]; // offset: 0x8C
    RipplingBackground *rippling_background; // offset: 0xD0
    u8 unknown_d4[0x1b]; // offset: 0xD4
    u8 initialized; // offset: 0xEF, @recomp Used to check if the widescreen patch has been initialized.
};

typedef struct PICDecompressor PICDecompressor;
struct PICDecompressor {
    s32 width;
    s32 height;
    s32 color_depth;
    u32 decompressed_size;
    s32 has_palette;
    u32 background_color;
    u8 *data;
    void *destination;
    u16 *palette;
};

#endif // TYPES_H
