#include "EurCall.h"

double EurCall::payoff(const double S) const {

	return (S > m_K ? S - m_K : 0);
}

double EurCall::BSAnalyticalPrice(const double S0,const double sigma,const double r) const
{
	const double d_plus = (log(S0 / m_K) + (r + sigma * sigma / 2.0) * m_T) / sigma / sqrt(m_T);
	const double d_minus = d_plus - sigma * sqrt(m_T);
	return S0 * Phi(d_plus) - m_K * exp(-r * m_T) * Phi(d_minus);
}

double EurCall::BSAnalyticalJumpDiffusionPrice(double S0, double sigma, double r,double lambda, double m, double s) const {
	const double k = exp(m + s * s / 2) - 1;
	const double lambda_dash = lambda * (1 + k);
	const unsigned int N = 16;
	double sum = 0;
	for (int i = 0; i < N; i++) {

		EurCall c1(m_K, m_T, m_m);

		const double sigma_n = sqrt(sigma * sigma + i * s * s / m_T);
		const double r_n = r - lambda * k + i * log(1 + k) / m_T;
		const double pr = c1.BSAnalyticalPrice(S0, sigma_n, r_n);
		sum += exp(-lambda_dash * m_T) * pow(lambda_dash * m_T, i) / factorial(i)*pr;
	}

	return sum;
}


Results EurCall::MonteCarloPriceHeston(double S0, double r, unsigned int N, double var_mean, double var0, double eta, double rho, double a) const
{
	const double dt = m_T / m_m;

	Stats1 s;
	for (unsigned int i = 0; i < N; ++i)
	{
		vector<double> S(m_m + 1);
		S[0] = S0;
		vector<double> var(m_m + 1);
		var[0] = var0;
		for (unsigned int j = 1; j <= m_m; ++j)
		{

			const double eps1 = m_nrg.generate();
			const double eps2 = m_nrg.generate();
			const double z1 = eps1;
			const double z2 = rho * eps1 + sqrt(1 - rho * rho) * eps2;
			const double drift = (r - var[j - 1] / 2) * dt;
			const double diff = sqrt(var[j - 1] * dt) * z1;
			S[j] = S[j - 1] * exp(drift + diff);
			var[j] = pow(sqrt(var[j - 1]) + eta / 2.0 * sqrt(dt) * z2, 2) - a * (var[j - 1] - var_mean) * dt - eta * eta / 4.0 * dt;
		}
		s.add(payoff(S[m_m]));
	}
	Results results;
	results.price = exp(-r * m_T) * s.mean();
	results.error = exp(-r * m_T) * s.stdevP() / sqrt(N - 1);
	return results;
}

Results EurCall::MonteCarloPriceJumpDiffusion(double S0, double sigma, double r, double lambda, double m, double s, unsigned int N) const
{
	const double dt = m_T / m_m;
	const double drift = (r - sigma * sigma / 2 - lambda * (exp(m + s * s / 2) - 1))*dt;
	Results results;


		Stats1 S1;
		for (unsigned int i = 0; i < N; ++i)
		{
			vector<double> S(m_m + 1);
			S[0] = S0;


			for (unsigned int j = 1; j <= m_m; ++j)
			{

				const double z1 = m_nrg.generate();

				const double diff = sigma * sqrt(dt) * z1;

				const double randnum = static_cast<double>(rand()) / RAND_MAX;
				if (randnum <= lambda * dt) {

					const double z2 = m_nrg.generate();
					const double jump = exp(s * z2 + m);
					S[j] = S[j - 1] * exp(drift + diff) * jump;
				}
				else {

					S[j] = S[j - 1] * exp(drift + diff);
				}


			}
			S1.add(payoff(S[m_m]));
		}

		Results rs2;
		rs2.price = exp(-r * m_T) * S1.mean();
		rs2.error = exp(-r * m_T) * S1.stdevP() / sqrt(N - 1);
		//error_value = rs2.error / rs2.price;
		//cout << num_paths << endl;
		//cout << rs2.price << endl;
		//cout << error_value << endl;
		//num_paths += 500000;
		
		
		return rs2;
	
	
}
