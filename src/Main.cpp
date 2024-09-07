#include "Block.hpp"
#include "Blockchain.hpp"

#include <iostream>
#include <random>
#include <string>
#include <vector>

int main() {
    auto blockchain = blockchain_t(6);

    while (blockchain.is_valid()) {
        std::cout << blockchain.blocks.back().serialize().dump(4)
                  << std::endl;

        const std::vector<std::uint8_t> bytes;
        const std::string hash_prev = blockchain.blocks.back().header.hash_curr;
        block_t block(hash_prev, bytes);

        block.mine(blockchain.difficulty);

        blockchain.blocks.push_back(block);
    }

    return 0;
}
