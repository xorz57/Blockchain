#include "Block.hpp"
#include "Blockchain.hpp"
#include "Color.hpp"

#include <iostream>
#include <random>
#include <string>
#include <vector>

int main() {
    auto blockchain = blockchain_t(6);

    std::cout << blockchain.blocks.front() << std::endl;

    while (blockchain.is_valid()) {
        const std::uint32_t index = blockchain.blocks.back().index + 1;
        const std::vector<std::uint8_t> bytes;
        const std::string hash_prev = blockchain.blocks.back().hash_curr;
        block_t block(index, bytes, hash_prev);

        block.mine(blockchain.difficulty);

        std::cout << block << std::endl;

        blockchain.blocks.push_back(block);
    }

    return 0;
}
