#pragma once
#include <vector>

// Solve for implied vol, given market price
// s -> underlying spot price | K -> option strike price | T -> time to expiry (years)
// r -> risk-free interest rate (annualized) | q -> continuous dividend yied
double solveIV(double price, double S, double K, double T, double r, double q);

// Vectorized interface
// batch-computing of IVs over many strikes and expiries
std::vector<double> computeIVGrid(
    const std::vector<double>& prices,
    double S,
    const std::vector<double>& strikes,
    const std::vector<double>& expiries,
    double r,
    double q
);
