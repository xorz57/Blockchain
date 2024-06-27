#include "Block.hpp"
#include "Color.hpp"

#include <openssl/sha.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
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
    std::cout << color::basic::yellow << "mining block #" << index << color::reset << std::endl;

    std::string str(difficulty, '0');
    bool found = false;
    std::mutex mutex;

    auto mining_thread = [&](int thread_id) {
        while (!found) {
            std::unique_lock<std::mutex> lock(mutex);
            if (found) return;
            nonce++;
            hash_curr = hash();
            if (hash_curr.substr(0, difficulty) == str) {
                found = true;
            }
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(mining_thread, i);
    }

    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << color::basic::green << "mined block #" << index << " " << hash_curr << color::reset << std::endl;
}