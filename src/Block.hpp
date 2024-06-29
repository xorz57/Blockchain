#pragma once

#include "Transaction.hpp"

#include <cstdint>
#include <string>
#include <vector>

struct block_t {
    block_t(std::uint32_t index, std::vector<std::uint8_t> bytes, std::string hash_prev);
    block_t(std::uint32_t index, std::vector<std::uint8_t> bytes, std::vector<transaction_t> transactions, std::string hash_prev);
    block_t(std::uint32_t index, std::vector<transaction_t> transactions, std::string hash_prev);

    std::string merkle_root_hash(const std::vector<transaction_t> &transactions) const;
    std::string hash() const;
    void mine(std::uint32_t difficulty);

    std::uint32_t index = 0;
    std::uint32_t nonce = 0;
    std::vector<std::uint8_t> bytes;
    std::vector<transaction_t> transactions;
    std::string timestamp;
    std::string hash_prev;
    std::string hash_curr;
};

std::ostream &operator<<(std::ostream &os, const block_t &block);
