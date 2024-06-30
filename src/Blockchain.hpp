#pragma once

#include "Block.hpp"

#include <cstdint>
#include <vector>

struct blockchain_t {
    blockchain_t() = default;
    explicit blockchain_t(std::uint32_t difficulty);

    bool is_valid() const;

    std::uint32_t difficulty = 0;
    std::vector<block_t> blocks;
};