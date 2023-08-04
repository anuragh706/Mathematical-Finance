#include "InterestRateSwap.h"

double InterestRateSwap::NPV(const DiscountFactorCurve& df) const {

	int no_of_periods = m_maturity * m_frequency;
	double fixed_leg_sum = 0.0;
	for (int i = 0; i < no_of_periods; i++) {
		fixed_leg_sum += df.getDF(static_cast<double>((i + 1))/m_frequency);
	}
	double float_leg_sum = 1 - df.getDF(m_maturity);
	return (fixed_leg_sum*m_swap_rate/m_frequency - float_leg_sum);
}