#pragma once
#include "Function.h"
#include "BSEq.h"
#include "CNMethod.h"
class AdapterNs :public Function {

public:
	AdapterNs(BSEq* p1_, int imax_, double S_) :BSPDEptr(p1_), imax1(imax_), S01(S_) {}

	double eval(double x) {
		int jmax = static_cast<int> (x);
		CNMethod MethodCrankChooser(BSPDEptr, imax1, jmax);
		MethodCrankChooser.SolvePDE();
		return (MethodCrankChooser.v(0.0, S01));
	}
private:
	BSEq* BSPDEptr;
	int imax1;
	double S01;
};
