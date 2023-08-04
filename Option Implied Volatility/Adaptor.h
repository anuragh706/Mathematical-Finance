#pragma once
#include "Function.h"
#include"EurCall.h"
class Adaptor: public Function {
public:
	Adaptor(const EurCall* call,double S, double r1) :ptr(call),S0(S), r(r1){}
	double eval(double x) const {
		return ptr->BSAnalyticalPrice(S0,x,r);
	}
private:
	const EurCall* ptr;
	const double S0, r;
	
};