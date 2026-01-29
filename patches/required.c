#include "patches.h"
#include "misc_funcs.h"

extern void overlay_apply_relocations(u32 file_id, u8 *load_addr);
extern void *func_80014840_15440(void *, u32 file_id);
void *func_80013B14_14714(unsigned short file_id);
extern Task *D_8006D328_6DF28;
void* func_080026B8_71FE88(void *arg);

// @recomp Patched to load the overlay in the recomp runtime and to relocate TLB mapped overlays.
RECOMP_PATCH u8 *func_80001C00_2800(u32 file_id, u8 *buf_start) 
{
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
            recomp_load_overlays(file_rom_addr, (void *)buf_start, file_size);
            
            if (D_800573D8_57FD8[cur_file_id] & FILE_COMP_MASK) {
                buf_cur = func_80005394_5F94(file_rom_addr, buf_start, file_size);
            } else {
                file_size_aligned = (file_size + 1) & ~1;
                func_80001640_2240(file_rom_addr, (void *)buf_start, file_size_aligned);
                buf_cur = buf_start + file_size_aligned;
            }

            // @recomp Apply relocations after loading the overlay.
            overlay_apply_relocations(file_id, buf_start);
        }

        D_8015C5D4_15D1D4 = was_loading_file;

        while (buf_cur < buf_end) {
            *buf_cur = 0;
            buf_cur++;
        }

        // @recomp Not needed in the static recompilation.
        // osWritebackDCache_recomp(buf_start, buf_end - buf_start);
    } else {
        buf_end = NULL;
    }

    // Sometimes used to determine where to next load a file.
    return buf_end;
}

// @recomp Patched to relocate TLB mapped addresses to their proper KSEG0 addresses so that the recomp runtime can find them.
RECOMP_PATCH void func_8001481C_1541C(Task *task) 
{
    const u32 tlb_overlay_start = 0x08000000lu;
    const u32 code_overlay_mask = ~0x40000000;

    func_80001EB0_2AB0(task->overlay_file_id, (u32)task->overlay_vram_addr);

    // @recomp Relocate all functions pointers.
    if (task->function_1 != NULL) {
        // If task->overlay_file_id is non-zero and loaded into memory, this function will resolve task->function_1 into a KSEG0 pointer.
        void *resolved_function = func_80014840_15440((void *)task->function_1, task->overlay_file_id);

        // If task->overlay_file_id is non-zero and loaded into memory, this function will return the base address of the overlay as a KSEG0 pointer.
        // Note that the returned pointer to the start of the overlay will be ORed with 0x40000000 if it is an overlay containing code.
        u32 overlay_start = (u32)func_800141C4_14DC4(task->overlay_file_id) & code_overlay_mask;

        if (resolved_function != NULL && resolved_function != task->function_1) {
            task->function_1 = (TaskCallback) ((u32)task->function_1 - tlb_overlay_start + overlay_start);
        }
    }

    if (task->function_2 != NULL) {
        void *resolved_function = func_80014840_15440((void *)task->function_2, task->overlay_file_id);
        u32 overlay_start = (u32)func_800141C4_14DC4(task->overlay_file_id) & code_overlay_mask;

        if (resolved_function != NULL && resolved_function != task->function_2) {
            task->function_2 = (TaskCallback) ((u32)task->function_2 - tlb_overlay_start + overlay_start);
        }
    }

    if (task->function_3 != NULL) {
        void *resolved_function = func_80014840_15440((void *)task->function_3, task->overlay_file_id);
        u32 overlay_start = (u32)func_800141C4_14DC4(task->overlay_file_id) & code_overlay_mask;

        if (resolved_function != NULL && resolved_function != task->function_3) {
            task->function_3 = (TaskCallback) ((u32)task->function_3 - tlb_overlay_start + overlay_start);
        }
    }
}

// @recomp Patch the only other place where a TLB mapped overlay function is called from the main segment.
RECOMP_PATCH void func_8001198C_1258C(void) 
{
    func_80013B14_14714(0x3C);
    func_80001EB0_2AB0(0x3C, (u32)func_800141C4_14DC4(0x3C));
    func_080026B8_71FE88(D_8006D328_6DF28);
}