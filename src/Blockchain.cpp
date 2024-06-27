#include "Blockchain.hpp"

blockchain_t::blockchain_t(int difficulty) : m_difficulty(difficulty) {
    m_blocks.emplace_back(0, "Genesis Block", "000000000000000000000000000000000000000000000000000000000000000");
}

void blockchain_t::add(const std::string &data) {
    auto block = block_t(m_blocks.size(), data, m_blocks.back().hash_curr);
    block.mine(m_difficulty);
    m_blocks.push_back(block);
}

bool blockchain_t::is_valid() const {
    for (size_t i = 1; i < m_blocks.size(); ++i) {
        const block_t &block_curr = m_blocks[i];
        const block_t &block_prev = m_blocks[i - 1];

        if (block_curr.hash_curr != block_curr.hash()) {
            return false;
        }

        if (block_curr.hash_prev != block_prev.hash_curr) {
            return false;
        }
    }
    return true;
}
