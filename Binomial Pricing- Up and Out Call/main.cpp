#include <iostream>
#include <vector>
#include <string>
#include "UpAndOutBarrierCall.h"
#include "ExoticOption.h"

using namespace std;

void BarrierOptionsDemo()
{
	//cout << "americanOptionsDemo()" << endl;

	const double K = 100.0;
	const double T = 1;

	const double S0 = 98.0;
	const double sigma = 0.2;
	const double r = 0.05;
	const int steps = 5500;
	const double B = 130;
	//cout << "Which type of option do you want to price? 1. Up and Out European Call." << endl;
	int response;
	//cin >> response;

	const ExoticOption* p = nullptr;	//	Non-const pointer to a const object
	//if (response == 1)
	p =  new UpandOutBarrierCall(K,T,B);

	const double price = p->binomialTreePrice(S0, sigma, r, steps);
	const double analytical_price = p->BSFormulaPrice(S0, sigma, r);
	cout << "Option price: " << price << endl;
	cout << "Analyical price: " << analytical_price << endl;

	delete p;

	return;
}

int main() {

	BarrierOptionsDemo();

}
/*
With N=1000, American put price: 7.87752
With N=10,000, American put price: 7.87596
*/