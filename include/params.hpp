#pragma once

#include <cmath>
#include <cstdint>
#include <limits>

namespace BFVpp {
struct Parameter {
    static constexpr uint32_t nbit = 10;
    static constexpr uint32_t n = 1U << nbit;
    static constexpr uint32_t plain_modulus = 2;
    static const inline double α = std::pow(2.0, -25);  // fresh noise
    using T = uint32_t;
    static constexpr double Δ =
        static_cast<double>(std::numeric_limits<T>::max()) / plain_modulus;
};
}  // namespace BFVpp