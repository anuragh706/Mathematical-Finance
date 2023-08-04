#include "UpAndOutBarrier.h"
#include <cmath>
bool UpAndOutBarrier::hasBreached(const double S) const {

	return (S > m_B ? 1 : 0);
}
double UpAndOutBarrier::payoff(double S) const {
	
	return (S > m_K ? (S - m_K) : 0);
}

void UpAndOutBarrier::applyBoundaryConditions(double& lowerS, double& upperS,const double& r, const double& t) const {

	lowerS = m_K * exp(-r * (m_T - t));
	upperS = 0.0;
}


double UpAndOutBarrier::N(double x) const
{
	double gamma = 0.2316419;     double a1 = 0.319381530;
	double a2 = -0.356563782;   double a3 = 1.781477937;
	double a4 = -1.821255978;   double a5 = 1.330274429;
	double pi = 4.0 * atan(1.0); double k = 1.0 / (1.0 + gamma * x);
	if (x >= 0.0)
	{
		return 1.0 - ((((a5 * k + a4) * k + a3) * k + a2) * k + a1)
			* k * exp(-x * x / 2.0) / sqrt(2.0 * pi);
	}
	else return 1.0 - N(-x);
}


double UpAndOutBarrier::D(double x, double sigma, double r) const {
	return (log(x) + (r + 0.5 * sigma * sigma) * m_T) / (sigma * sqrt(m_T));
}

double UpAndOutBarrier::BSFormulaPrice(double S0, double sigma, double r) const {

	const double d1 = D(S0 / m_K, sigma, r);
	const double d3 = D(S0 / m_B, sigma, r);
	const double d5 = D(S0 / m_B, sigma, -r);
	const double d7 = D(S0 * m_K / (m_B * m_B), sigma, -r);
	const double d2 = d1 - sigma * sqrt(m_T);
	const double d4 = d3 - sigma * sqrt(m_T);
	const double d6 = d5 - sigma * sqrt(m_T);
	const double d8 = d7 - sigma * sqrt(m_T);

	const double Nd1 = N(d1);
	const double Nd2 = N(d2);
	const double Nd3 = N(d3);
	const double Nd4 = N(d4);
	const double Nd5 = N(d5);
	const double Nd6 = N(d6);
	const double Nd7 = N(d7);
	const double Nd8 = N(d8);

	const double B_by_S0_one = pow((m_B / S0), (1 + 2 * r / (sigma * sigma)));
	const double B_by_S0_two = pow((m_B / S0), (-1 + 2 * r / (sigma * sigma)));

	return (S0 * (Nd1 - Nd3 - B_by_S0_one * (Nd6 - Nd8)) - m_K * exp(-r * m_T) * (Nd2 - Nd4 - B_by_S0_two * (Nd5 - Nd7)));

}