#pragma once

#include "Block.hpp"

#include <vector>

class blockchain_t {
public:
    explicit blockchain_t(int difficulty);

    void add(const std::string &data);
    bool is_valid() const;

private:
    std::vector<block_t> m_blocks;
    int m_difficulty;
};