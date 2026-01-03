#include "recomp.h"
#include "librecomp/overlays.hpp"
#include "librecomp/helpers.hpp"
#include "ultramodern/ultramodern.hpp"

extern "C" void osMapTLB_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void osUnmapTLB_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void osUnmapTLBAll_recomp(uint8_t* rdram, recomp_context* ctx) {}