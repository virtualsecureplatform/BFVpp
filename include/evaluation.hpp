#pragma once

#include "types.hpp"
#include "mulfft.hpp"

namespace BFVpp {
template <class P>
void Add(Ctxt<P> &res, const Ctxt<P> &a, const Ctxt<P> &b)
{
    for (int i = 0; i < 2 * P::n; i++) res[0][i] = a[0][i] + b[0][i];
}
template <class P>
void MultiplicationWithoutRelinerization(CtxtMult<P> &res, const Ctxt<P> &a, const Ctxt<P> &b){
    PolynomialInFD<P> ffta,fftb,fftc;
    TwistIFFT<P>(ffta, a[0]);
    TwistIFFT<P>(fftb, b[1]);
    MulInFD<P::n>(fftc, ffta, fftb);
    TwistIFFT<P>(ffta, a[1]);
    TwistIFFT<P>(fftb, b[0]);
    FMAInFD<P::n>(fftc,ffta,fftb);
    TwistFFTrescale<P>(res[0],fftc);

    PolyMulRescale<P>(res[1],a[1],b[1]);

    PolyMulRescale<P>(res[2],a[0],b[0]);
}
}  // namespace BFVpp