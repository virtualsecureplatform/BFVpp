#pragma once

#include"./types.hpp"
#include"./encrypt.hpp"

namespace BFVpp{
    template <class P>
    inline constexpr std::array<typename P::T, P::l> hgen()
    {
        std::array<typename P::T, P::l> h{};
        for (int i = 0; i < P::l; i++)
            h[i] = 1ULL << (std::numeric_limits<typename P::T>::digits -
                            (i + 1) * P::Bgbit);
        return h;
    }

    template<class P>
    inline relinKey<P> relinKeygen(const lweKey<P> &key){
        constexpr std::array<typename P::T, P::l> h = hgen<P>();

        Polynomial<P> keysquare;
        PolyMulNaieve<P>(keysquare,key,key);
        relinKey<P> relinkey;
        for (Ctxt<P> &ctxt : relinkey) ctxt = encryptzero<P>(P::α, key);
        for (int i = 0; i < P::l; i++)
            for(int j = 0; j<P::n;j++)  relinkey[i][1][j] += static_cast<typename P::T>(keysquare[j]) * h[i];
        return relinkey;
    }

    template<class P>
    inline relinKeyFFT<P> relinKeyFFTgen(const lweKey<P> &key){
        relinKey<P> relinkey = relinKeygen<P>(key); 
        relinKeyFFT<P> relinkeyfft;
        for (int i = 0; i < P::l; i++)
        for (int j = 0; j < 2; j++) TwistIFFT<P>(relinkeyfft[i][j], relinkey[i][j]);
        return relinkeyfft;
    }
}