#include "ExoticOption.h"
#include <vector>
using namespace std;
double ExoticOption::PriceByFiniteDifference(const double S0, const double sigma, const double r, const unsigned int Nt, const unsigned int Ns) const {
	
	const double S_max = getSmax();
	const double S_min = 0;
	const double dS = (S_max - S_min) / Ns;
	const double dt = m_T / Nt;

	double ST = S_min;
	vector<double> v(Ns + 1);
	for (int j = 0; j <= Ns; ++j)
	{
		v[j] = payoff(ST);
		
		if (hasBreached(ST))
			v[j] = 0.0;
		ST += dS;	
	}

	double t = m_T;
	for (int i = Nt; i > 0; --i)
	{
		vector<double> u(Ns + 1);
		double S = S_min;
		for (int j = 1; j < Ns; ++j)
		{
			S += dS;
			const double a = -sigma * sigma * S * S / 2.0;
			const double b = -r * S;
			const double c = r;

			const double A = dt / dS * (b / 2.0 - a / dS);
			const double B = 1.0 - dt * c + 2.0 * dt * a / dS / dS;
			const double C = -dt / dS * (b / 2.0 + a / dS);

			u[j] = A * v[j - 1] + B * v[j] + C * v[j + 1];
			
			if (hasBreached(S)) u[j] = 0.0;

		}

		t -= dt;

		applyBoundaryConditions(u[0], u[Ns],r,t);
		
		v = u;
	}

	//
	//	Linearly interpolate since S0 may not
	//	correspond to a gridpoint.
	//
	const int left = floor(S0 - S_min) / dS;
	const double w = (S0 - (S_min + left * dS)) / dS;
	const double price = v[left] * (1.0 - w) + v[left + 1] * w;

	return price;
	
}