#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct block_header_t {
    std::uint32_t index = 0;
    std::uint32_t nonce = 0;
    std::string timestamp;
    std::string hash_prev;
    std::string hash_curr;
};

struct block_t {
    block_t(std::uint32_t index, std::vector<std::uint8_t> bytes, const std::string &hash_prev);

    std::string hash() const;

    void mine(std::uint32_t difficulty);

    block_header_t header;
    std::vector<std::uint8_t> bytes;
};

std::ostream &operator<<(std::ostream &os, const block_t &block);
