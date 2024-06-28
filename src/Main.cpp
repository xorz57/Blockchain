#include "Block.hpp"
#include "Blockchain.hpp"
#include "Color.hpp"

#include <iostream>

int main() {
    auto blockchain = blockchain_t(5);

    std::cout << blockchain.blocks.front() << std::endl;

    while (blockchain.is_valid()) {
        const std::uint32_t index = blockchain.blocks.back().index + 1;
        const std::vector<transaction_t> transactions{
                {"Alice", "Bob", 50.0f},
                {"Bob", "Carol", 25.0f},
        };
        const std::string hash_prev = blockchain.blocks.back().hash_curr;
        block_t block(index, transactions, hash_prev);
        block.mine(blockchain.difficulty);
        std::cout << block << std::endl;
        blockchain.blocks.push_back(block);
    }

    return 0;
}