#pragma once
#include<limits>
class EurOption {

public:
    EurOption() :T(0), K(0.0){};
    EurOption(double T_, double K_) { T = T_; K = K_;}
    virtual double PriceByBSFormula(double S0,double sigma, double r) = 0;
    virtual double DeltaByBSFormula(double S0,double sigma, double r)=0;
    virtual double GammaByBSFormula(double S0,double sigma, double r) = 0;
    virtual double ThetaByBSFormula(double S0,double sigma, double r) = 0;
    virtual double PriceByNumericalIntergration(double S0, double sigma, double r) = 0;
    
protected:
    double T, K;
    double d_plus(double S0, double sigma, double r);
    double d_minus(double S0, double sigma, double r);
    double N(double);
    double N_dash(double); //// global functuon since not dependent on class
    double pdf(double S0, double sigma, double r, double T, double ST);  // we can avoid T here since it is a member variable
    double max_num = 1000000.0;
    double min_num = -1000000.0;
    double total_steps = 1000000.0;
    
};