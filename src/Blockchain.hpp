#pragma once

#include "Block.hpp"

#include <vector>

struct blockchain_t {
    explicit blockchain_t(int difficulty);

    void add_block(block_t &&block);

    bool is_valid() const;

    std::vector<block_t> blocks;
    int difficulty;
};