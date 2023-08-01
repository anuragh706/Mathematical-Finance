#include "EurOption.h"
#include <cmath>
#include<iostream>
using namespace std;
double EurOption::N(double x)
{
    double gamma = 0.2316419;     double a1 = 0.319381530;
    double a2 = -0.356563782;   double a3 = 1.781477937;
    double a4 = -1.821255978;   double a5 = 1.330274429;
    double pi = 4.0 * atan(1.0); double k = 1.0 / (1.0 + gamma * x);
    if (x >= 0.0)
    {
        return 1.0 - ((((a5 * k + a4) * k + a3) * k + a2) * k + a1)
            * k * exp(-x * x / 2.0) / sqrt(2.0 * pi);
    }
    else return 1.0 - N(-x);
}

double EurOption::d_plus(double S0, double sigma, double r)
{
    return (log(S0 / K) +
        (r + 0.5 * pow(sigma, 2.0)) * T)
        / (sigma * sqrt(T));
}

double EurOption::d_minus(double S0, double sigma, double r)
{
    return d_plus(S0, sigma, r) - sigma * sqrt(T);
}

double EurOption::N_dash(double d) {

    double pi = 4.0 * atan(1.0);
    return (exp(-d * d / 2.0)) / sqrt(2.0 * pi);
}

double EurOption::pdf(double S0, double sigma, double r, double T, double ST) {
    
    double m = log(S0) + (r - 0.5 * sigma * sigma) * T;
    double s = sigma * sqrt(T);

    //cout << "power term" << -pow((log(ST) - m), 2) << endl;
    //cout<< "exp term" << exp(-pow((log(ST) - m), 2) / (2 * s * s)) << endl;
    double exp_term = exp(-pow((log(ST) - m), 2) / (2*s * s));
    double pi = 4.0 * atan(1.0);
    
    return (exp_term) / (ST * s * sqrt(2 * pi));
}
