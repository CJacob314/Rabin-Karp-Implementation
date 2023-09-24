#include "RabinKarp.h"

// Efficient Rabin fingerprint hash implementation: read https://en.wikipedia.org/wiki/Rabin_fingerprint
size_t CJacob::RabinKarp::computeRabinFingerprint(
    const std::string& str, size_t start, size_t end, size_t power, size_t mod, size_t prevHash, char prevChar) {

    size_t hash = prevHash;
    if (!start) {
        // start == 0, so compute the initial hash.
        for (size_t i = start; i < end; ++i) {
            hash = (hash * 257 + str[i]) % mod; // 257 is a prime number
        }
    } else {
        // start != 0, so compute the next rolling hash.
        hash = ((hash + mod - ((static_cast<size_t>(prevChar) * power) % mod)) * 257 + str[end - 1]) % mod;
    }

    return hash;
}

std::variant<std::vector<size_t>, std::string> CJacob::RabinKarp::run(const std::string& s, const std::string& p) {
    // Lengths of haystack and pattern strings
    const size_t n = s.length();
    const size_t m = p.length();

    if (m > n) return "Pattern passed longer than the haystack"; // Pattern longer than haystack is impossible to find, obviously.
    std::vector<size_t> indices;

    static constexpr size_t mod = 0x3C069143; // Large but not too large prime number to avoid collisions AND integer overflows.

    // Modular exponentiation to calculate 257^(m - 1) % mod. Thank you CJacob314/RSA-Implementation for making this easy!
    size_t power = 1;
    for (uint64_t i = 0; i < m - 1; ++i) {
        power = (power * 257) % mod;
    }

    // Compute pattern and haystack hashes
    size_t p_hash = computeRabinFingerprint(p, 0, m, power, mod);
    size_t s_hash = computeRabinFingerprint(s, 0, m, power, mod);

    // Loop through haystack until the last possible substring starting index.
    for (size_t i = 0; i <= n - m; ++i) {
        if (p_hash == s_hash) {
            // Found a hash equivalence. Verify that it isn't a collision.
            bool match = true;
            for (size_t j = 0; j < m; ++j) {
                if (s[i + j] != p[j]) {
                    match = false; // Equivalence was a collision!
                    break;
                }
            }

            if (match) {
                indices.push_back(i); // Was an actual match, add to return vector.
            }
        }

        if (i < n - m)
            s_hash = computeRabinFingerprint(s, i + 1, i + m + 1, power, mod, s_hash, s[i]); // Compute hash for next window
    }

    return indices;
}