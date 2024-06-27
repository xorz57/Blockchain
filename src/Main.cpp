#include "Block.hpp"
#include "Blockchain.hpp"
#include "Color.hpp"

#include <iostream>

int main() {
    blockchain_t blockchain(6);

    while (blockchain.is_valid()) {
        blockchain.push(block_t(blockchain.blocks.back().index + 1, "", blockchain.blocks.back().hash_curr));
    }

    return 0;
}