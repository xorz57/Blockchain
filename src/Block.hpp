#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

struct block_header_t {
    block_header_t() = default;

    std::uint32_t nonce = 0;
    std::string timestamp;
    std::string hash_prev;
    std::string hash_curr;
};

struct block_t {
    block_t() = default;
    block_t(const std::string &hash_prev, std::vector<std::uint8_t> bytes);

    std::string hash() const;
    void mine(std::uint32_t difficulty);

    nlohmann::json serialize() const;
    void unserialize(const nlohmann::json &data);

    block_header_t header;
    std::vector<std::uint8_t> bytes;
};
