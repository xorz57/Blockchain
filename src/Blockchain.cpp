#include "Blockchain.hpp"

blockchain_t::blockchain_t(std::uint32_t difficulty) : difficulty(difficulty) {
    const std::uint32_t index = 0;
    const std::vector<std::uint8_t> bytes{'x', 'o', 'r', 'z', '5', '7', '\0'};
    const std::string hash_prev = "0000000000000000000000000000000000000000000000000000000000000000";
    blocks.emplace_back(0, bytes, hash_prev);
}

bool blockchain_t::is_valid() const {
    for (std::size_t i = 1; i < blocks.size(); ++i) {
        const block_t &block_curr = blocks[i];
        const block_t &block_prev = blocks[i - 1];

        if (block_curr.hash_curr != block_curr.hash()) {
            return false;
        }

        if (block_curr.hash_prev != block_prev.hash_curr) {
            return false;
        }
    }
    return true;
}
