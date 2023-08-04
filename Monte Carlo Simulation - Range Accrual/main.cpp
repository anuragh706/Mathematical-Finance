#include "RangeAccrual.h"
#include <iostream>
#include "BSModel.h"
using namespace std;

int main() {

	const double S0 = 105, sigma = 0.25,r = 0.05, Smin=100, Smax=110, notional=1000000, T=1, eps=0.001;
	unsigned int D = 252, N=100000;
	BSModel Model(S0, sigma, r);

	RangeAccrual r1(Smin, Smax, T, notional);
	Results res;
	res = r1.PriceByMC(&Model, N, D, eps);
	cout<<res.Price<<endl;
	cout << res.error << endl;

	return 0;
}