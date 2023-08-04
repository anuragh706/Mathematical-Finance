#ifndef ExplicitMethod_h
#define ExplicitMethod_h

#include "FDMethod.h"

class ExplicitMethod: public FDMethod
{
   public:
      ExplicitMethod(ParabPDE* PtrPDE_,const int imax_,const  int jmax_)
         : FDMethod(PtrPDE_, imax_, jmax_) {}

      double A(int i, int j)
      {
          return m_dt * (b(i, j) / 2.0 - a(i, j) / m_dx) / m_dx;
      }
      double B(int i, int j)
      {
          return 1.0 - m_dt * c(i, j) + 2.0 * m_dt * a(i, j) / (m_dx * m_dx);
      }
      double C(int i, int j)
      {
          return -m_dt * (b(i, j) / 2.0 + a(i, j) / m_dx) / m_dx;
      }
      double D(int i, int j)
      {
          return -m_dt * d(i, j);
      }

      void SolvePDE();


      
};

#endif
