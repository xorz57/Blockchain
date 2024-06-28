#pragma once

#include <ostream>
#include <string>

struct transaction_t {
    transaction_t(std::string sender, std::string receiver, float amount) : sender(sender), receiver(receiver), amount(amount) {}

    friend std::ostream &operator<<(std::ostream &os, const transaction_t &transaction);

    std::string sender;
    std::string receiver;
    float amount = 0.0f;
};