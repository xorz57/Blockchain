#include "Transaction.hpp"

#include <iomanip>
#include <sstream>

std::ostream &operator<<(std::ostream &os, const transaction_t &transaction) {
    os << std::fixed << std::setprecision(5);
    os << transaction.sender << "->" << transaction.receiver << ":" << transaction.amount;
    return os;
}