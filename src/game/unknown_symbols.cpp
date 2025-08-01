#include "recomp.h"
#include "ultramodern/ultramodern.hpp"

extern "C" void __osPfsSelectBank_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void __osContRamRead_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void osPiWriteIo_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void osPiReadIo_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void __osContRamWrite_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void __osViSwapContext_recomp(uint8_t* rdram, recomp_context* ctx) {}
extern "C" void __osTimerInterrupt_recomp(uint8_t* rdram, recomp_context* ctx) {}
