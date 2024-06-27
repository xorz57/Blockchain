#include "Block.hpp"
#include "Color.hpp"

#include <openssl/sha.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

block_t::block_t(int index, std::string data, std::string hash_prev) : index(index),
                                                                       data(data),
                                                                       hash_prev(hash_prev) {
    timestamp = std::to_string(std::time(nullptr));
    hash_curr = hash();
}

std::string block_t::hash() const {
    std::ostringstream oss;

    oss << timestamp << nonce << index << data << hash_prev;
    std::string buffer = oss.str();

    oss.str("");

    std::vector<unsigned char> hash_bytes(SHA256_DIGEST_LENGTH);
    SHA256(static_cast<const unsigned char *>(static_cast<const void *>(buffer.c_str())), buffer.size(), hash_bytes.data());
    for (const auto &byte: hash_bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}

void block_t::mine(int difficulty) {
    std::cout << color::basic::yellow << "Mining block #" << index << color::reset << std::endl;

    std::string str(difficulty, '0');
    do {
        nonce++;
        hash_curr = hash();
    } while (hash_curr.substr(0, difficulty) != str);

    std::cout << color::basic::green << "Mined  block #" << index << " " << hash_curr << color::reset << std::endl;
}