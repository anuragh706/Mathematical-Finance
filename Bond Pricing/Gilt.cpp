#include "Gilt.h"
#include <iostream>
using namespace std;
double Gilt::cleanprice(Date settlement, double YTM) const
{

	return DirtyPrice(settlement, YTM) - AccruedInterest(settlement);

}
double Gilt::AccruedInterest(Date settlement) const {

	Date mat_date2=m_maturity;
	
	while (1) {
		mat_date2.addMonths(-6);
		if (mat_date2 < settlement) {
			break;
		}
	}

	Date prev_coupon_date = mat_date2;
	mat_date2.addMonths(6);
	Date next_coupon_date = mat_date2;

	double r = settlement.daysDiff(prev_coupon_date);
	double s = next_coupon_date.daysDiff(settlement);
	//cout << r << "\t" << s << endl;
	//cout << r / (r + s) * m_cpn / 2 << endl;
	return r / (r+s) * m_cpn / 2;
}
double Gilt::DirtyPrice(Date settlement,double YTM) const {
	Date mat_date2 = m_maturity;
	int n=0;

	while(true) 
	{
		mat_date2.addMonths(-6);
		if (mat_date2 < settlement) {
			break;
		}
		n++;
	}
	
	//cout << n << endl;
	Date prev_coupon_date = mat_date2;
	mat_date2.addMonths(6);
	Date next_coupon_date = mat_date2;

	double r = settlement.daysDiff(prev_coupon_date);
	double s = next_coupon_date.daysDiff(settlement);
	//cout << r <<"\t" << s << endl;
	int m = n + 1;
	double sum = 0;
	for (int i = 0; i <= n; i++) {

		sum += (m_cpn * 0.5) / pow(1 + YTM / 200, i);
		cout << sum << endl;
	}
	//cout << sum << endl;
	sum += 100.0 / (pow(1 + YTM / 200, n));
	//cout << (s / (r + s)) << endl;
	return sum / (pow(1 + YTM / 200, s / (r+s)));

}

double Gilt::getYTM(Date settlement, double clnPrice) const {

	double left = -0.05;
	double right = 6;
	double mid = (left + right) / 2;

	double func_mid = clnPrice - cleanprice(settlement, mid);
	double func_left = clnPrice - cleanprice(settlement, left);
	double func_right = clnPrice - cleanprice(settlement, right);
	double diff = 1.0;
	double epsilon = 0.000001;
	
	while (diff > epsilon) {
		if (func_left * func_mid < 0) {
			right = mid;
			func_right = clnPrice - cleanprice(settlement, right);
		}
		else {
			left = mid;
			func_left = clnPrice - cleanprice(settlement, left);
		}
		mid = (left + right) / 2;
		func_mid= clnPrice - cleanprice(settlement, mid);
		
		diff = abs(right - left);
		
	}

	return mid;


}