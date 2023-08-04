#pragma once
#include "ExoticOption.h"

double N(double x) ;
class UpandOutBarrierCall : public ExoticOption
{
public:
	UpandOutBarrierCall(double K, double T,double B)
		: ExoticOption(T), m_K(K), m_B(B) {}
	double BSFormulaPrice(double S0, double sigma, double r) const;
private:
	double payoff(double S) const
	{
		return S > m_K ? S-m_K : 0.0;
	}
	bool hasKnockedOut(double ST) const
	{
		if (ST > m_B) return true;
		else return false;
	}
	double D(double x, double sigma, double r) const;
	
	const double m_K,m_B;
};

/*
Option price: 3.25522
Analyical price: 3.23758

*/