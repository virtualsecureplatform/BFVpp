#pragma once

#include "mulfft.hpp"
#include "types.hpp"

namespace BFVpp {
template <class P>
void Add(Ctxt<P> &res, const Ctxt<P> &a, const Ctxt<P> &b)
{
    for (int i = 0; i < 2 * P::n; i++) res[0][i] = a[0][i] + b[0][i];
}
template <class P>
void MultiplicationWithoutRelinerization(CtxtMult<P> &res, const Ctxt<P> &a,
                                         const Ctxt<P> &b)
{
    UnsignedCtxt<P> aa, bb;
    RemoveSign<P>(aa[0], a[0]);
    RemoveSign<P>(aa[1], a[1]);
    RemoveSign<P>(bb[0], b[0]);
    RemoveSign<P>(bb[1], b[1]);

    PolynomialInFD<P> ffta, fftb, fftc;
    TwistIFFT<P>(ffta, aa[0]);
    TwistIFFT<P>(fftb, bb[1]);
    MulInFD<P::n>(fftc, ffta, fftb);
    TwistIFFT<P>(ffta, aa[1]);
    TwistIFFT<P>(fftb, bb[0]);
    FMAInFD<P::n>(fftc, ffta, fftb);
    TwistFFTrescale<P>(res[0], fftc);

    PolyMulRescaleUnsigned<P>(res[1], aa[1], bb[1]);

    PolyMulRescaleUnsigned<P>(res[2], aa[0], bb[0]);
}

template <class P>
constexpr typename P::T offsetgen()
{
    typename P::T offset = 0;
    for (int i = 1; i <= P::l; i++)
        offset += P::Bg / 2 *
                  (1ULL << (std::numeric_limits<typename P::T>::digits -
                            i * P::Bgbit));
    return offset;
}

template <class P>
inline void Decomposition(DecomposedPolynomial<P> &decvec,
                          const Polynomial<P> &poly)
{
    constexpr typename P::T offset = offsetgen<P>();
    constexpr typename P::T mask =
        static_cast<typename P::T>((1ULL << P::Bgbit) - 1);
    constexpr typename P::T halfBg = (1ULL << (P::Bgbit - 1));

    for (int j = 0; j < P::n; j++) {
        typename P::T temp = poly[j] + offset;
        for (int i = 0; i < P::l; i++)
            decvec[i][j] =
                ((temp >> (std::numeric_limits<typename P::T>::digits -
                           (i + 1) * P::Bgbit)) &
                 mask) -
                halfBg;
    }
}

template <class P>
inline void DecompositionFFT(DecomposedPolynomialInFD<P> &decvecfft,
                             const Polynomial<P> &poly)
{
    DecomposedPolynomial<P> decvec;
    Decomposition<P>(decvec, poly);
    for (int i = 0; i < P::l; i++) TwistIFFT<P>(decvecfft[i], decvec[i]);
}

template <class P>
inline void relinKeySwitch(Ctxt<P> &res, const Polynomial<P> &poly,
                           const relinKeyFFT<P> &relinkeyfft)
{
    DecomposedPolynomialInFD<P> decvecfft;
    DecompositionFFT<P>(decvecfft, poly);
    CtxtInFD<P> resfft;
    MulInFD<P::n>(resfft[0], decvecfft[0], relinkeyfft[0][0]);
    MulInFD<P::n>(resfft[1], decvecfft[0], relinkeyfft[0][1]);
    for (int i = 1; i < P::l; i++) {
        FMAInFD<P::n>(resfft[0], decvecfft[i], relinkeyfft[i][0]);
        FMAInFD<P::n>(resfft[1], decvecfft[i], relinkeyfft[i][1]);
    }
    TwistFFT<P>(res[0], resfft[0]);
    TwistFFT<P>(res[1], resfft[1]);
}

template <class P>
inline void Relinearization(Ctxt<P> &res, const CtxtMult<P> &mult,
                            const relinKeyFFT<P> &relinkeyfft)
{
    Ctxt<P> squareterm;
    relinKeySwitch<P>(squareterm, mult[2], relinkeyfft);
    for (int i = 0; i < P::n; i++) res[0][i] = mult[0][i] + squareterm[0][i];
    for (int i = 0; i < P::n; i++) res[1][i] = mult[1][i] + squareterm[1][i];
}

template <class P>
inline void Multiplication(Ctxt<P> &res, const Ctxt<P> &a, const Ctxt<P> &b,
                           const relinKeyFFT<P> &relinkeyfft)
{
    CtxtMult<P> resmult;
    MultiplicationWithoutRelinerization<P>(resmult, a, b);
    Relinearization<P>(res, resmult, relinkeyfft);
}
}  // namespace BFVpp