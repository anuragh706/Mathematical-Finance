#ifndef Option_h
#define Option_h
#include "Option.h"
#include "BSModel01.h"

class VanillaOption: public Option
{
public:
    VanillaOption(const double T_, const double zl_, const double zu_) :Option(T_, zl_, zu_) {}
    virtual double Payoff(double z) const = 0;
    virtual double UpperBdCond(BSModel* PtrModel, double t) const = 0;
    virtual double LowerBdCond(BSModel* PtrModel, double t) const = 0;
    double getMaturity() { return m_T; }
};



#endif
