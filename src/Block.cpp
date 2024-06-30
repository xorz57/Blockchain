#include "Block.hpp"
#include "Color.hpp"
#include "Cryptography.hpp"

#include <ctime>
#include <format>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

block_t::block_t(const std::string &hash_prev, std::vector<std::uint8_t> bytes) : bytes(std::move(bytes)) {
    header.timestamp = std::to_string(std::time(nullptr));
    header.hash_prev = hash_prev;
    header.hash_curr = hash();
}

std::string block_t::hash() const {
    std::ostringstream oss;
    oss << header.nonce;
    for (const auto &byte: bytes) {
        oss << static_cast<std::uint32_t>(byte);
    }
    oss << header.timestamp << header.hash_prev;
    std::string buffer = oss.str();
    return cryptography::sha256(buffer);
}

void block_t::mine(std::uint32_t difficulty) {
    bool found = false;
    std::mutex mutex;
    std::string str(difficulty, '0');

    auto t0 = std::chrono::steady_clock::now();

    auto mining_thread = [&](int thread_id) {
        while (!found) {
            std::unique_lock<std::mutex> lock(mutex);
            if (found) return;
            header.nonce++;
            header.hash_curr = hash();
            if (header.hash_curr.substr(0, difficulty) == str) {
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

    std::cout << color::bright::green;
    std::cout << std::format("mined block {} in {}h {}m {}s", header.hash_curr, hours, minutes, seconds);
    std::cout << color::reset << std::endl;
}

std::ostream &operator<<(std::ostream &os, const block_t &block) {
    os << color::bright::blue;
    os << "nonce: " << block.header.nonce << "\n";
    os << "timestamp: " << block.header.timestamp << "\n";
    os << "hash_prev: " << block.header.hash_prev << "\n";
    os << "hash_curr: " << block.header.hash_curr << "\n";
    os << "bytes: ";
    for (const auto &byte: block.bytes) {
        os << std::hex << std::setw(2) << std::setfill('0') << static_cast<std::uint32_t>(byte) << std::dec << " ";
    }
    if (block.bytes.empty()) os << "none";
    os << color::reset;
    return os;
}