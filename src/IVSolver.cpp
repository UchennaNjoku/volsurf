#include "IVSolver.hpp"
#include <cmath>
#include <stdexcept>

double solveIV(double price, double S, double K, double T, double r, double q) {
    // TODO: Newton-Raphson + bisection fallback
    return 0.2; // placeholder
}

std::vector<double> computeIVGrid(
    const std::vector<double>& prices,
    double S,
    const std::vector<double>& strikes,
    const std::vector<double>& expiries,
    double r,
    double q
) {
    std::vector<double> vols;
    vols.reserve(prices.size());
    for (size_t i = 0; i < prices.size(); ++i) {
        vols.push_back(solveIV(prices[i], S, strikes[i], expiries[i], r, q));
    }
    return vols;
}
