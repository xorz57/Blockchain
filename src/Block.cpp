#include "Block.hpp"
#include "Color.hpp"
#include "Cryptography.hpp"

#include <ctime>
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
        oss << byte;
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

    const std::uint32_t hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
    const std::uint32_t minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count() % 60;
    const std::uint32_t seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60;

    std::cout << color::bright::green
              << "mined block " << header.hash_curr << " in "
              << std::setfill('0') << std::setw(2) << hours << "h "
              << std::setw(2) << minutes << "m "
              << std::setw(2) << seconds << "s"
              << color::reset << std::endl;
}

nlohmann::json block_t::serialize() const {
    nlohmann::json serialized_block;

    serialized_block["nonce"] = header.nonce;
    serialized_block["timestamp"] = header.timestamp;
    serialized_block["hash_prev"] = header.hash_prev;
    serialized_block["hash_curr"] = header.hash_curr;

    nlohmann::json serialized_bytes;
    for (const auto &byte: bytes) {
        std::ostringstream oss;
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<std::uint32_t>(byte);
        std::string value = oss.str();
        serialized_bytes.push_back(value);
    }
    serialized_block["bytes"] = serialized_bytes;

    return serialized_block;
}

void block_t::unserialize(const nlohmann::json &data) {
    header.nonce = data["nonce"].get<std::uint32_t>();
    header.timestamp = data["timestamp"].get<std::string>();
    header.hash_prev = data["hash_prev"].get<std::string>();
    header.hash_curr = data["hash_curr"].get<std::string>();

    nlohmann::json serialized_bytes = data["bytes"];
    bytes.clear();
    for (const auto &byte: serialized_bytes) {
        std::istringstream iss(byte.get<std::string>());
        std::uint32_t value;
        iss >> std::hex >> value;
        bytes.push_back(static_cast<std::uint8_t>(value));
    }
}