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
    static constexpr uint32_t Bgbit = 6;
    static constexpr std::uint32_t Bg = 1U << Bgbit;
    static constexpr uint32_t l = 3;
    using T = uint32_t;
    static constexpr double Δ =
        static_cast<double>(1ULL << std::numeric_limits<T>::digits) /
        plain_modulus;
};
}  // namespace BFVpp