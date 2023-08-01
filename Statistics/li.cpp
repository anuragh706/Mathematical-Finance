#include "li.h"
#include<iostream>
using namespace std;

void LinearInterpolator::add(double x, double y) {
	m_data_points.insert({x,y});
	//cout << count << endl;
	count++;
}

double LinearInterpolator::value(double z) {

	if (count == 0) {
	
		cout << "No data points entered." << endl;
		exit;
	}
	int ctr = 0;
	map<double, double>::iterator it;

	double prev_first = m_data_points.begin()->first;
	double prev_second = m_data_points.begin()->second;
	double first_ele;
	double second_ele;

	if ((z <= m_data_points.begin()->first) || (count==1)) {
		cout << "Check : "<<m_data_points.begin()->first << endl;
		cout << z << endl;
		cout << (z <= m_data_points.begin()->first) << endl;
		cout << (m_data_points.size() == 1) << endl;
		return m_data_points.begin()->second;
	}
	else 
	{
		cout << "I'm in the else" << endl;
		for (it = m_data_points.begin(); it != m_data_points.end(); it++) {

			cout << ctr << endl;
			if (ctr == 0) 
			{
				ctr++;
				
				continue;
			}
			else
			{
				first_ele=it->first;
				second_ele = it->second;
				cout << "Second Ele" << second_ele << endl;
				if (z <= first_ele) {
				
					double slope = (second_ele - prev_second) / (first_ele - prev_first);

					
					return prev_second + slope * (z - prev_first);
				}
			
			}
			ctr++;
			prev_first = first_ele;
			prev_second = second_ele;
			cout << second_ele << endl;
		
		}
	
	}

	cout << ctr << endl;

	if (ctr == count) {

		return second_ele;
	}


}