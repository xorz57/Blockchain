#include "Blockchain.hpp"

blockchain_t::blockchain_t(std::uint32_t difficulty) : difficulty(difficulty) {
    const std::string hash_prev = "0000000000000000000000000000000000000000000000000000000000000000";
    const std::vector<std::uint8_t> bytes{'x', 'o', 'r', 'z', '5', '7', '\0'};
    blocks.emplace_back(hash_prev, bytes);
}

bool blockchain_t::is_valid() const {
    for (std::size_t i = 1; i < blocks.size(); ++i) {
        const block_t &block_curr = blocks[i];
        const block_t &block_prev = blocks[i - 1];

        if (block_curr.header.hash_curr != block_curr.hash()) {
            return false;
        }

        if (block_curr.header.hash_prev != block_prev.header.hash_curr) {
            return false;
        }
    }
    return true;
}
