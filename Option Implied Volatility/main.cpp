#include <iostream>
#include "EurCall.h"
#include "Adaptor.h"
#include"Function.h"
using namespace std;


double BisectionSolver(const Function* f, double c, double left, double right, double acc)
{
	double fl = f->eval(left);
	double fr = f->eval(right);

	while (true)
	{
		const double mid = (left + right) / 2.0;
		if (right - left <= acc)
			return mid;
		const double fm = f->eval(mid);
		if (fl <= c && c <= fm || fm <= c && c <= fl)
		{
			right = mid;
			fr = fm;
		}
		else
		{
			left = mid;
			fl = fm;
		}
	}

	return 0.0;
}

int main() {

	const double K = 105.0;
	const double T = 1;
	const unsigned int m = 365;
	const EurCall opt(K, T, m);

	const double S0 = 100.0;
	const double sigma = 0.25;
	const double r = 0.05;
	const double var0 = 0.2 * 0.2;
	const double var_mean = 0.3 * 0.3;
	const double a = 1.25;
	const double eta = 0.3;
	const double rho = 0.1;
	const unsigned int N = 1'000'0;
	const double lambda = 1;
	const double jump_mean = 0.05;
	const double jump_sigma = 0.3;
	const double T2 = 0.5;
	const double sigma2 = 0.15;

	
	const Results results = opt.MonteCarloPriceHeston(S0, r, N,var_mean,var0,eta,rho,a);

	cout << "MC Heston price: " << results.price << endl;
	cout << "MC error: " << results.error << endl;
	
	const Adaptor ad(&opt,S0, r);
	cout << "BS Analytical Price"<<opt.BSAnalyticalPrice(S0, sigma, r) << endl;
	const double implied_vol = BisectionSolver(&ad, results.price, 0.1, 0.3, 0.0001);
	cout << "Implied vol is:" << implied_vol << endl;
	
	const EurCall opt2(K, T2, m);
	cout << "Jump diffusion analytical price:"<<opt2.BSAnalyticalJumpDiffusionPrice(S0, sigma2, r, lambda, jump_mean, jump_sigma) << endl;
	
	const unsigned int N2 = 100000;
	Results rs1 = opt2.MonteCarloPriceJumpDiffusion(S0, sigma2, r, lambda, jump_mean, jump_sigma, N2);
	cout << "Jump diffusion Monte Carlo price:" << rs1.price << endl;
	cout << "Standard Error of Jump diffusion Monte Carlo price is:" << rs1.error << endl;
	//cout << N2 * pow(rs1.error / (.001 * rs1.price), 2) << endl;
	return 0;



}

/*
MC price Heston: 9.71542
MC error: 0.0556158
Implied vol is:0.242725
Jump diffusion analytical price:7.75294

*/