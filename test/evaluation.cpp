#include <iostream>

#include "../include/bfv++.hpp"

int main()
{
    std::cout << "Add Test" << std::endl;
    constexpr uint32_t num_test = 1000;
    for (int test = 0; test < num_test; test++) {
        std::random_device seed_gen;
        std::default_random_engine engine(seed_gen());
        std::uniform_int_distribution<typename BFVpp::Parameter::T> message(
            0, BFVpp::Parameter::plain_modulus - 1);

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
        // std::cout<<p[i]<<":"<<p2[i]<<std::endl;
        for (int i = 0; i < BFVpp::Parameter::n; i++) assert(pres[i] == (p0[i]+p1[i])%BFVpp::Parameter::plain_modulus);
    }
    std::cout << "Passed" << std::endl;
}