#ifndef EurCall_h
#define EurCall_h
#include "EurOption.h"

class EurCall:public EurOption
{
   public:
      EurCall(double T_, double K_) : EurOption(T_, K_) {}
      double PriceByBSFormula(double S0,double sigma, double r);
      double DeltaByBSFormula(double, double, double);
      double GammaByBSFormula(double, double, double);
      double ThetaByBSFormula(double, double, double);
      double PriceByNumericalIntergration(double S0, double sigma, double r);  /// Add this to base class
    private:
      double payoff(double, double);
};

#endif
