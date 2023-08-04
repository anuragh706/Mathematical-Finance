#pragma once
#include "ExoticOption.h"

class EurCall : public ExoticOption
{
public:
	EurCall(double K, double T, unsigned int m)
		: ExoticOption(T, m), m_K(K) {}
	double BSAnalyticalPrice(const double S0,const double sigma,const double r) const;
	double BSAnalyticalJumpDiffusionPrice(const double S0,const double sigma,const double r,const double lambda,const double m,const double s) const;
	Results MonteCarloPriceHeston(double S0, double r, unsigned int N, double var_mean, double var0, double eta, double rho, double a) const;
	Results MonteCarloPriceJumpDiffusion(double S0, double sigma, double r, double lambda, double m, double s, unsigned int N) const;
private:
	virtual double payoff(const double S) const;
	const double m_K;
};