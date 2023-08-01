#pragma once
#include <map>
using namespace std;
class histogram
{
	public:
		void GetInfo(double, double, int);
		void add(double);
		bool exception_handling(double, double, int);
		void GetOutput();
		histogram() :min_limit(0.0),max_limit(0.0),nBins(0), interval_width(0.0),size(0) {};
	private:

		double min_limit, max_limit, interval_width;
		int nBins,size;
		map <double, int> m_histogram_data;


};
