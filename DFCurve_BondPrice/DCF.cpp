#include "DCF.h"
void DiscountFactorCurve::insert(const double T, const double df) {
	m_Li.insert(T, df);
}
double DiscountFactorCurve::getDF(const double T) const {
	return m_Li.value(T);
}

