#include <iostream>
#include<limits>
#include "EurCall.h"
#include "EurPut.h"
using namespace std;
bool isDataCorrect(double value) {
	
	if (value < 0) {
			//cout << "Negative value entered.";
			return 0;		
	}
	else return 1;
}
void getTradeData(double& K, double& T, int& CP, double& S0, double& sigma, double& r) {

	cout << "############Enter the Trade Data##########" << endl;
	cout << "	Enter Strike Price: ";
	cin >> K;
	cout << "	Enter Time to Maturity: ";
	cin >> T;
	cout << "	Enter Call[1] or Put[-1] ";
	cin >> CP;

	cout << "Enter the Market Data:" << endl;
	cout << "	Enter Share Price: ";
	cin >> S0;
	cout << "	Enter volatility: ";
	cin >> sigma;

	cout << "	Enter Interest Rate: ";
	cin >> r;

}
int main() {

	const int total_options = 4;
	enum Call_Put
	{
		Call = 1,
		Put = -1
	};
	double S0, sigma, r, T, K;
	int CP;
	EurOption* ptr[total_options];
	
	//cout << std::numeric_limits<int>::max() << endl;
	for (int i = 0; i < total_options; i++) {
		
		getTradeData(K, T, CP, S0, sigma, r);
		if (isDataCorrect(S0) && isDataCorrect(T) && isDataCorrect(T) && isDataCorrect(sigma))
		{

			if (CP == Call_Put::Call) {
				EurCall c1(T,K);
				ptr[i] = &c1;
			}
			else {
				EurPut p1(T, K);
				ptr[i] = &p1;
			
			}
				
			cout << "	The Price of the option is:" << ptr[i]->PriceByBSFormula(S0, sigma, r) << endl;
			cout << "	The Delta of the option is:" << ptr[i]->DeltaByBSFormula(S0, sigma, r) << endl;
			cout << "	The Gamma of the option is:" << ptr[i]->GammaByBSFormula(S0, sigma, r) << endl;
			cout << "	The Theta of the option is:" << ptr[i]->ThetaByBSFormula(S0, sigma, r) << endl<<endl;
			cout << "	The Numerical Price of the option is:" << ptr[i]->PriceByNumericalIntergration(S0, sigma, r) << endl << endl;
		}
		else cout << "Please renter the data. Negative values entered.";
	}
	return 0;

}