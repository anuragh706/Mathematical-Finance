#include "ImplicitScheme.h"
#include "Matrix.h"
#include <cmath>

Vector ImplicitScheme::w(int i)
{
   Vector w(m_jmax+1);
   w[1]=D(i,1)+A(i,1)*fl(i)-E(i,1)*fl(i-1);
   for (int j=2;j<m_jmax-1;j++) w[j]=D(i,j);
   w[m_jmax-1]=D(i,m_jmax-1)+C(i,m_jmax-1)*fu(i)-G(i,m_jmax-1)*fu(i-1);
   return w;
}

Vector ImplicitScheme::A(int i, Vector q)
{
   Vector p(m_jmax+1);
   p[1]=B(i,1)*q[1]+C(i,1)*q[2];
   for (int j=2;j<m_jmax-1;j++)
   {
      p[j]=A(i,j)*q[j-1]+B(i,j)*q[j]+C(i,j)*q[j+1];
   }
   p[m_jmax-1]=A(i,m_jmax-1)*q[m_jmax-2]+B(i,m_jmax-1)*q[m_jmax-1];
   return p;
}

Vector ImplicitScheme::LUDecomposition(int i, Vector q)
{
   Vector p(m_jmax+1), r(m_jmax+1), y(m_jmax+1);
   r[1]=F(i,1);
   y[1]=q[1];
   for (int j=2;j<m_jmax;j++)
   {
      r[j]=F(i,j)-E(i,j)*G(i,j-1)/r[j-1];
      y[j]=q[j]-E(i,j)*y[j-1]/r[j-1];
   }
   p[m_jmax-1]=y[m_jmax-1]/r[m_jmax-1];
   for (int j=m_jmax-2; j>0; j--)
   {
      p[j]=(y[j]-G(i,j)*p[j+1])/r[j];
   }
   return p;
}

void ImplicitScheme::SolvePDE()
{
   for (int j=0; j<=m_jmax; j++) V[m_imax][j]=f(j);
   for (int i=m_imax; i>0; i--)
   {
      V[i-1]=LUDecomposition(i,A(i,V[i])+w(i));
      V[i-1][0]=fl(i-1);
      V[i-1][m_jmax]=fu(i-1);
   }
}
