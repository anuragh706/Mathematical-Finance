#pragma once
#include<vector>
#include<map>
using namespace std;
class LinearInterpolator {

	
	public:
		void add(double,double);
		double value(double);
		LinearInterpolator() : count(0) {};

	private:

		map<double, double> m_data_points;
		//pair<vector<double>, vector<double>>  m_data_points;
		int count;
};