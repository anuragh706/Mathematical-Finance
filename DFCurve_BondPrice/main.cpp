#include <vector>
#include <iostream>
#include "DCF.h"
#include "InterestRateSwap.h"
using namespace std;

class Function {

public:
	virtual double eval(double x) const = 0;

};


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



// Adaptor to get the DF from a set of swap rates
class Adaptor : public Function {

public:
	Adaptor(InterestRateSwap* swap1, DiscountFactorCurve* df1): swap(swap1),dfc(df1){}
	double eval(double x) const {
		
		(dfc)->insert((swap)->getMaturity(), x);
		return swap->NPV(*dfc);
	}
private:
	InterestRateSwap* swap;
	DiscountFactorCurve* dfc;
};

class Adaptor2 : public Function {

public:
	Adaptor2(InterestRateSwap* swap1, DiscountFactorCurve* df1) : swap(swap1), dfc(df1) {}
	double eval(double x) const {

		swap->setSwapRate(x);
		return swap->NPV(*dfc);
	}
private:
	InterestRateSwap* swap;
	DiscountFactorCurve* dfc;
};



void Bootstrapper(vector<InterestRateSwap*>& SwapPortfolio, DiscountFactorCurve& f1 ) {
		
	for (unsigned int i = 0; i < SwapPortfolio.size(); i++) {
		
		Adaptor a1(SwapPortfolio[i],&f1);
		double rate = BisectionSolver(&a1, 0, 0.001, 1, 1e-7);
		f1.insert(SwapPortfolio[i]->getMaturity(), rate);
	}
	
	
}

int main() {
	
	
	int n;

	int maturity, frequency;
	double swap_rate;

	vector<InterestRateSwap*> SwapPortfolio(6);
	InterestRateSwap s1(1, 2, 0.0264);
	InterestRateSwap s2(2, 2, 0.0302);
	InterestRateSwap s3(3, 2, 0.0342);
	InterestRateSwap s4(5, 2, 0.0411);
	InterestRateSwap s5(7, 2, 0.0456);
	InterestRateSwap s6(10, 2, 0.0497);
	SwapPortfolio[0] = &s1;
	SwapPortfolio[1] = &s2;
	SwapPortfolio[2] = &s3;
	SwapPortfolio[3] = &s4;
	SwapPortfolio[4] = &s5;
	SwapPortfolio[5] = &s6;

	

	vector<double> tenors(6);
	tenors[0] = 1.0;
	tenors[1] = 2.0;
	tenors[2] = 3.0;
	tenors[3] = 5.0;
	tenors[4] = 7.0;
	tenors[5] = 10.0;
	DiscountFactorCurve f1;
	Bootstrapper(SwapPortfolio, f1);

	for (int i = 0; i < 6; i++) {
	
		cout << "Tenor: " << tenors[i] << "\t" << f1.getDF(tenors[i])<<endl;
	}
	
	InterestRateSwap swap1(1, 2, 0);
	cout << "1. Price of a zero coupon bond: " << 1+swap1.NPV(f1)<<endl;
	cout << "2. Continuously Compounded 2 year rate: " << -1.0/2*log(f1.getDF(tenors[1])) << endl;
	InterestRateSwap swap2(7, 2, 0.0442);
	cout << "3. Price of a 7 year swap : " << swap2.NPV(f1) << endl;
	InterestRateSwap swap3(9, 2, 0.0);
	Adaptor2 a3(&swap3, &f1);
	cout << "4. Par Rate of 9- year point : " << BisectionSolver(&a3, 0, 0.04, 0.05, 0.0000001) << endl;

	return 0;
}

/*

Tenor: 1        0.974113
Tenor: 2        0.941702
Tenor: 3        0.902773
Tenor: 5        0.813534
Tenor: 7        0.724025
Tenor: 10       0.601883
1. Price of a zero coupon bond: 0.974113
2. Continuously Compounded 2 year rate: 0.0300331
3. Price of a 7 year swap : -0.0084729
4. Par Rate of 9- year point : 0.0483085
*/