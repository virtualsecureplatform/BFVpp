#pragma once

#include "types.hpp"
#include "utils.hpp"
#include "mulfft.hpp"

namespace BFVpp{
    template <class P>
    inline Ctxt<P> encryptzero(const double α,const lweKey<P> &key){
        std::uniform_int_distribution<typename P::T> Torusdist(
        0, std::numeric_limits<typename P::T>::max());
        Ctxt<P> c;
        for (typename P::T &i : c[0]) i = Torusdist(generator);
        PolyMul<P>(c[1], c[0], key);
        for (typename P::T &i : c[1]) i += ModularGaussian<P>(0, α);
        return c;
    }
    template<class P>
    inline Ctxt<P> encrypt(const Polynomial<P> &m, const double α, const lweKey<P> &key){
        Ctxt<P> c = encryptzero<P>(α,key);
        for(int i = 0;i<P::n;i++) c[1][i] += static_cast<typename P::T>(P::Δ*m[i]);
        return c;
    }
}