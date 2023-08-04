#ifndef FDMethod_h
#define FDMethod_h
#include <vector>
#include "ParabPDE.h"

using namespace std;
typedef vector<double> Vector;

class FDMethod
{
   public:
      
       FDMethod(ParabPDE* PtrPDE_, int imax_, int jmax_) :PtrPDE(PtrPDE_), m_imax(imax_), m_jmax(jmax_) 
       { 
           m_dx = (PtrPDE->getxu() - PtrPDE->getxl()) / m_jmax;
           m_dt = PtrPDE->getT() / m_imax;
           V.resize(m_imax + 1);
           for (int i = 0; i <= m_imax; i++) V[i].resize(m_jmax + 1);
         }

      double t(double i){return m_dt*i;}
      double x(int j){return PtrPDE->getxl()+m_dx*j;}

      double a(double i,int j){return PtrPDE->a(t(i),x(j));}
      double b(double i,int j){return PtrPDE->b(t(i),x(j));}
      double c(double i,int j){return PtrPDE->c(t(i),x(j));}
      double d(double i,int j){return PtrPDE->d(t(i),x(j));}

      double f (int j){return PtrPDE->f(x(j));}
      double fu(int i){return PtrPDE->fu(t(i));}
      double fl(int i){return PtrPDE->fl(t(i));}

      double v(double t,double x);

protected:

    ParabPDE* PtrPDE;
    int m_imax, m_jmax;
    double m_dx, m_dt;
    vector<Vector> V;
};

#endif
