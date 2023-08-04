#pragma once
#include "date.h"

class Gilt 
{
	public:
	Gilt(Date maturity, double coupon) : m_maturity(maturity), m_cpn(coupon) {};
	
	double cleanprice(Date settlement, double YTM) const;
	//double yield(Date settlement, double price);
	double DirtyPrice(Date settlement,double YTM) const;
	double AccruedInterest(Date settlement) const;
	double getYTM(Date settlement, double clnPrice) const;
	private:
		double m_cpn;
		Date m_maturity;
};
