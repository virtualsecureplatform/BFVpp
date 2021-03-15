#pragma once

#include "../thirdparties/spqlios/spqlios-fft.h"
#include "./types.hpp"
#include "./utils.hpp"

namespace BFVpp {

template <class P>
inline void TwistFFT(Polynomial<P> &res, const PolynomialInFD<P> &a)
{
    if constexpr (std::is_same_v<typename P::T, uint32_t>)
        fftplvl1.execute_direct_torus32(res.data(), a.data());
    else if constexpr (std::is_same_v<typename P::T, uint64_t>)
        fftplvl2.execute_direct_torus64(res.data(), a.data());
    else
        static_assert(false_v<typename P::T>, "Undefined TwistFFT!");
}

template <class P>
inline void TwistFFTrescale(Polynomial<P> &res, const PolynomialInFD<P> &a)
{
    if constexpr (std::is_same_v<typename P::T, uint32_t>)
        fftplvl1.execute_direct_torus32_rescale(res.data(), a.data());
    // else if constexpr (std::is_same_v<typename P::T, uint64_t>)
    //     fftplvl2.execute_direct_torus64_rescale(res.data(), a.data());
    else
        static_assert(false_v<typename P::T>, "Undefined TwistFFT!");
}

template <class P>
inline void TwistIFFT(PolynomialInFD<P> &res, const Polynomial<P> &a)
{
    if constexpr (std::is_same_v<typename P::T, uint32_t>)
        fftplvl1.execute_reverse_torus32(res.data(), a.data());
    else if constexpr (std::is_same_v<typename P::T, uint64_t>)
        fftplvl2.execute_reverse_torus64(res.data(), a.data());
    else
        static_assert(false_v<typename P::T>, "Undefined TwistIFFT!");
}

template <class P>
inline void PolyMul(Polynomial<P> &res, const Polynomial<P> &a,
                    const Polynomial<P> &b)
{
    if constexpr (std::is_same_v<typename P::T, uint32_t>) {
        PolynomialInFD<P> ffta;
        TwistIFFT<P>(ffta, a);
        PolynomialInFD<P> fftb;
        TwistIFFT<P>(fftb, b);
        MulInFD<P::n>(ffta, ffta, fftb);
        TwistFFT<P>(res, ffta);
    }
    else if constexpr (std::is_same_v<typename P::T, uint64_t>) {
        for (int i = 0; i < P::n; i++) {
            typename P::T ri = 0;
            for (int j = 0; j <= i; j++)
                ri +=
                    static_cast<typename std::make_signed<typename P::T>::type>(
                        a[j]) *
                    b[i - j];
            for (int j = i + 1; j < P::n; j++)
                ri -=
                    static_cast<typename std::make_signed<typename P::T>::type>(
                        a[j]) *
                    b[P::n + i - j];
            res[i] = ri;
        }
    }
    else
        static_assert(false_v<typename P::T>, "Undefined PolyMul!");
}

template <class P>
inline void RemoveSign(UnsignedPolynomial<P> &res, const Polynomial<P> &a){
    for(int i = 0;i<P::n;i++) res[i] = (a[i]+1)/2;
}

template <class P>
inline void PolyMulRescaleUnsigned(Polynomial<P> &res, const UnsignedPolynomial<P> &a,
                    const UnsignedPolynomial<P> &b)
{
    if constexpr (std::is_same_v<typename P::T, uint32_t>) {
        PolynomialInFD<P> ffta,fftb;
        TwistIFFT<P>(ffta, a);
        TwistIFFT<P>(fftb, b);
        MulInFD<P::n>(ffta, ffta, fftb);
        TwistFFTrescale<P>(res, ffta);
    }
    else
        static_assert(false_v<typename P::T>, "Undefined PolyMul!");
}

template <class P>
inline void PolyMulRescale(Polynomial<P> &res, const Polynomial<P> &a,
                    const Polynomial<P> &b)
{
    if constexpr (std::is_same_v<typename P::T, uint32_t>) {
        UnsignedPolynomial<P> aa,bb;
        RemoveSign<P>(aa,a);
        RemoveSign<P>(bb,b);
        PolyMulRescaleUnsigned<P>(res,aa,bb);
    }
    else
        static_assert(false_v<typename P::T>, "Undefined PolyMul!");
}

template <class P>
inline void PolyMulNaieve(Polynomial<P> &res, const Polynomial<P> &a,
                    const Polynomial<P> &b)
{
    for (int i = 0; i < P::n; i++) {
        typename P::T ri = 0;
        for (int j = 0; j <= i; j++)
            ri +=
                static_cast<typename std::make_signed<typename P::T>::type>(
                    a[j]) *
                b[i - j];
        for (int j = i + 1; j < P::n; j++)
            ri -=
                static_cast<typename std::make_signed<typename P::T>::type>(
                    a[j]) *
                b[P::n + i - j];
        res[i] = ri;
    }
}

}  // namespace BFVpp