#pragma once

#include "types.hpp"
#include "utils.hpp"

namespace BFVpp {
template <class P>
inline lweKey<P> lweKeygen()
{
    std::uniform_int_distribution<int> ternary(-1, 1);
    lweKey<P> sk;
    for (typename P::T &ski : sk) ski = ternary(generator);
    return sk;
}
}  // namespace BFVpp
