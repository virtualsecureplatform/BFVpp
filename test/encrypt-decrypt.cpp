#include "../include/bfv++.hpp"

#include<iostream>

int main(){
    std::cout<<"Encrypt-Decrypt Test"<<std::endl;
    constexpr uint32_t num_test = 1000;
    for (int test = 0; test < num_test; test++) {
        std::random_device seed_gen;
        std::default_random_engine engine(seed_gen());
        std::uniform_int_distribution<typename BFVpp::Parameter::T> message(0, BFVpp::Parameter::plain_modulus-1);

        BFVpp::lweKey<BFVpp::Parameter> key = BFVpp::lweKeygen<BFVpp::Parameter>();
        BFVpp::Polynomial<BFVpp::Parameter> p,p2;
        for (typename BFVpp::Parameter::T &i : p) i = message(engine);
        BFVpp::Ctxt<BFVpp::Parameter> c =
            BFVpp::encrypt<BFVpp::Parameter>(p, BFVpp::Parameter::α, key);
        p2 = BFVpp::decrypt<BFVpp::Parameter>(c, key);
        // for (int i = 0; i < BFVpp::Parameter::n; i++) std::cout<<p[i]<<":"<<p2[i]<<std::endl;
        for (int i = 0; i < BFVpp::Parameter::n; i++) assert(p[i] == p2[i]);
    }
    std::cout << "Passed" << std::endl;
}