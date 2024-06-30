#pragma once

#include "Block.hpp"

#include <cstdint>
#include <vector>

struct blockchain_t {
    explicit blockchain_t(std::uint32_t difficulty);

    bool is_valid() const;

    std::uint32_t difficulty;
    std::vector<block_t> blocks;
};