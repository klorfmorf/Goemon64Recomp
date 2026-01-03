/**
 * @file overlay_reloc.c
 * @brief Runtime MIPS relocation for dynamically loaded overlays.
 *
 * When an overlay is loaded at a different RAM address than it was linked at,
 * all absolute addresses embedded in the code must be adjusted. This module
 * applies those adjustments using relocation data extracted from the ELF.
 */

#include "overlay_relocs.h"

/**
 * @brief Apply relocations to a loaded overlay.
 *
 * Adjusts all absolute addresses within the overlay to account for the
 * difference between the link-time address (VMA) and the runtime load address.
 *
 * @param file_id   Index into the game's file table (0 to FILE_TABLE_SIZE-1)
 * @param load_addr Pointer to where the overlay was loaded in RAM
 *
 * @note This function is safe to call for files with no relocations (no-op).
 */
void overlay_apply_relocations(u32 file_id, u8 *load_addr) {
    const OverlayRelocInfo *info;
    const OverlayReloc *relocs;
    s32 delta;
    u16 reloc_count;
    u16 i;

    /* -------------------------------------------------------------------- */
    /* Validate inputs and retrieve relocation info                         */
    /* -------------------------------------------------------------------- */

    if (file_id >= OVERLAY_FILE_TABLE_SIZE) {
        return;
    }

    info = &g_overlay_relocs[file_id];
    relocs = info->relocs;
    reloc_count = info->count;

    /* No relocations for this file - early exit */
    if (relocs == NULL || reloc_count == 0) {
        return;
    }

    /* -------------------------------------------------------------------- */
    /* Calculate relocation delta                                           */
    /* -------------------------------------------------------------------- */

    /*
     * Delta = (where we loaded it) - (where it was linked)
     *
     * All absolute addresses in the overlay need this value added to them.
     * If delta is 0, the overlay was loaded at its intended address and
     * no relocation is needed.
     */
    delta = (s32)((u32)load_addr - info->original_vaddr);

    if (delta == 0) {
        return;
    }

    /* -------------------------------------------------------------------- */
    /* Process relocations                                                  */
    /* -------------------------------------------------------------------- */

    for (i = 0; i < reloc_count; i++) {
        u32 offset = relocs[i].offset;
        u8 type = relocs[i].type;

        /* Pointer to the instruction/data to relocate */
        u32 *target_addr = (u32 *)(load_addr + offset);
        u32 value = *target_addr;

        switch (type) {

        /* ---------------------------------------------------------------- */
        case RELOC_R_MIPS_32:
        /* ---------------------------------------------------------------- */
            /*
             * Direct 32-bit absolute address.
             * Simply add the delta to adjust for new location.
             */
            *target_addr = value + (u32)delta;
            break;

        /* ---------------------------------------------------------------- */
        default:
        /* ---------------------------------------------------------------- */
            /* Unknown relocation type - ignore */
            break;
        }
    }
}