#pragma once
#include "BSModel.h"
#include "stats.h"
#include "error.h"
#include <vector>
using namespace std;
struct Results {

	double Price;
	double error;

};
class Option {

public:
	Option(const double m_T_) :m_T(m_T_) {}
	Results PriceByMC(BSModel* Model, unsigned int N, unsigned int M, const double eps) const;

protected: 
	virtual double payoff(const vector <double>& S) const=0;
	virtual double payoff(const double & S) const = 0;
	const double m_T;
};