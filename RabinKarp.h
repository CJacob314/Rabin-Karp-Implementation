#ifndef __RABIN_KARP_H
#define __RABIN_KARP_H

#include <cstdint>
#include <functional>
#include <string>
#include <variant>

namespace CJacob {

/**
 * @brief Rabin-Karp string search algorithm implementation.
 * @details An implementation of the Rabin-Karp string searching algorithm which supports strings of lengths up to 2^64 - 1.
 */
class RabinKarp {
    private:
    // Private efficient hash function based on https://en.wikipedia.org/wiki/Rabin_fingerprint
    static inline size_t computeRabinFingerprint(
        const std::string&, size_t, size_t, size_t, size_t, size_t = 0, char = 0);

    public:
    /**
     * @param s Haystack string
     * @param p Pattern string
     * @return A `variant` of either a vector of indices where `p` was found in `s` or a string describing the error.
     */
    static std::variant<std::vector<size_t>, std::string> run(const std::string&, const std::string&);

}; // class RabinKarp

} // namespace CJacob

#endif