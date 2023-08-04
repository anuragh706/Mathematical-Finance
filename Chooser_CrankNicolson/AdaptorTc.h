#pragma once
#include "Function.h"
#include "BSEq.h"
#include "CNMethod.h"

class AdapterTc :public Function {

public:
	AdapterTc(BSModel* ModelPtr_, int jmax_, int imax_,double S0_, double K_, double T_, double zl_, double zu_): ModelPtr(ModelPtr_)
		, jmax(jmax_), imax(imax_), S0(S0_), K(K_), T(T_), zl(zl_), zu(zu_) {}

	double eval(double x) {

		ChooserOption chooser(K, T, x, zl, zu, ModelPtr);
		BSEq BSPDEChooser(ModelPtr, &chooser);
		CNMethod MethodCrankChooser(&BSPDEChooser, imax, jmax);
		MethodCrankChooser.SolvePDE();
		return (MethodCrankChooser.v(0.0, S0));
	}
private:
	BSModel* ModelPtr;
	
	int jmax, imax;
	double S0,K, T, zl, zu;
};
