#include "ChooserOption.h"
#include "Call.h"
#include "Put.h"

double ChooserOption::Payoff(double z) const {

	BSModel tempptr(z, ptr->getRate(), ptr->getSigma());
	Call c1(m_K, m_T-m_Tc, m_zl, m_zu);
	Put p1(m_K, m_T - m_Tc, m_zl, m_zu);
	return max(c1.PriceByBSFormula(&tempptr), p1.PriceByBSFormula(&tempptr)) ;
}

double ChooserOption::UpperBdCond(BSModel* PtrModel, double t) const {

	return m_zu - m_K * exp(-ptr->getRate() * (m_T - (m_Tc - t)));
}
double ChooserOption::LowerBdCond(BSModel* PtrModel, double t) const {

	return m_K * exp(-ptr->getRate() * (m_T - (m_Tc - t)));

}

double ChooserOption::PriceByBSFormula(BSModel* PtrModel) const {

	const double S0 = PtrModel->getStockPrice();
	const double r = PtrModel->getRate();
	const double sigma = PtrModel->getSigma();
	const double d = (log(S0 / m_K) + (r + 0.5 * pow(sigma, 2)) * m_T) / (sigma * sqrt(m_T));

	const double y = (log(S0 / m_K) + r * m_T + 0.5 * pow(sigma, 2) * m_Tc) / (sigma * sqrt(m_Tc));

	const double first_term=(S0 * PtrModel->N(d)-m_K*exp(-r*m_T)*PtrModel->N(d-sigma*sqrt(m_T)));
	const double second_term= (-S0 * PtrModel->N(-y) + m_K * exp(-r * m_T) * PtrModel->N(-y + sigma*sqrt(m_Tc)));

	return (first_term + second_term);
}