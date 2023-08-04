#pragma once
#include <vector>
#include "normalRandomGenerator.h"
#include "stats.h"
#include <cstdlib>
using namespace std;

double Phi(double x);
int factorial(int n);
struct Results
{
	double price;
	double error;
	double delta;
};

class ExoticOption {

public:
	ExoticOption(double T, unsigned int m) : m_T(T), m_m(m) {}
	
protected:
	virtual double payoff(const double S) const = 0;
	const double m_T;
	const unsigned int m_m;
	const NormalRandomGenerator m_nrg;
};