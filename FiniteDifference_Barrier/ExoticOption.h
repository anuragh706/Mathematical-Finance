#pragma once

class ExoticOption {
public:
	ExoticOption() :m_T(0.0) {}
	ExoticOption(const double T) :m_T(T) {}
	double PriceByFiniteDifference(const double S0, const double sigma, const double r, const unsigned int Nt, const unsigned int Ns) const;
	virtual double BSFormulaPrice(double S0, double sigma, double r) const = 0;
protected:
	const double m_T;
	virtual double payoff(const double S) const = 0;
	virtual bool hasBreached(const double S) const = 0;
	virtual void applyBoundaryConditions(double& lowerS, double& upperS, const double& r, const double& t) const = 0;
	virtual double getSmax() const = 0;
	
};
