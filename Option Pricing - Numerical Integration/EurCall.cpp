#include "EurCall.h"
#include <cmath>
#include <algorithm>
#include<iostream>
using namespace std;

double EurCall::PriceByBSFormula(double S0,double sigma, double r)
{
   return S0*N(d_plus(S0,sigma,r))
      -K*exp(-r*T)*N(d_minus(S0,sigma,r));
}
double EurCall::DeltaByBSFormula(double S0,double sigma, double r) {

    return (N(d_plus(S0, sigma, r)));
}
double EurCall::GammaByBSFormula(double S0, double sigma, double r) {
    return (N_dash(d_plus(S0, sigma, r)) / (S0 * sigma * sqrt(T)));
}
double EurCall::ThetaByBSFormula(double S0, double sigma, double r) {

    double term_1 = N_dash(d_plus(S0, sigma, r)) * (S0 * sigma) / (2 * sqrt(T));
    double term_2 = r * K * exp(-r * T) * N(d_minus(S0, sigma, r));

    return ((-term_1-term_2));
}
double EurCall::payoff(double ST, double K) {
    return max(ST - K, 0.0);
}
double EurCall::PriceByNumericalIntergration(double S0, double sigma, double r) {

    double lower_limit = K;
    double delta_ST = (max_num - lower_limit) / total_steps;
    double ST = lower_limit;
    double ST_plus_ds = lower_limit + delta_ST;
    //double p, q; // initialise
    double area = 0.0;
 
    for (int i = 0; i < total_steps; i++) {
        
        double p = pdf(S0, sigma, r, T, ST) * payoff(ST, K);
        
        double q= pdf(S0, sigma, r, T, ST_plus_ds) * payoff(ST_plus_ds, K);  // try reducing the iterations
        area = area + (p + q) / 2;
        //cout << area<<endl;
        ST = ST_plus_ds;
        ST_plus_ds = ST_plus_ds + delta_ST;

    }
    return area * exp(-r * T);
  
}