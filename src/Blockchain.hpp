#pragma once

#include "Block.hpp"

#include <cstdint>
#include <vector>

struct blockchain_t {
    explicit blockchain_t(std::uint32_t difficulty);

    void push(block_t &&block);

    bool is_valid() const;

    std::vector<block_t> blocks;
    std::uint32_t difficulty;
};