#include <iostream>
#include <fstream>
#include "BSModel01.h"
#include "Option.h"
#include "BSEq.h"
#include "ExplicitMethod.h"
#include "Put.h"
#include "CNMethod.h"
#include "Call.h"
#include "ChooserOption.h"
#include<iomanip>
#include "AdaptorNs.h"
#include "AdaptorNt.h"
#include "AdaptorTc.h"

int main()
{
   double S0=100.0, r=0.05, sigma=0.2;
   BSModel Model(S0,r,sigma);

   double K=100.0, T=1.0, zl=0.0, zu=2.0*S0, Tc=0.5;
   int imax = 50, jmax = 1000;
   
   Put EuropeanPut(K,T,zl,zu);
   Call EuropeanCall(K, T, zl, zu);
   /*
   BSEq BSPDEPut(&Model,&EuropeanPut);
   BSEq BSPDECall(&Model, &EuropeanCall);

   
   ExplicitMethod MethodPut(&BSPDEPut, imax, jmax);
   ExplicitMethod MethodCall(&BSPDECall, imax, jmax);

   MethodPut.SolvePDE();
   MethodCall.SolvePDE();

   cout << "Explicit Method Put Price = " << MethodPut.v(0.0,S0) << endl;
   cout << "Explicit Method Call Price = " << MethodCall.v(0.0, S0) << endl;
   CNMethod MethodCrankPut(&BSPDEPut, imax, jmax);
   MethodCrankPut.SolvePDE();

   CNMethod MethodCrankCall(&BSPDECall, imax, jmax);
   MethodCrankCall.SolvePDE();

   cout << "Crank Nicolson Put Price = " << MethodCrankPut.v(0.0, S0) << endl;
   cout << "Crank Nicolson Call Price = " << MethodCrankCall.v(0.0, S0) << endl;

   cout << "Analytical Put Price:" << EuropeanPut.PriceByBSFormula(&Model) << endl;
   cout << "Analytical Call Price:" << EuropeanCall.PriceByBSFormula(&Model) << endl;
   */
   ChooserOption chooser(K, T, Tc,zl, zu,&Model);
   BSEq BSPDEChooser(&Model, &chooser);
   CNMethod MethodCrankChooser(&BSPDEChooser, imax, jmax);
   MethodCrankChooser.SolvePDE();
   
   cout << "Crank Nicolson Chooser Option Price = " << MethodCrankChooser.v(0.0, S0) << endl;
   cout << "Crank Nicolson Chooser Option Analytical Formula Price = " << chooser.PriceByBSFormula(&Model) << endl;

   int tempNs = 5;
   int  maxNs = 1000;
   ofstream fout("AnalysisNs.csv");
   vector<double> xvalues;
   while (tempNs < maxNs ) {
   
	   xvalues.push_back(tempNs);
	   tempNs += 50;
   }

   BSEq* p1 = &BSPDEChooser;
   AdapterNs a1(p1, imax, S0);
   analysis(&a1, xvalues, fout);

   int tempNt = 5;
   int  maxNt = 1000;
   ofstream fout2("AnalysisNt.csv");
   
   //BSEq* p1 = &BSPDEChooser;
   AdapterNt a2(p1, jmax, S0);
   analysis(&a2, xvalues, fout2);

   ofstream fout3("AnalysisTc.csv");

   vector<double> Tcvalues;
   double tempTc = 0.01;
   while (tempTc < T) {

	   Tcvalues.push_back(tempTc);
	   tempTc += 0.02;
   }
   AdapterTc a3(&Model, jmax, imax, S0, K, T, zl, zu);
   analysis(&a3, Tcvalues, fout3);

   cout << "Call Price:" << EuropeanCall.PriceByBSFormula(&Model) << endl;
   cout << "Put Price:" << EuropeanPut.PriceByBSFormula(&Model) << endl;
   return 0;
}
