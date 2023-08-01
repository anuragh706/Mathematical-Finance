#include"stats.h"
#include<cmath>
#include<iostream>
using namespace std;

void stats1::add(double value)
{
	sum += value;
	count += 1;
	sumsquared += value * value;
}

double stats1::mean()
{
	return sum / count;
}

double stats1::stddev()
{
	double mean_sumsquared = sumsquared / count;
	double mean_squared = pow(sum / count,2);
	return pow(mean_sumsquared - mean_squared,0.5);

}

void stats2::add(double value1, double value2)
{
	product_sum += value1 * value2;
	sumx += value1;
	sumy += value2;
	sumx_squared += (value1 * value1);
	sumy_squared += (value2 * value2);
	count += 1;
}

double stats2::covariance()
{

	return product_sum / count - sumx * sumy / (count * count);


}


double stats2::correlation()
{
	double covariance = product_sum / count - sumx * sumy / (count * count);

	double mean_sumx_squared = sumx_squared / count;
	double mean_sumy_squared = sumy_squared / count;
	double mean_sumx = sumx / count;
	double mean_sumy = sumy / count;
	double stddevx = pow(mean_sumx_squared - mean_sumx * mean_sumx, 0.5);
	double stddevy = pow(mean_sumy_squared - mean_sumy * mean_sumy, 0.5);
	
	return covariance/(stddevx*stddevy);
}

double stats2::slope() 
{
	
	double cov = covariance();
	cout << "Covariance: " << cov << endl;
	double mean_sum_squared = sumx_squared / count;
	double sumx_mean_squared = sumx / count* sumx / count;
	double var_x = mean_sum_squared - sumx_mean_squared;
	//cout << "Standard Deviation: " << var_x << endl;
	return cov / var_x;
}

double stats2::intercept()
{
	double get_slope = slope();

	double y_mean = sumy / count;
	double x_mean = sumx / count;

	return y_mean - get_slope * x_mean;


}
