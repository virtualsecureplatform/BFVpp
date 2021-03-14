#pragma once

#include "types.hpp"

namespace BFVpp{
    template <class P>
    void Add(Ctxt<P> &res, const Ctxt<P> &a, const Ctxt<P> &b){
        for(int i = 0;i<2*P::n;i++) res[i] = a[i] + b[i];
    }
    template <class P>
}