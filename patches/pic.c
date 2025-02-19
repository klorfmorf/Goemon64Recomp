#include "patches.h"

/*
u32 func_800161F0_16DF0(s32 row, s32 column);
void func_800162F4_16EF4(s32 row, s32 column);

RECOMP_PATCH void func_800165C4_171C4(PICDecompressor *pic_decompressor) {
    s32 row, column;
    u32 color;

    for (row = 0; row < pic_decompressor->height; row++) {
        for (column = 0; column < pic_decompressor->width; column++) {
            color = func_800161F0_16DF0(row, column) & 0xFFFE;

            if (pic_decompressor->background_color == color) {
                func_800162F4_16EF4(row, column);
            }
        }
    }
}
    
u8 *func_800145B4_151B4(u32 file_id, u8 *data);
void func_80014D70_15970(u8 *data, PICDecompressor *pic_decompressor);
void func_80014DD8_159D8(u8 *data, u8 *destination, PICDecompressor *pic_decompressor);

extern s32 D_80168174_168D74;
extern s32 D_80168178_168D78;
extern u8 *D_8016848C_16908C;

RECOMP_PATCH u8 *func_800144E8_150E8(u32 file_id, u8 *data, u8 *destination) {
    u8 *data_end;
    u8 *destination_end;
    PICDecompressor pic_decompressor;

    data_end = func_800145B4_151B4(file_id, data);

    if (data[0] == 'P' && data[1] == 'I' && data[2] == 'C') {
        func_80014D70_15970(data, &pic_decompressor);
        func_80014DD8_159D8(data, destination, &pic_decompressor);

        destination_end = destination + pic_decompressor.decompressed_size;
    }

    return destination_end;
}
*/