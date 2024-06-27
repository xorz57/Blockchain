#include "Block.hpp"
#include "Blockchain.hpp"

#include <iostream>

int main() {
    blockchain_t blockchain(4);

    blockchain.push(block_t(blockchain.blocks.back().index + 1, "block#1", blockchain.blocks.back().hash_curr));
    blockchain.push(block_t(blockchain.blocks.back().index + 1, "block#2", blockchain.blocks.back().hash_curr));
    blockchain.push(block_t(blockchain.blocks.back().index + 1, "block#3", blockchain.blocks.back().hash_curr));

    if (blockchain.is_valid()) {
        std::cout << "Blockchain is valid!" << std::endl;
    } else {
        std::cout << "Blockchain is invalid!" << std::endl;
    }

    return 0;
}