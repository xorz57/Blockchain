#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct block_t {
    block_t(std::uint32_t index, std::vector<std::uint8_t> bytes, std::string hash_prev);

    std::string calculate_hash() const;

    void mine(std::uint32_t difficulty);

    std::uint32_t index = 0;
    std::uint32_t nonce = 0;
    std::vector<std::uint8_t> bytes;
    std::string timestamp;
    std::string hash_prev;
    std::string hash_curr;
};

std::ostream &operator<<(std::ostream &os, const block_t &block);
