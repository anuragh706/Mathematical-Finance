#include<cmath>
#include<random>
#include"nrg.h"
#include<iostream>
using namespace std;
const double pi=22.0/7;
double NRG::generate() {

	if (flag == 0) {
		
		double uni_rand1 = double(rand()) / RAND_MAX;
		double uni_rand2 = double(rand()) / RAND_MAX;
		norm_rand1= pow(-2.0 * log(uni_rand1), 0.5) * cos(2 * pi * uni_rand2);
		norm_rand2= pow(-2.0 * log(uni_rand1), 0.5) * sin(2 * pi * uni_rand2);
		count += 1;
		flag = 1;
		return norm_rand1;
	
	}
	else {
		flag = 0;
		return norm_rand2;

	
	}

	


}
