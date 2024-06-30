#include "Block.hpp"
#include "Blockchain.hpp"
#include "Color.hpp"

#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<transaction_t> generate_random_transactions() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> amount_dist(1.0f, 100.0f);
    static std::uniform_int_distribution<int> transaction_count_dist(1, 5);

    static const std::vector<std::string> names = {"Alice", "Bob", "Carol", "Dave", "Eve"};
    static std::uniform_int_distribution<size_t> name_dist(0, names.size() - 1);

    std::vector<transaction_t> transactions;
    const std::size_t transaction_count = transaction_count_dist(gen);
    for (std::size_t i = 0; i < transaction_count; ++i) {
        std::string sender = names[name_dist(gen)];
        std::string receiver = names[name_dist(gen)];
        while (receiver == sender) {
            receiver = names[name_dist(gen)];
        }
        float amount = amount_dist(gen);
        transactions.push_back({sender, receiver, amount});
    }

    return transactions;
}

int main() {
    auto blockchain = blockchain_t(6);

    std::cout << blockchain.blocks.front() << std::endl;

    while (blockchain.is_valid()) {
        const std::uint32_t index = blockchain.blocks.back().index + 1;
        const std::vector<std::uint8_t> bytes;
        const std::vector<transaction_t> transactions = generate_random_transactions();
        const std::string hash_prev = blockchain.blocks.back().hash_curr;
        block_t block(index, bytes, transactions, hash_prev);
        block.mine(blockchain.difficulty);
        std::cout << block << std::endl;
        blockchain.blocks.push_back(block);
    }

    return 0;
}
