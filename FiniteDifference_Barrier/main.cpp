#include <iostream>
#include <fstream>
#include "ExoticOption.h"
#include "UpAndOutBarrier.h"
#include <cmath>
using namespace std;

double FindNs(unsigned int left, unsigned int right, double threshold, double S0, double sigma, double r, int Nt, double analytical_price, double T, double B, double K) {
	if (abs(double(right-left)) <= 1) return left;
	unsigned int mid = static_cast<unsigned int>((left + double(right))/2.0);
	ExoticOption* p = nullptr;

	UpAndOutBarrier t1(T, B, K);
	//p = &t1;
	double numerical_price = t1.PriceByFiniteDifference(S0, sigma, r, Nt, mid);
	//double diff = abs(numerical_price/analytical_price-1);
	if (numerical_price != numerical_price) {
		return FindNs(left, mid, threshold, S0, sigma, r, Nt, analytical_price, T, B, K);
		cout << "Inf found.";
	}
	if (abs(numerical_price/analytical_price-1) < threshold)
		return FindNs(mid, right, threshold, S0, sigma, r, Nt, analytical_price, T, B, K);
	if (abs(numerical_price/analytical_price-1) >= threshold)
		return FindNs(left, mid, threshold, S0, sigma, r, Nt, analytical_price, T, B, K);
}


int main() {

	const double K = 100.0;
	const double T = 1;

	const double S0 = 98.0;
	const double sigma = 0.2;
	const double r = 0.05;
	const int steps = 5500;
	const double B = 130;
	 int Nt = 30000;
	 int Ns = 800;
	
	ExoticOption* p=nullptr;

	UpAndOutBarrier t1(T, B, K);
	p = &t1;

	cout << p->PriceByFiniteDifference(S0, sigma, r, Nt, Ns) << endl;
	const double analytical_price=p->BSFormulaPrice(S0, sigma, r);
	cout << analytical_price << endl;
	unsigned int left = 10;
	unsigned int right = 2500;
	const double threshold = 0.01;
	
	ofstream outputfile;
	outputfile.open("output.csv");
	if (!outputfile) return 0;
	else {
		outputfile << "Nt" << "," << "Ns" <<"," << "Ns_Square" << "," << "Nt_by_NsSquare" << "," << "Numerical Price" << "," << "Analytical Price" << endl;
		for (int i = 1; i < 2000; i += 50) {
			UpAndOutBarrier t1(T, B, K);
			//double optimal_Ns = FindNs(left, right, threshold, S0, sigma, r, Nt, analytical_price, T, B, K);
			int optimal_Ns= FindNs(left, right, threshold, S0, sigma, r, i, analytical_price, T, B, K);
			p = &t1;
			double numerical_price = p->PriceByFiniteDifference(S0, sigma, r, i, optimal_Ns);
			
			outputfile << i<<","<<optimal_Ns <<"," << optimal_Ns * optimal_Ns <<"," << optimal_Ns * optimal_Ns /i<<","<<numerical_price<<","<<analytical_price << endl;
			cout<<i<<"\t"<< optimal_Ns << endl;
		}
		outputfile.close();
	}
	

	return 0;
}