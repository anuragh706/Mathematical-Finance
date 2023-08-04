#pragma once
//double BisectionSolver(const Function* f, double c, double left, double right, double acc);
class Function {

public:

	virtual double eval(double x) const =0;

};
