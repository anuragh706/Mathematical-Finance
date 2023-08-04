#pragma once
#include <cmath>



class ExoticOption
{
public:
	ExoticOption(double T) : m_T(T) {}
	double binomialTreePrice(double S0, double sigma, double r, int N) const;
	virtual double BSFormulaPrice(double S0, double sigma, double r) const=0;
protected:
	virtual double payoff(double S) const = 0;
	virtual bool hasKnockedOut(double S) const= 0;
	
	const double m_T;
};
