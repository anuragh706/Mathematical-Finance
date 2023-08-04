#pragma once
#include "VanillaOption.h"
class Call : public VanillaOption
{
public:

    Call(double K_, double T_, double zl_, double zu_) :VanillaOption(T_, zl_, zu_), m_K(K_) {}
    double PriceByBSFormula(BSModel* PtrModel) const;
    double getMaturity() { return m_T; }
private:
    virtual double Payoff(double z) const;
    double UpperBdCond(BSModel* PtrModel, double t) const;
    double LowerBdCond(BSModel* PtrModel, double t) const;

    const double m_K;
};
