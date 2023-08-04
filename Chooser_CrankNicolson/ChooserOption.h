#pragma once
#include "ExoticOption.h"
#include "Call.h"
#include "Put.h"
class ChooserOption : public ExoticOption
{
public:

    ChooserOption(double K_, double T_, double Tc_, double zl_, double zu_,BSModel *ptr_) :ExoticOption(T_, zl_, zu_), m_K(K_), m_Tc(Tc_), ptr(ptr_) {}
    double PriceByBSFormula(BSModel* PtrModel) const;
    double getMaturity() { return m_Tc; }
private:
    virtual double Payoff(double z) const;
    double UpperBdCond(BSModel* PtrModel, double t) const;
    double LowerBdCond(BSModel* PtrModel, double t) const;
    
    const double m_K, m_Tc;
    
    BSModel* ptr;
};
