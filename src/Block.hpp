#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct block_header_t {
    std::uint32_t nonce = 0;
    std::string timestamp;
    std::string hash_prev;
    std::string hash_curr;
};

struct block_t {
    block_t(const std::string &hash_prev, std::vector<std::uint8_t> bytes);

    std::string hash() const;

    void mine(std::uint32_t difficulty);

    block_header_t header;
    std::vector<std::uint8_t> bytes;
};

std::ostream &operator<<(std::ostream &os, const block_t &block);
