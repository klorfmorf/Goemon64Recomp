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
        vram_start = D_80054ACC_556CC[cur_file_id].start;
        vram_end = D_80054ACC_556CC[cur_file_id].end;

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

// @recomp Patched to always map the overlay, regardless of if it was mapped already or not.
RECOMP_PATCH u32 func_80001EB0_2AB0(u32 file_id, u32 addr) {
    u32 page_index;
    u32 kuseg_addr;
    u32 page_count;

    page_index = 0;

    if (func_80001DF4_29F4(file_id) != 0) {
        if (file_id != 0) {
            kuseg_addr = D_80054ACC_556CC[file_id - 1].start;
            page_count = (D_80054ACC_556CC[file_id - 1].end - D_80054ACC_556CC[file_id - 1].start) >> 13;
        } else {
            kuseg_addr = 0x07000000;
            page_count = 31;
        }

        addr &= 0x3FFFFFFF;
        
        while (page_index <= page_count) {
            osMapTLB_recomp(page_index, OS_PM_4K, (void *)kuseg_addr, addr, addr + 0x1000, -1);
            page_index++;
            kuseg_addr += 0x2000;
            addr += 0x2000;
        } 
    }

    return 0;
}