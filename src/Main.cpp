#include "Block.hpp"
#include "Blockchain.hpp"
#include "Color.hpp"

int main() {
    auto blockchain = blockchain_t(4);

    while (blockchain.is_valid()) {
        auto index = blockchain.blocks.back().index + 1;
        auto bytes = std::vector<std::uint8_t>{'x', 'o', 'r', 'z', '5', '7', '\0'};
        auto hash_prev = blockchain.blocks.back().hash_curr;

        auto block = block_t(index, bytes, hash_prev);

        block.mine(blockchain.difficulty);
        blockchain.push(block);
    }

    return 0;
}