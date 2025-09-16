#pragma once
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <utility>

namespace solana {

// Maximum length of derived pubkey seed
constexpr std::size_t MAX_SEED_LENGTH = 32;

// Size of public key in bytes
constexpr std::size_t PUBLIC_KEY_LENGTH = 32;

class PublicKey {
public:
    // Constructors
    explicit PublicKey(uint64_t value);
    explicit PublicKey(const std::string& base58);
    explicit PublicKey(const std::vector<uint8_t>& bytes);
    explicit PublicKey(const std::array<uint8_t, PUBLIC_KEY_LENGTH>& bytes);

    // Create unique key (for tests/benchmarks)
    static PublicKey unique();

    // Default public key value
    static const PublicKey Default;

    // Equality check
    bool equals(const PublicKey& other) const;

    // Return base-58 representation
    std::string toBase58() const;

    // JSON-style representation
    std::string toJSON() const;

    // Raw bytes
    std::vector<uint8_t> toBytes() const;

    // Fixed-size buffer
    std::array<uint8_t, PUBLIC_KEY_LENGTH> toBuffer() const;

    // String representation
    std::string toString() const;

    // Derive public key from seed
    static PublicKey createWithSeed(
        const PublicKey& fromPublicKey,
        const std::string& seed,
        const PublicKey& programId
    );

    // Derive program address
    static PublicKey createProgramAddressSync(
        const std::vector<std::vector<uint8_t>>& seeds,
        const PublicKey& programId
    );

    // Async-like variant (kept for compatibility)
    static PublicKey createProgramAddress(
        const std::vector<std::vector<uint8_t>>& seeds,
        const PublicKey& programId
    );

    // Find valid program address
    static std::pair<PublicKey, uint8_t> findProgramAddressSync(
        const std::vector<std::vector<uint8_t>>& seeds,
        const PublicKey& programId
    );

    // Async-like variant (compatibility)
    static std::pair<PublicKey, uint8_t> findProgramAddress(
        const std::vector<std::vector<uint8_t>>& seeds,
        const PublicKey& programId
    );

    // Check if pubkey is on ed25519 curve
    static bool isOnCurve(const PublicKey& key);

private:
    // Fixed 32-byte key data
    std::array<uint8_t, PUBLIC_KEY_LENGTH> _bytes{};
};

} 
