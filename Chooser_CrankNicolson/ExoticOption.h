#pragma once
#include"BSModel01.h"
#include "Option.h"
class ExoticOption: public Option
{
public:
    ExoticOption(const double T_, const double zl_, const double zu_) :Option(T_, zl_, zu_) {}
    double getMaturity() {return m_T;}
    virtual double Payoff(double z) const = 0;
    virtual double UpperBdCond(BSModel* PtrModel, double t) const = 0;
    virtual double LowerBdCond(BSModel* PtrModel, double t) const = 0;


};