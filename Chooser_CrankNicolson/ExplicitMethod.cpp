#include "ExplicitMethod.h"

void ExplicitMethod::SolvePDE()
{
   for (int j=0; j<=m_jmax; j++) V[m_imax][j]=f(j);
   for (int i=m_imax; i>0; i--)
   {
      V[i-1][0]=fl(i-1);
      V[i-1][m_jmax]=fu(i-1);
      for (int j=1;j<m_jmax;j++)
      {
         V[i-1][j]=A(i,j)*V[i][j-1]+B(i,j)*V[i][j]
	          +C(i,j)*V[i][j+1]+D(i,j);
         
      }
   }
}
