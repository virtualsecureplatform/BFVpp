#pragma once

#include "mulfft.hpp"
#include "types.hpp"

namespace BFVpp {
template <class P>
inline Polynomial<P> decrypt(const Ctxt<P> &c, const lweKey<P> &key)
{
    Polynomial<P> mulres, p;
    PolyMul<P>(mulres, c[0], key);
    Polynomial<P> phase = c[1];
    for (int i = 0; i < P::n; i++) phase[i] -= mulres[i];

    for (int i = 0; i < P::n; i++)
        p[i] = static_cast<typename P::T>(std::round(phase[i] / P::Δ)) %
               P::plain_modulus;
    return p;
}
}  // namespace BFVpp