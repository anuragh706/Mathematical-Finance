#pragma once
#include "DCF.h"
class InterestRateSwap {

public:
	InterestRateSwap() :m_swap_rate(0), m_maturity(0), m_frequency(0) {}
	InterestRateSwap(int mat, int freq, double swap) :m_swap_rate(swap), m_maturity(mat), m_frequency(freq) {}

	double NPV(const DiscountFactorCurve& df) const;
	int getMaturity() { return m_maturity; }
	void setSwapRate(double s) { m_swap_rate = s; }
private:
	const int m_maturity, m_frequency;
	double m_swap_rate;

};