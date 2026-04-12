#include "patches.h"
#include "ui_funcs.h"

// @recomp Patched to enable RT64's extended GBI mode and set the correct refresh rate.
RECOMP_PATCH void func_800012FC_1EFC() 
{
    u8 retraces_per_game_step = D_8008CCC0_8D8C0.retraces_per_game_step;

#if 0
    if ((D_8008CCC0_8D8C0.controller[0].button_held_down & L_TRIG) && (D_8008CCC0_8D8C0.controller[0].button_held_down & Z_TRIG) && (D_8008CCC0_8D8C0.controller[0].button_held_down & R_JPAD)) {
        D_8008CCC0_8D8C0.stepw = 10;
    }
#endif

    // @recomp Run Ui Callbacks
    recomp_run_ui_callbacks();

    gEXEnable(D_8015C5CC_15D1CC++);
    // gEXSetRDRAMExtended(D_8015C5CC_15D1CC++, 1);

    if (retraces_per_game_step != 0) {
        gEXSetRefreshRate(D_8015C5CC_15D1CC++, 60 / retraces_per_game_step);
    }

    // Rely on automatic tagging for display lists which are not covered by the draw list system (only Konami Logo so far?).
    // gEXMatrixGroupDecomposedNormal(D_8015C5CC_15D1CC++, G_EX_PUSH, 0, G_EX_EDIT_ALLOW);

    gSPDisplayList(D_8015C5CC_15D1CC++, &D_8006D4E0_6E0E0);
}
