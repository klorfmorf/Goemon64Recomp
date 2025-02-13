#include "patches.h"

// @recomp Patched to enable RT64's extended GBI mode and set the current framerate.
RECOMP_PATCH void func_800012FC_1EFC() {
    // TODO: Reverse engineer the actual struct.
    u8 retraces_per_game_step = D_8008CCC0_8D8C0.unknown[0x3ADCA];

    if (*((u16 *)&D_8008CCC0_8D8C0.unknown[0x3B07A]) & 0x10 && *((u16 *)&D_8008CCC0_8D8C0.unknown[0x3B07A]) & 0x200)
    {
        D_8008CCC0_8D8C0.unknown[0x3ADD4] = 10;
    }

    gEXEnable(D_8015C5CC_15D1CC++);

    if (retraces_per_game_step != 0) {
        gEXSetRefreshRate(D_8015C5CC_15D1CC++, 60 / retraces_per_game_step);
    }

    gSPDisplayList(D_8015C5CC_15D1CC++, &D_8006D4E0_6E0E0);
}
