#include "Block.hpp"
#include "Color.hpp"
#include "Cryptography.hpp"

#include <ctime>
#include <format>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

block_t::block_t(std::uint32_t index, std::vector<std::uint8_t> bytes, std::string hash_prev)
    : index(index),
      bytes(std::move(bytes)),
      hash_prev(std::move(hash_prev)) {
    timestamp = std::to_string(std::time(nullptr));
    hash_curr = hash();
}

block_t::block_t(std::uint32_t index, std::vector<transaction_t> transactions, std::string hash_prev)
    : index(index),
      transactions(std::move(transactions)),
      hash_prev(std::move(hash_prev)) {
    timestamp = std::to_string(std::time(nullptr));
    hash_curr = hash();
}

std::string block_t::hash() const {
    std::ostringstream oss;
    oss << timestamp << nonce << index << hash_prev;
    for (const auto &byte: bytes) {
        oss << byte;
    }
    for (const auto &transaction: transactions) {
        oss << transaction;
    }
    std::string buffer = oss.str();
    return cryptography::sha256(buffer);
}

void block_t::mine(std::uint32_t difficulty) {
    std::cout << color::basic::yellow << "mining block #" << index << color::reset << std::endl;

    bool found = false;
    std::mutex mutex;
    std::string str(difficulty, '0');

    auto t0 = std::chrono::steady_clock::now();

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
    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back(mining_thread, i);
    }

    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    auto t1 = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = t1 - t0;

    int hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
    int minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count() % 60;
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60;

    std::cout << color::basic::green;
    std::cout << std::format("mined block #{} {} in {} hours {} minutes {} seconds", index, hash_curr, hours, minutes, seconds);
    std::cout << color::reset << std::endl;
}
