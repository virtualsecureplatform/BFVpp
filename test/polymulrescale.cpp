#include <iostream>

#include "../include/bfv++.hpp"

namespace BFVpp {
template <class P>
inline void PolyMulNaieveRescale(Polynomial<P> &res, const Polynomial<P> &a,
                                 const Polynomial<P> &b)
{
    Polynomial<P> aa, bb;
    for (int i = 0; i < P::n; i++) aa[i] = (a[i] + 1) / 2;
    for (int i = 0; i < P::n; i++) bb[i] = (b[i] + 1) / 2;
    for (int i = 0; i < P::n; i++) {
        __int128_t ri = 0;
        for (int j = 0; j <= i; j++)
            ri += static_cast<__int128_t>(aa[j]) * bb[i - j];
        for (int j = i + 1; j < P::n; j++)
            ri -= static_cast<__int128_t>(aa[j]) * bb[P::n + i - j];
        res[i] = static_cast<typename P::T>((ri) >> (29));
    }
}
}  // namespace BFVpp

int main()
{
    constexpr uint32_t num_test = 1000;

    std::cout << "PolyMulRescale Test" << std::endl;
    for (int test = 0; test < num_test; test++) {
        std::random_device seed_gen;
        std::default_random_engine engine(seed_gen());
        std::uniform_int_distribution<typename BFVpp::Parameter::T> message(
            0, (1ULL << 32) - 1);

        BFVpp::lweKey<BFVpp::Parameter> key =
            BFVpp::lweKeygen<BFVpp::Parameter>();
        BFVpp::Polynomial<BFVpp::Parameter> p0, p1, pres, ptrue;
        for (typename BFVpp::Parameter::T &i : p0) i = message(engine);
        for (typename BFVpp::Parameter::T &i : p1) i = message(engine);

        BFVpp::PolyMulRescale<BFVpp::Parameter>(pres, p0, p1);
        BFVpp::PolyMulNaieveRescale<BFVpp::Parameter>(ptrue, p0, p1);

        for (int i = 0; i < BFVpp::Parameter::n; i++) {
            // std::cout<<pres[i]<<":"<<ptrue[i]<<std::endl;
            assert(abs(static_cast<int>(pres[i] - ptrue[i])) <= 2);
        }
    }
    std::cout << "Passed" << std::endl;
}