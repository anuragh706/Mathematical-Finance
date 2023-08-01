#include "Histogram.h"
#include "stats.h"
#include<iostream>
using namespace std;

void histogram::GetInfo(double a, double b, int c) {
	min_limit = a;
	max_limit = b;
	nBins = c;
	//bool check = exception_handling(min, max, nBins);
	interval_width = (max_limit - min_limit) / (nBins);
	m_histogram_data[min_limit] = 0;
	m_histogram_data[max_limit] = 0;
	double key = min_limit;
	for (int i = 0; i < (nBins+2); i++) {
		//cout << min << "\t";
		m_histogram_data[min_limit] = 0;
		min_limit = min_limit + interval_width;
	}
	size = m_histogram_data.size();
}
void histogram::add(double x) {
	
	map <double, int>::iterator it;
	for (it = m_histogram_data.begin(); it != m_histogram_data.end(); it++) {
	
		
		if (x < it->first) {
			//cout << x << endl;
			if (x >= max_limit) {
				
				//cout << "I'm in max" << endl;
				//cout << "Max limit: " << it->first << endl;
				//cout << "Max is" << max_limit;
				(it->second)++;
				break;
			}
			(it->second)++;
			break;
		}
	
	}
}
void histogram::GetOutput() {

	map <double, int>::iterator it;
	int ctr = 0;
	double prev_bound = m_histogram_data.begin()->first;
	for (it = m_histogram_data.begin(); it != m_histogram_data.end(); it++) {

		if (ctr == 0) {
			cout << "(-inf," << it->first << "):\t" << it->second<<endl;
				ctr++;
				prev_bound = it->first;
				continue;
		}
		else if (ctr == nBins+1) {
			cout << "[" << max_limit << ",inf):\t" << it->second << endl;
			break;
		}
		else {
			cout << "["<<prev_bound<<","<< it->first <<"):\t" << it->second << endl;
			ctr++;
			prev_bound = it->first;
		}
	}




}