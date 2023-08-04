#pragma once
#include "ExoticOption.h"
class RangeAccrual : public ExoticOption {

public:
	RangeAccrual(const double m_Smin_, const double m_Smax_, const double m_T_, const double m_Notional_) :ExoticOption(m_T_), m_Smax(m_Smax_), m_Smin(m_Smin_), m_Notional(m_Notional_) {}

private:
	const double m_Smin, m_Smax,m_Notional;
	double payoff(const vector<double>& S) const;
	double payoff(const double& S) const;

};