#include "Transaction.hpp"

#include <sstream>

std::ostream &operator<<(std::ostream &os, const transaction_t &transaction) {
    os << transaction.sender << "->" << transaction.receiver << ":" << transaction.amount;
    return os;
}