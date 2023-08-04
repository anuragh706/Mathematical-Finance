#pragma once
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
class Function {

public:
	virtual double eval(double x) = 0;
};

void analysis(Function* f, vector<double> xvalues, ofstream& fout) {

	for (int i = 0; i < xvalues.size(); i++) {

		fout << setw(10) << xvalues[i] << "," <<setw(10)<< f->eval(xvalues[i]) << endl;
	}
}