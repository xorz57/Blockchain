#include "Block.hpp"
#include "Blockchain.hpp"

#include <iostream>

int main() {
    blockchain_t blockchain(4);

    blockchain.add_block(block_t(1, "block#1", blockchain.blocks.back().hash_curr));
    blockchain.add_block(block_t(2, "block#2", blockchain.blocks.back().hash_curr));
    blockchain.add_block(block_t(3, "block#3", blockchain.blocks.back().hash_curr));

    std::cout << "Blockchain is valid: " << blockchain.is_valid() << std::endl;

    return 0;
}