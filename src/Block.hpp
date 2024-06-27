#pragma once

#include <cstdint>
#include <string>

struct block_t {
    block_t(std::uint32_t index, std::string data, std::string hash_prev);

    std::string hash() const;
    void mine(std::uint32_t difficulty);

    std::string timestamp;
    std::uint32_t nonce = 0;
    std::uint32_t index = 0;
    std::string data;
    std::string hash_prev;
    std::string hash_curr;
};