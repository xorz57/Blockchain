#include "Block.hpp"
#include "Blockchain.hpp"
#include "Color.hpp"

#include <iostream>

int main() {
    blockchain_t blockchain(5);

    blockchain.push(block_t(blockchain.blocks.back().index + 1, "block #1", blockchain.blocks.back().hash_curr));
    blockchain.push(block_t(blockchain.blocks.back().index + 1, "block #2", blockchain.blocks.back().hash_curr));
    blockchain.push(block_t(blockchain.blocks.back().index + 1, "block #3", blockchain.blocks.back().hash_curr));

    if (blockchain.is_valid()) {
        std::cout << color::basic::green << "Blockchain is valid!" << color::reset << std::endl;
    } else {
        std::cout << color::basic::red << "Blockchain is invalid!" << color::reset << std::endl;
    }

    return 0;
}