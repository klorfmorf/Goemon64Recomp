#ifndef __GOEMON_GAME_H__
#define __GOEMON_GAME_H__

#include <cstdint>
#include <span>
#include <vector>

namespace goemon64 {
    void quicksave_save();
    void quicksave_load();
    std::vector<uint8_t> decompress_mnsg(std::span<const uint8_t> compressed_rom);
};

#endif
