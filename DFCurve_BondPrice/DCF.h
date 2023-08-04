#pragma once
#include "interpolator.h"
#include "error.h"
class DiscountFactorCurve{
public:
	DiscountFactorCurve() {
		m_Li.insert(0.0, 1.0);
	}
	void insert(const double T, const double df);
	double getDF(const double T) const;
	
private:
	LinearInterpolator m_Li;
};
