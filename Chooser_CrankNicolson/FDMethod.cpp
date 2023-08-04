#include "FDMethod.h"


double FDMethod::v(double t,double x)
{
   int i = (int)(t/m_dt);
   int j = (int)((x-PtrPDE->getxl())/m_dx);
   double l1 = (t-FDMethod::t(i))/m_dt, l0 = 1.0-l1;
   double w1 = (x-FDMethod::x(j))/m_dx, w0 = 1.0-w1;
   return l1*w1*V[i+1][j+1] + l1*w0*V[i+1][j]
         +l0*w1*V[ i ][j+1] + l0*w0*V[ i ][j];
}
