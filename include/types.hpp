#pragma once

#include <array>

#include "params.hpp"

namespace BFVpp {
template <class P>
using lweKey = std::array<typename P::T, P::n>;  // ternary secret key
template <class P>
using Polynomial = std::array<typename P::T, P::n>;
template <class P>
using UnsignedPolynomial = Polynomial<P>;
template <class P>
using PolynomialInFD = std::array<double, P::n>;
template <class P>
using Ctxt = std::array<Polynomial<P>, 2>;
template <class P>
using UnsignedCtxt = std::array<UnsignedPolynomial<P>, 2>;
template <class P>
using CtxtMult = std::array<Polynomial<P>, 3>;
}  // namespace BFVpp