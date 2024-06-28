#include "Block.hpp"
#include "Blockchain.hpp"
#include "Color.hpp"

int main() {
    auto blockchain = blockchain_t(6);

    while (blockchain.is_valid()) {
        auto index = blockchain.blocks.back().index + 1;
        auto bytes = std::vector<std::uint8_t>{'x', 'o', 'r', 'z', '5', '7', '\0'};
        auto transactions = std::vector<transaction_t>{
                {"Alice", "Bob", 10.0f},
                {"Bob", "Alice", 20.0f},
        };
        auto hash_prev = blockchain.blocks.back().hash_curr;

        auto block = block_t(index, bytes, transactions, hash_prev);

        block.mine(blockchain.difficulty);
        blockchain.push(block);
    }

    return 0;
}