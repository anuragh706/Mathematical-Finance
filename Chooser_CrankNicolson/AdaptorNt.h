#pragma once
#include "Function.h"
#include "BSEq.h"
#include "CNMethod.h"
class AdapterNt :public Function {

public:
	AdapterNt(BSEq* p1_, int jmax_, double S_) :BSPDEptr(p1_), jmax1(jmax_), S01(S_) {}

	double eval(double x) {
		int imax = static_cast<int> (x);
		CNMethod MethodCrankChooser(BSPDEptr, imax, jmax1);
		MethodCrankChooser.SolvePDE();
		return (MethodCrankChooser.v(0.0, S01));
	}
private:
	BSEq* BSPDEptr;
	int jmax1;
	double S01;
};
