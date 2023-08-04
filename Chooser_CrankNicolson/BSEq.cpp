#include "BSEq.h"
#include <cmath>



double BSEq::a(double t, double z)
{
   return -0.5*pow(PtrModel->getSigma()*z,2.0);
}

double BSEq::b(double t, double z)
{
   return -PtrModel->getRate()*z;
}

double BSEq::c(double t, double z)
{
   return PtrModel->getRate();
}

double BSEq::d(double t, double z)
{
   return 0.0;
}

double BSEq::f(double z)
{
   return PtrOption->Payoff(z);
}

double BSEq::fl(double t)
{
   return PtrOption->LowerBdCond(PtrModel,t);
}

double BSEq::fu(double t)
{
   return PtrOption->UpperBdCond(PtrModel,t);
}
