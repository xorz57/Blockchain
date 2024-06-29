#include "Cryptography.hpp"

#include <openssl/sha.h>

#include <array>
#include <iomanip>
#include <sstream>

std::string cryptography::sha256(const std::string &input) {
    std::ostringstream oss;
    std::array<std::uint8_t, SHA256_DIGEST_LENGTH> bytes;
    SHA256(static_cast<const std::uint8_t *>(static_cast<const void *>(input.c_str())), input.size(), bytes.data());
    for (const std::uint8_t byte: bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0') << byte;
    }
    return oss.str();
}