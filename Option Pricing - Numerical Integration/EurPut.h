#pragma once
#include "EurOption.h"

class EurPut: public EurOption
{
public:
    EurPut(double T_, double K_) : EurOption(T_, K_) {}
        double PriceByBSFormula(double S0,
        double sigma, double r);
        double DeltaByBSFormula(double, double, double);
        double GammaByBSFormula(double, double, double);
        double ThetaByBSFormula(double, double, double);
        double PriceByNumericalIntergration(double S0, double sigma, double r);
private:
    
    double payoff(double ST, double K);
};

