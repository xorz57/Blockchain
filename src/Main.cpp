#include "Block.hpp"
#include "Blockchain.hpp"

#include <iostream>

int main() {
    blockchain_t blockchain(4);

    blockchain.add("Block 1 Data");
    blockchain.add("Block 2 Data");
    blockchain.add("Block 3 Data");

    std::cout << "Blockchain is valid: " << blockchain.is_valid() << std::endl;

    return 0;
}