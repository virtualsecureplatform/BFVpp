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
    UnsignedCtxt<P> aa,bb;
    RemoveSign<P>(aa[0],a[0]);
    RemoveSign<P>(aa[1],a[1]);
    RemoveSign<P>(bb[0],b[0]);
    RemoveSign<P>(bb[1],b[1]);

    PolynomialInFD<P> ffta,fftb,fftc;
    TwistIFFT<P>(ffta, aa[0]);
    TwistIFFT<P>(fftb, bb[1]);
    MulInFD<P::n>(fftc, ffta, fftb);
    TwistIFFT<P>(ffta, aa[1]);
    TwistIFFT<P>(fftb, bb[0]);
    FMAInFD<P::n>(fftc,ffta,fftb);
    TwistFFTrescale<P>(res[0],fftc);

    PolyMulRescaleUnsigned<P>(res[1],aa[1],bb[1]);

    PolyMulRescaleUnsigned<P>(res[2],aa[0],bb[0]);
}
}  // namespace BFVpp