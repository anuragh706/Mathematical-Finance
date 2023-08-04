#pragma once
#include "BSModel01.h"

class Option {

public:
    Option(const double T_, const double zl_, const double zu_) :m_T(T_), m_zl(zl_), m_zu(zu_) {}
    virtual double Payoff(double z) const = 0;
    virtual double UpperBdCond(BSModel* PtrModel, double t) const = 0;
    virtual double LowerBdCond(BSModel* PtrModel, double t) const = 0;
    virtual double getMaturity() { return m_T; }
    double getMinS() { return m_zl; }
    double getMaxS() { return m_zu; }
protected:
    const double m_T, m_zl, m_zu;
};
