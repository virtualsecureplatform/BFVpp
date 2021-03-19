#include <iostream>

#include "../include/bfv++.hpp"

namespace BFVpp{
template<class P>
inline Polynomial<P> decryptCtxtMult(const CtxtMult<P> &c, const lweKey<P> &key)
{
    Polynomial<P> mulres, p,keysquare;
    PolyMul<P>(mulres, c[0], key);
    Polynomial<P> phase = c[1];
    for (int i = 0; i < P::n; i++) phase[i] -= mulres[i];

    PolyMulNaieve<P>(keysquare,key,key);
    PolyMul<P>(mulres, c[2], keysquare);
    for (int i = 0; i < P::n; i++) phase[i] += mulres[i];

    for (int i = 0; i < P::n; i++)
        p[i] = static_cast<typename P::T>(std::round(phase[i] / P::Δ)) %
               P::plain_modulus;
    return p;
}
}

int main()
{
    constexpr uint32_t num_test = 1000;
    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());

    std::cout << "Add Test" << std::endl;
    for (int test = 0; test < num_test; test++) {
        std::uniform_int_distribution<typename BFVpp::Parameter::T> message(0, BFVpp::Parameter::plain_modulus - 1);

        BFVpp::lweKey<BFVpp::Parameter> key =
            BFVpp::lweKeygen<BFVpp::Parameter>();
        BFVpp::Polynomial<BFVpp::Parameter> p0, p1,pres;
        for (typename BFVpp::Parameter::T &i : p0) i = message(engine);
        for (typename BFVpp::Parameter::T &i : p1) i = message(engine);

        BFVpp::Ctxt<BFVpp::Parameter> c0 =
            BFVpp::encrypt<BFVpp::Parameter>(p0, BFVpp::Parameter::α, key);
        BFVpp::Ctxt<BFVpp::Parameter> c1 =
            BFVpp::encrypt<BFVpp::Parameter>(p1, BFVpp::Parameter::α, key);
        BFVpp::Ctxt<BFVpp::Parameter> cres;
        BFVpp::Add<BFVpp::Parameter>(cres,c0,c1);
        pres = BFVpp::decrypt<BFVpp::Parameter>(cres, key);
        // for (int i = 0; i < BFVpp::Parameter::n; i++)
        // std::cout<<p0[i]<<":"<<p1[i]<<std::endl;
        for (int i = 0; i < BFVpp::Parameter::n; i++) assert(pres[i] == (p0[i]+p1[i])%BFVpp::Parameter::plain_modulus);
    }
    std::cout << "Passed" << std::endl;

    std::cout << "Mul without Relinerarization Test" << std::endl;
    for (int test = 0; test < num_test; test++) {
        std::uniform_int_distribution<typename BFVpp::Parameter::T> message(
            0, BFVpp::Parameter::plain_modulus - 1);

        BFVpp::lweKey<BFVpp::Parameter> key =
            BFVpp::lweKeygen<BFVpp::Parameter>();
        BFVpp::Polynomial<BFVpp::Parameter> p0, p1,pres,ptrue;
        for (typename BFVpp::Parameter::T &i : p0) i = message(engine);
        for (typename BFVpp::Parameter::T &i : p1) i = message(engine);

        BFVpp::Ctxt<BFVpp::Parameter> c0 =
            BFVpp::encrypt<BFVpp::Parameter>(p0, BFVpp::Parameter::α, key);
        BFVpp::Ctxt<BFVpp::Parameter> c1 =
            BFVpp::encrypt<BFVpp::Parameter>(p1, BFVpp::Parameter::α, key);
        BFVpp::CtxtMult<BFVpp::Parameter> cres;
        BFVpp::MultiplicationWithoutRelinerization<BFVpp::Parameter>(cres,c0,c1);
        pres = BFVpp::decryptCtxtMult<BFVpp::Parameter>(cres, key);

        BFVpp::PolyMulNaieve<BFVpp::Parameter>(ptrue,p0,p1);
        for (int i = 0; i < BFVpp::Parameter::n; i++) ptrue[i] %= BFVpp::Parameter::plain_modulus;

        // for (int i = 0; i < BFVpp::Parameter::n; i++)
        //     std::cout<<pres[i]<<":"<<ptrue[i]<<std::endl;
        for (int i = 0; i < BFVpp::Parameter::n; i++) assert(pres[i] == ptrue[i]);
    }
    std::cout << "Passed" << std::endl;

    BFVpp::lweKey<BFVpp::Parameter> key =
            BFVpp::lweKeygen<BFVpp::Parameter>();
    BFVpp::relinKeyFFT<BFVpp::Parameter> relinkeyfft = BFVpp::relinKeyFFTgen<BFVpp::Parameter>(key);

    std::cout << "Mul Test" << std::endl;
    for (int test = 0; test < num_test; test++) {
        std::uniform_int_distribution<typename BFVpp::Parameter::T> message(
            0, BFVpp::Parameter::plain_modulus - 1);

        BFVpp::Polynomial<BFVpp::Parameter> p0, p1,pres,ptrue;
        for (typename BFVpp::Parameter::T &i : p0) i = message(engine);
        for (typename BFVpp::Parameter::T &i : p1) i = message(engine);

        BFVpp::Ctxt<BFVpp::Parameter> c0 =
            BFVpp::encrypt<BFVpp::Parameter>(p0, BFVpp::Parameter::α, key);
        BFVpp::Ctxt<BFVpp::Parameter> c1 =
            BFVpp::encrypt<BFVpp::Parameter>(p1, BFVpp::Parameter::α, key);
        BFVpp::Ctxt<BFVpp::Parameter> cres;
        BFVpp::Multiplication<BFVpp::Parameter>(cres,c0,c1,relinkeyfft);
        pres = BFVpp::decrypt<BFVpp::Parameter>(cres, key);

        BFVpp::PolyMulNaieve<BFVpp::Parameter>(ptrue,p0,p1);
        for (int i = 0; i < BFVpp::Parameter::n; i++) ptrue[i] %= BFVpp::Parameter::plain_modulus;

        // for (int i = 0; i < BFVpp::Parameter::n; i++)
        //     std::cout<<pres[i]<<":"<<ptrue[i]<<std::endl;
        for (int i = 0; i < BFVpp::Parameter::n; i++) assert(pres[i] == ptrue[i]);
    }
    std::cout << "Passed" << std::endl;
}