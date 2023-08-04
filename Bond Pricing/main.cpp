#include <iostream>
#include "date.h"
#include "Gilt.h"
using namespace std;

int main() {

	const Date maturity(7, 9, 2039);
	double cpn = 4.25;
	const Gilt g(maturity, cpn);
	const Date settlement(12, 12, 2013);
	//cout << g.cleanprice(settlement, 4)<<endl;
	cout << g.DirtyPrice(settlement, 4)<<endl;

	const Date settlement2(12, 12, 2013);
	//const double clnprice = 111.95;
	//cout<<"Yield is: "<<g.getYTM(settlement, clnprice) << endl;

	return 0;
}