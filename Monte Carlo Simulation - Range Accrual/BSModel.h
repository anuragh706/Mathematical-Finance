#pragma once
#include <vector>
#include "normalRandomGenerator.h"
using namespace std;
class BSModel {
public:
	BSModel(const double S0_, const double sigma_, const double r_) :m_S0(S0_), m_sigma(sigma_), m_r(r_) {}
	void GeneratePath(vector<double>& SamplePath, const double T, unsigned int M, const double eps) const;
	double getRate() const { return m_r; }
	double getSigma() const { return m_sigma; }
	double getStock() const { return m_S0; }
private:
	const double m_S0, m_sigma, m_r;
	NormalRandomGenerator m_nrg;
};