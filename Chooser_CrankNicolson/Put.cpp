#include "Put.h"
double Put::Payoff(double z) const {

	return (z > m_K ? 0.0 : (m_K - z));
}

double Put::UpperBdCond(BSModel* PtrModel, double t) const {

	return 0.0;

}
double Put::LowerBdCond(BSModel* PtrModel, double t) const {

	return m_K * exp(-PtrModel->getRate() * (m_T - t));

}
double Put::PriceByBSFormula(BSModel* PtrModel) const {
	const double d_plus= (log(PtrModel->getStockPrice() / m_K) +
		(PtrModel->getRate() + 0.5 * pow(PtrModel->getSigma(), 2.0)) * m_T)
		/ (PtrModel->getSigma() * sqrt(m_T));
	const double d_minus= d_plus - PtrModel->getSigma() * sqrt(m_T);
	return (m_K * exp(-PtrModel->getRate() * m_T) * PtrModel->N(-d_minus))
		- (PtrModel->getStockPrice() * PtrModel->N(-d_plus));
} 
