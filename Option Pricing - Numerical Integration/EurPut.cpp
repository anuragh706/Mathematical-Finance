#include "EurPut.h"
#include <cmath>
#include <algorithm>
using namespace std;
double EurPut::PriceByBSFormula(double S0,
    double sigma, double r)
{
    return -(S0 * N(-d_plus(S0, sigma, r))
        - K * exp(-r * T) * N(-d_minus(S0, sigma, r)));
}
double EurPut::DeltaByBSFormula(double S0,
    double sigma, double r) {
    return (-N(-d_plus(S0, sigma, r)));
}
double EurPut::GammaByBSFormula(double S0,
    double sigma, double r) {
    return (N_dash(d_plus(S0, sigma, r))/(S0*sigma*sqrt(T)));
}
double EurPut::ThetaByBSFormula(double S0, double sigma, double r) {

    double term_1 = N_dash(d_plus(S0, sigma, r)) * (S0 * sigma) / (2 * sqrt(T));
    double term_2 = r * K * exp(-r * T) * N(-d_minus(S0, sigma, r));
    return ((-term_1 + term_2));
}

double EurPut::payoff(double ST, double K) {
    return max(ST - K, 0.0);
}
double EurPut::PriceByNumericalIntergration(double S0, double sigma, double r) {

    double lower_limit = (log(K / S0) - (r - sigma * sigma * 0.5) * T) / (sigma * sqrt(T));
    double delta_ST = (max_num - lower_limit) / total_steps;
    double x = lower_limit;
    double x_plus_ds = lower_limit + delta_ST;
    double p, q;
    double area = 0.0;
    for (int i = 0; i < total_steps; i++) {

        p = pdf(S0, sigma, r, T, x) * payoff(x, K);
        q = pdf(S0, sigma, r, T, x_plus_ds) * payoff(x_plus_ds, K);
        area = area + (p + q) / 2;
        x = x_plus_ds;
        x_plus_ds = x_plus_ds + delta_ST;

    }

    return area * exp(-r * T);

}
