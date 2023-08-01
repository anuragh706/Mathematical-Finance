#include<iostream>
#include "stats.h"
#include"nrg.h"
#include<random>
using namespace std;

int main()
{

	double randnum;
	stats1 s;
	for (int i = 0; i < 100; i++)
	{
		randnum = double(rand());
		s.add(double(randnum) / RAND_MAX);
	
	
	}

	cout << "Mean of uniform random variable [0,1] is: " << s.mean()<<endl;

	cout << "Standard Deviation of uniform random variable is [0,1] is:" << s.stddev() << endl;

	stats2 s2;
	for (int i = 1; i < 100; i++)
	{
		s2.add(i,i*i);
		
	}

	cout << "Covariance is: " << s2.covariance() << endl;
	cout << "Correlation is:" << s2.correlation() << endl;

	stats2 s3;
	double x, y;

	for (int j = 0; j < 5; j++) {
		
		cin >> x;
		
		cin >> y;

		cout << endl;
		s3.add(x, y);
		
	
	}
	stats1 s4;
	NRG n1;
	cout << "Slope is: " << s3.slope() << endl;
	cout << "Intercept in: " << s3.intercept() << endl;

	double norm1;
	for (int j = 0; j < 100000; j++) {

		norm1 = n1.generate();

		s4.add(norm1);


	}

	cout << "Standard Normal Mean is: " << s4.mean()<<endl;
	cout << "Standard Normal StdDev is: " << s4.stddev() << endl;
	//cout << "Total Count is: "<<s4.count() << endl;


	return 0;



}