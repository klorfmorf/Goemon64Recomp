#include "patches.h"
#include "common.h"

RECOMP_DECLARE_EVENT(recomp_on_init());

extern void func_800041E0_4DE0(void*, int);

RECOMP_PATCH void func_80004170_4D70(void) 
{
	// @recomp_event recomp_on_init(): Allow mods to initialize themselves once.
	recomp_on_init();

	func_800041E0_4DE0(&D_8008CCC0_8D8C0, sizeof(SYS_W));
	D_8015C5C8_15D1C8 = &D_8008CCC0_8D8C0;
	D_8015C5D4_15D1D4 = 0;
	D_8008CCC0_8D8C0.fill_color_alpha = 1;
	D_8008CCC0_8D8C0.frame_buffer_bits_per_pixel = G_IM_SIZ_16b;
}