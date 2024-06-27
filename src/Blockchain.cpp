#include "Blockchain.hpp"

blockchain_t::blockchain_t(int difficulty) : difficulty(difficulty) {
    blocks.emplace_back(0, "block#0", "000000000000000000000000000000000000000000000000000000000000000");
}

void blockchain_t::add_block(block_t &&block) {
    block.mine(difficulty);
    blocks.push_back(block);
}

bool blockchain_t::is_valid() const {
    for (size_t i = 1; i < blocks.size(); ++i) {
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
