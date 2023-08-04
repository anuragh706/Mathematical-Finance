#pragma once
#include "ExoticOption.h"
class UpAndOutBarrier:public ExoticOption {
public:

	UpAndOutBarrier() :ExoticOption(0.0), m_B(0.0), m_K(0.0) {}
	UpAndOutBarrier(double T, double B, double K) :ExoticOption(T), m_B(B), m_K(K) {}
	virtual double BSFormulaPrice(double S0, double sigma, double r) const;
private:
	const double m_K;
	const double m_B;
	virtual double payoff(const double S) const;
	virtual bool hasBreached(const double S) const;
	virtual void applyBoundaryConditions(double& lowerS, double& upperS, const double& r, const double& t) const;
	double getSmax() const { return m_B; }
	double D(double x, double sigma, double r) const;
	double N(double x) const;
	
};
