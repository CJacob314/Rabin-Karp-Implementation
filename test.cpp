#include <iostream>

#include "RabinKarp.h"

using CJacob::RabinKarp;

/*
    This is not an actual testing function. It's just my one single test case. If I were to ever use this for a file-compression algorithm,
    I'd first write an actual test suite for my Rabin-Karp code.
 */
int main(void) {
    auto res = RabinKarp::run("abcHelloaasdlfjaabdfjabcabalsdfjlkajfabclasdkfjalkjabc", "abc");

    std::visit([](const auto& val) {{
        using T = std::decay_t<decltype(val)>; // Stripped down type of `val`

        // Compile-time evaluation of branches is necessary to avoid compilation errors from type mismatches
        if constexpr (std::is_same_v<T, std::vector<size_t>>) {
            // val is a vector of size_t so call was successful.

            for (const auto& it : val) {
                std::cout << it << ' ';
            }
            std::cout << '\n';
        } else if constexpr (std::is_same_v<T, std::string>) {
            // val is a string, so the call was a failure.

            std::cerr << val << '\n'; // Print error message
        } else {
            std::cerr << "Something went wrong.\n";
        }
    } }, res);

    return 0;
}