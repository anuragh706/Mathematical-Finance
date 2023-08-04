#pragma once
#include "Option.h"

class ExoticOption :public Option {


public:
	ExoticOption(const double m_T_) : Option(m_T_) {}

protected:

	virtual double payoff(const vector <double>& S) const = 0;
	virtual double payoff(const double& S) const = 0;

};

