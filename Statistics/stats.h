#pragma once
class stats1 
{

	public:
	void add(double);
	
	double mean();
	
	double stddev();
	stats1() : value(0.0), sum(0.0), sumsquared(0.0), count(0.0){};

	private:
	double value, sum, sumsquared, count;


};

class stats2
{
	public:
		void add(double, double);
		stats2() : value1(0.0), value2(0.0), product_sum(0.0), sumx_squared(0.0), sumy_squared(0.0), count(0.0), sumx(0.0), sumy(0.0) {};
		double covariance();
		double correlation();
		double slope();
		double intercept();

	private:
		double value1, value2, product_sum, sumx_squared, sumy_squared, count, sumx, sumy;

};