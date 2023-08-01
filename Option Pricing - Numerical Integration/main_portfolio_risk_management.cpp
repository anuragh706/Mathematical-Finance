#include <iostream>
#include <fstream>
#include<limits>
#include "EurCall.h"
#include "EurPut.h"
#include<vector>
#include<iomanip>
using namespace std;

struct TradeData {

	int OptionType;
	double strike, expiry, contracts;

};

struct all_portfolio {

	double price, delta, gamma, theta;

};
bool isDataCorrect(double value) {

	if (value < 0) {
		//cout << "Negative value entered.";
		return 0;
	}
	else return 1;
}

bool getTradeData(ifstream& file,vector<TradeData>& portfolio) {

	TradeData option;
	if (!file) {
		cout << "Trade Data file not available. Exitting!!";
		return 0;
	}
	
	string optiontype;
	while (!file.eof()) {

		file >> optiontype;
		if (optiontype == "C") option.OptionType = 1;
		else option.OptionType = -1;
		file >> option.contracts;
		file >> option.strike;
		file >> option.expiry;
		portfolio.push_back(option);
		
	}

	return 1;
}

void getMarketData(double& S0, double& sigma, double& r) {

	cout << "Enter Stock Price:";
	cin >> S0;
	cout << "Enter Volatility:";
	cin >> sigma;
	cout << "Enter Interest Rate:";
	cin >> r;

}
int main() {

	vector<TradeData> portfolio;
	vector<all_portfolio> prices;
	all_portfolio p1;
	enum Call_Put
	{
		Call = 1,
		Put = -1
	};
	double S0, sigma, r;
	
	
	
	ifstream file;

	file.open("TradeData.txt");
	if (!getTradeData(file, portfolio)) return 0;
	file.close();
	int total_trades = portfolio.size();
	vector<EurOption*> ptr;
	
	//ptr= new EurOption[total_trades];
	
	getMarketData(S0,sigma,r);
	//cout << std::numeric_limits<int>::max() << endl;

	//cout <<setfill(' ') << std::setw(20);
	cout<< " #####Portfolio Details#######" << endl;
	//cout << setfill('#') << left;
	cout <<setw(15)<<left<<"Option Type"<<setw(15)<<right<<"Contracts" << setw(15) << right<<"Strike Rate" << setw(15) << right<<"Expiry" << setw(15) << right<<"Price" << setw(15) << right<<"Delta" << setw(15) << right<<"Gamma" << setw(15) << right<<"Theta" << endl;
	cout << "===============================================================================================================" << endl;
	double sumprice=0.0, sumdelta=0.0, sumgamma=0.0, sumtheta = 0.0;
	for (int i = 0; i < total_trades; i++) {

		
		if (isDataCorrect(S0) && isDataCorrect(portfolio[i].strike) && isDataCorrect(portfolio[i].expiry) && isDataCorrect(sigma))
		{
			
			if (portfolio[i].OptionType==Call_Put::Call) {
				ptr.push_back(new EurCall(portfolio[i].expiry, portfolio[i].strike));
				//EurCall c1(portfolio[i].expiry, portfolio[i].strike);
				//ptr.push_back(&c1);
				
				cout << setw(15) <<left<< "Call";
			}
			else {
				ptr.push_back(new EurPut(portfolio[i].expiry, portfolio[i].strike));
				//EurPut p1(portfolio[i].expiry, portfolio[i].strike);
				//ptr.push_back(&p1);
				cout << setw(15) <<left<< "Put";
			}
			cout.precision(2);
			cout << fixed;
			cout << setw(15) << right << portfolio[i].contracts << setw(15) << right << portfolio[i].strike << setw(15) << right << portfolio[i].expiry;
			p1.price = ptr[i]->PriceByBSFormula(S0, sigma, r)* portfolio[i].contracts;// no need to store for now
			p1.delta = ptr[i]->DeltaByBSFormula(S0, sigma, r) * portfolio[i].contracts;
			p1.gamma = ptr[i]->GammaByBSFormula(S0, sigma, r)* portfolio[i].contracts;
			p1.theta = ptr[i]->ThetaByBSFormula(S0, sigma, r)* portfolio[i].contracts;
			sumprice += p1.price;
			sumdelta += p1.delta;
			sumgamma += p1.gamma;
			sumtheta += p1.theta;
			prices.push_back(p1);
			cout << setw(15) << right << prices[i].price << setw(15) << right << prices[i].delta << setw(15) << right << prices[i].gamma << setw(15) << right << prices[i].theta << endl;
			//cout << "	The Numerical Price of the option is:" << ptr[i]->PriceByNumericalIntergration(S0, sigma, r) << endl << endl;
		}
		else cout << "Please renter the data. Negative values entered.";

	}
	for (int i = 0; i < total_trades; i++) {
		delete ptr[i];
	}

	cout << setw(15) << left << "Total:" << setw(15) << right <<" "<< setw(15) << right<< " " << setw(15) << right<<" " << setw(15) << right<< setw(15) << right << setw(15) << right << setw(15) << right;
	cout << setw(15) << right << sumprice << setw(15) << right << sumdelta << setw(15) << right << sumgamma << setw(15) << right << sumtheta << endl;
	return 0;

}