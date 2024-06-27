#pragma once

#include <string>

struct block_t
{
    block_t(int index, std::string data, std::string hash_prev);

    std::string hash() const;
    void mine(int difficulty);

    std::string timestamp;
    int nonce = 0;
    int index = 0;
    std::string data;
    std::string hash_prev;
    std::string hash_curr;
};