#include "patches.h"

// @recomp Patched to load the overlay in the recomp runtime.
RECOMP_PATCH u8 *func_80001C00_2800(u32 file_id, u8 *buf_start) {
    s32 cur_file_id;
    s32 next_file_id;
    u32 file_rom_addr;
    u32 file_size;
    u32 file_size_aligned;
    u32 vram_start;
    u32 vram_end;
    u8 *buf_cur;
    u8 *buf_end;
    u8 was_loading_file;

    was_loading_file = D_8015C5D4_15D1D4;

    if (file_id < FILE_MAX && file_id != FILE_NONE) {
        cur_file_id = file_id - 1;
        next_file_id = file_id;
        file_rom_addr = D_800573D8_57FD8[cur_file_id] & FILE_ADDR_MASK;
        file_size = (D_800573D8_57FD8[next_file_id] & FILE_ADDR_MASK) - file_rom_addr;
        vram_start = D_80054ACC_556CC[cur_file_id].vram_start;
        vram_end = D_80054ACC_556CC[cur_file_id].vram_end;

        buf_end = buf_start + ((s32)vram_end - (s32)vram_start);

        D_8015C5D4_15D1D4 = TRUE;
        
        buf_cur = buf_start;

        if (file_size != 0) {
            // @recomp Load the overlay in the recomp runtime.
            patch_api_load_overlays(file_rom_addr, (void *)buf_start, file_size);
            
            if (D_800573D8_57FD8[cur_file_id] & FILE_COMP_MASK) {
                buf_cur = func_80005394_5F94(file_rom_addr, buf_start, file_size);
            } else {
                file_size_aligned = (file_size + 1) & ~1;
                func_80001640_2240(file_rom_addr, (void *)buf_start, file_size_aligned);
                buf_cur = buf_start + file_size_aligned;
            }
        }

        D_8015C5D4_15D1D4 = was_loading_file;

        while (buf_cur < buf_end) {
            *buf_cur = 0;
            buf_cur++;
        }

        // osWritebackDCache_recomp(buf_start, buf_end - buf_start);
    } else {
        buf_end = NULL;
    }

    // Sometimes used to determine where to next load a file.
    return buf_end;
}

