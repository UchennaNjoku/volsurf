#include "IVSolver.hpp"
#include <cassert>
#include <iostream>

int main() {
    // sample values
    double mkt_price = 2.5, S = 100.5, K = 102.4, T = 30/365, r = 0.01, q = 4.0;
    double iv = solveIV(mkt_price, S, K, T, r, q);
    std::cout << "IV stub returned: " << iv << "\n"; 
    assert(iv >0 && iv < 5);
    std::cout << "IV test passed! \n";
    return 0;
}
