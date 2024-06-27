#include "Blockchain.hpp"

blockchain_t::blockchain_t(std::uint32_t difficulty) : difficulty(difficulty) {
    blocks.emplace_back(0, std::vector<std::uint8_t>(), "000000000000000000000000000000000000000000000000000000000000000");
}

void blockchain_t::push(block_t &&block) {
    block.mine(difficulty);
    blocks.push_back(block);
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
