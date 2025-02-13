#ifndef PATCHES_H
#define PATCHES_H

#include <ultra64.h>
#include "rt64_extended_gbi.h"

#define RECOMP_EXPORT      __attribute__((section(".recomp_export")))
#define RECOMP_PATCH       __attribute__((section(".recomp_patch")))
#define RECOMP_FORCE_PATCH __attribute__((section(".recomp_force_patch")))

#include "patch_helpers.h"
#include "patch_api_funcs.h"

#include "types.h"
#include "macros.h"

#include "game_funcs.h"
#include "game_vars.h"

#endif // PATCHES_H
