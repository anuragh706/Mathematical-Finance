#include <iostream>
#include "ExoticOption.h"
#include<cmath>
#include<vector>
using namespace std;

double ExoticOption::binomialTreePrice(double S0, double sigma, double r, int N) const
{
	const double delta = m_T / N;
	const double u = exp(sigma * sqrt(delta));
	const double d = 1.0 / u;
	const double R = exp(r * delta) - 1.0;
	
	const double qu = (1.0 + R - d) / (u - d);
	const double qd = 1.0 - qu;

	vector<double> v(N + 1);
	for (int i = 0; i <= N; ++i)
	{
		
		const double ST = S0 * pow(u, i) * pow(d, N - i);
		if (hasKnockedOut(ST)) v[i] = 0.0;
		else v[i] = payoff(ST);
	} 
	for (int n = N - 1; n >= 0; --n)
	{
		//if (n % 1000 == 0) cout << "Iteration No" << n << endl;
		for (int i = 0; i <= n; ++i)
		{
			

			v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
			const double S = S0 * pow(u, i) * pow(d, n - i);
			if (hasKnockedOut(S))
			{
					v[i] = 0.0;
			}
			
		}
	}
	return v[0];
}
