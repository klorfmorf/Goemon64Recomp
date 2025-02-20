#include "patches.h"

u32 func_800161F0_16DF0(s32 row, s32 column);
void func_800162F4_16EF4(s32 row, s32 column);

/*
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
*/

u8 *func_800145B4_151B4(u32 file_id, u8 *data);
void func_80014D70_15970(u8 *data, PICDecompressor *pic_decompressor);
void func_80014DD8_159D8(u8 *data, u8 *destination, PICDecompressor *pic_decompressor);

extern s32 D_80168174_168D74;
extern s32 D_80168178_168D78;
extern u8 *D_8016848C_16908C;

s32 g_pic_ci4_sum_r[16];
s32 g_pic_ci4_sum_g[16];
s32 g_pic_ci4_sum_b[16];
s32 g_pic_ci4_count[16];

s32 g_pic_ci8_sum_r[256];
s32 g_pic_ci8_sum_g[256];
s32 g_pic_ci8_sum_b[256];
s32 g_pic_ci8_count[256];

static inline void* memcpy(void* s1, const void* s2, size_t n) {
    char* su1 = (char*)s1;
    const char* su2 = (const char*)s2;
    while (n > 0) {
        *su1 = *su2;
        su1++;
        su2++;
        n--;
    }
    return (void*)s1;
}

void pic_fix_texture_alphas_rgba16(u8 *destination, PICDecompressor *pic_decompressor) {
    s32 row, column;
    const s32 width = pic_decompressor->width;
    const s32 height = pic_decompressor->height;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            u16 *pixel = &((u16 *)destination)[row * width + column];
            u8 a = *pixel & 0x1; // Alpha is LSB

            if (a == 0) {
                s32 sum_r = 0, sum_g = 0, sum_b = 0;
                s32 count = 0;

                // Check 3x3 neighborhood
                for (s32 dy = -1; dy <= 1; dy++) {
                    for (s32 dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue;
                        s32 nx = column + dx;
                        s32 ny = row + dy;
                        
                        if (nx >= 0 && nx < width &&
                            ny >= 0 && ny < height) {
                            u16 neighbor = ((u16 *)destination)[ny * width + nx];
                            if (neighbor & 0x1) { // Opaque neighbor
                                sum_r += (neighbor >> 11) & 0x1F;
                                sum_g += (neighbor >> 6) & 0x1F;
                                sum_b += (neighbor >> 1) & 0x1F;
                                count++;
                            }
                        }
                    }
                }

                if (count > 0) {
                    u16 new_r = (sum_r + count/2) / count;
                    u16 new_g = (sum_g + count/2) / count;
                    u16 new_b = (sum_b + count/2) / count;
                    *pixel = (new_r << 11) | (new_g << 6) | (new_b << 1);
                }
            }
        }
    }
}

void pic_fix_texture_alphas_ia8(u8 *destination, PICDecompressor *pic_decompressor) {
    s32 row, column;
    const s32 width = pic_decompressor->width;
    const s32 height = pic_decompressor->height;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            u8 *pixel = &destination[row * width + column];
            const u8 a = *pixel & 0x0F;
            
            if (a == 0) {
                s32 sum_i = 0;
                s32 count = 0;

                for (s32 dy = -1; dy <= 1; dy++) {
                    for (s32 dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue;
                        const s32 nx = column + dx;
                        const s32 ny = row + dy;
                        
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            const u8 *n_pixel = &destination[ny * width + nx];
                            const u8 n_a = *n_pixel & 0x0F;
                            
                            if (n_a > 0) {
                                sum_i += (*n_pixel >> 4) & 0x0F;
                                count++;
                            }
                        }
                    }
                }

                if (count > 0) {
                    *pixel = (((sum_i + count/2) / count) << 4);
                }
            }
        }
    }
}

void pic_fix_texture_alphas_ci8(u8 *destination, PICDecompressor *pic_decompressor) {
    s32 row, column;
    const s32 width = pic_decompressor->width;
    const s32 height = pic_decompressor->height;
    
    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            const u8 idx = destination[row * width + column];
            const u16 color = pic_decompressor->palette[idx];
            
            if (!(color & 0x1)) {  // Transparent pixel
                for (s32 dy = -1; dy <= 1; dy++) {
                    for (s32 dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue;
                        const s32 nx = column + dx;
                        const s32 ny = row + dy;
                        
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            const u8 n_idx = destination[ny * width + nx];
                            const u16 n_color = pic_decompressor->palette[n_idx];
                            
                            if (n_color & 0x1) {  // Opaque neighbor
                                g_pic_ci8_sum_r[idx] += (n_color >> 11) & 0x1F;
                                g_pic_ci8_sum_g[idx] += (n_color >> 6) & 0x1F;
                                g_pic_ci8_sum_b[idx] += (n_color >> 1) & 0x1F;
                                g_pic_ci8_count[idx]++;
                            }
                        }
                    }
                }
            }
        }
    }

    // Update palette entries
    for (int i = 0; i < 256; i++) {
        if (!(pic_decompressor->palette[i] & 0x1) && g_pic_ci8_count[i] > 0) {
            const u16 new_color = ((g_pic_ci8_sum_r[i]/g_pic_ci8_count[i]) << 11) |
                                ((g_pic_ci8_sum_g[i]/g_pic_ci8_count[i]) << 6) |
                                ((g_pic_ci8_sum_b[i]/g_pic_ci8_count[i]) << 1);
            pic_decompressor->palette[i] = new_color;
        }
    }
}

void pic_fix_texture_alphas_ia4(u8 *destination, PICDecompressor *pic_decompressor) {
    s32 row, column;
    const s32 width = pic_decompressor->width;
    const s32 height = pic_decompressor->height;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            const u32 byte_idx = (row * width + column) >> 1;
            const u8 shift = (column & 1) ? 0 : 4;
            u8 pixel = (destination[byte_idx] >> shift) & 0x0F;
            
            if (!(pixel & 0x1)) {  // Transparent pixel
                s32 sum_i = 0;
                s32 count = 0;

                for (s32 dy = -1; dy <= 1; dy++) {
                    for (s32 dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue;
                        const s32 nx = column + dx;
                        const s32 ny = row + dy;
                        
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            const u32 n_byte_idx = (ny * width + nx) >> 1;
                            const u8 n_shift = (nx & 1) ? 0 : 4;
                            const u8 n_pixel = (destination[n_byte_idx] >> n_shift) & 0x0F;
                            
                            if (n_pixel & 0x1) {  // Opaque neighbor
                                sum_i += (n_pixel >> 1) & 0x7;
                                count++;
                            }
                        }
                    }
                }

                if (count > 0) {
                    const u8 new_i = (sum_i + count/2) / count;
                    destination[byte_idx] &= ~(0x0F << shift);
                    destination[byte_idx] |= ((new_i << 1) << shift);
                }
            }
        }
    }
}

void pic_fix_texture_alphas_ci4(u8 *destination, PICDecompressor *pic_decompressor) {
    s32 row, column;
    const s32 width = pic_decompressor->width;
    const s32 height = pic_decompressor->height;
    
    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            const u32 byte_idx = (row * width + column) >> 1;
            const u8 shift = (column & 1) ? 0 : 4;
            const u8 idx = (destination[byte_idx] >> shift) & 0x0F;
            const u16 color = pic_decompressor->palette[idx];
            
            if (!(color & 0x1)) {  // Transparent pixel
                for (s32 dy = -1; dy <= 1; dy++) {
                    for (s32 dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue;
                        const s32 nx = column + dx;
                        const s32 ny = row + dy;
                        
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            const u32 n_byte_idx = (ny * width + nx) >> 1;
                            const u8 n_shift = (nx & 1) ? 0 : 4;
                            const u8 n_idx = (destination[n_byte_idx] >> n_shift) & 0x0F;
                            const u16 n_color = pic_decompressor->palette[n_idx];
                            
                            if (n_color & 0x1) {  // Opaque neighbor
                                g_pic_ci4_sum_r[idx] += (n_color >> 11) & 0x1F;
                                g_pic_ci4_sum_g[idx] += (n_color >> 6) & 0x1F;
                                g_pic_ci4_sum_b[idx] += (n_color >> 1) & 0x1F;
                                g_pic_ci4_count[idx]++;
                            }
                        }
                    }
                }
            }
        }
    }

    // Update palette entries
    for (int i = 0; i < 16; i++) {
        if (!(pic_decompressor->palette[i] & 0x1) && g_pic_ci4_count[i] > 0) {
            const u16 new_color = ((g_pic_ci4_sum_r[i]/g_pic_ci4_count[i]) << 11) |
                                ((g_pic_ci4_sum_g[i]/g_pic_ci4_count[i]) << 6) |
                                ((g_pic_ci4_sum_b[i]/g_pic_ci4_count[i]) << 1);
            pic_decompressor->palette[i] = new_color;
        }
    }
}

void pic_fix_texture_alphas(u8 *destination, PICDecompressor *pic_decompressor) {
    s32 row, column;
    const s32 width = pic_decompressor->width;
    const s32 height = pic_decompressor->height;

    if (pic_decompressor->color_depth == 16 || pic_decompressor->color_depth == 15) {
        // RGBA16 (RGBA 16-bit)
        pic_fix_texture_alphas_rgba16(destination, pic_decompressor);
    } else if (pic_decompressor->color_depth == 8) {
        if (pic_decompressor->has_palette == 1) {
            // CI8 (Color Indexed 8-bit)
            pic_fix_texture_alphas_ci8(destination, pic_decompressor);
        } else {
            // IA8 (Intensity-Alpha 8-bit)
            pic_fix_texture_alphas_ia8(destination, pic_decompressor);
        }
    } else if (pic_decompressor->color_depth == 4) {
        if (pic_decompressor->has_palette == 1) {
            // CI4 (Color Indexed 4-bit)
            pic_fix_texture_alphas_ci4(destination, pic_decompressor);

        } else {
            // IA4 (Intensity-Alpha 4-bit)
            pic_fix_texture_alphas_ia4(destination, pic_decompressor);
        }
    } 
}

#define TEXTURE_ID_IMPACT_HUD_NUMBERS_BEGIN 0x859F
#define TEXTURE_ID_IMPACT_HUD_NUMBERS_END 0x85A8

RECOMP_PATCH u8 *func_800144E8_150E8(u32 texture_id, u8 *data, u8 *destination) {
    u8 *data_end;
    u8 *destination_end;
    PICDecompressor pic_decompressor;

    data_end = func_800145B4_151B4(texture_id, data);

    if (data[0] == 'P' && data[1] == 'I' && data[2] == 'C') {
        func_80014D70_15970(data, &pic_decompressor);
        func_80014DD8_159D8(data, destination, &pic_decompressor);

        // Don't fix alphas for Impact HUD numbers since they rely on black outlines to look good.
        if (!(texture_id >= TEXTURE_ID_IMPACT_HUD_NUMBERS_BEGIN && texture_id <= TEXTURE_ID_IMPACT_HUD_NUMBERS_END)) {
            pic_fix_texture_alphas(destination, &pic_decompressor);
        }

        destination_end = destination + pic_decompressor.decompressed_size;
    } else {
        if (data_end != data) {
            memcpy(destination, data, data_end - data);
            destination_end = destination + (data_end - data);
        }
    }

    return destination_end;
}