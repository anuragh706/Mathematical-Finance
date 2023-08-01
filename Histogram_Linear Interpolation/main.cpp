#include<iostream>
#include"Histogram.h"
#include "nrg.h"
#include "date.h"
#include "nrg.cpp"
#include "Calendar.h"
using namespace std;

int main() {

	// How to check if the date is correct or not and not negative. what isf the day is more than 31.

	Date d1(6,2,2023);
	//Date d2(3, 2, 2023);
	//Date d3(7, 2, 2023);
	//Calendar c1;
	//c1.addHoliday(d1);
	//c1.addHoliday(d2);
	//c1.addHoliday(d3);
	//if (c1.isHoliday(d3)) cout << "Yes";
	//else cout << "No";
	//int months, days, years;
	
	unsigned int d, m, y;
	//d2.rollToGBD(c1);
	//d1.addYears(-5);
	
	//cout<<d1.dateDiff(d2);
	//cout << d1.weekday() << endl;
	//d1.addBusinessDays(17);
	//++d1;
	//if (d1 != d2)
//		cout << "Not Equal" << endl;
	//else cout << "Equal"<<endl;
	//d2.getDMY(d, m, y);

	//cout << "The date is:" << d << "/" << m << "/" << y << endl;
	
	int months;
	for (int i = 0; i < 10; i++) {
		
		cout << "Enter months to add:";
		cin >> months;
		d1.addMonths(months);
		d1.getDMY(d, m, y);
		cout <<"The date is:" << d << "/" << m << "/" << y << endl;
	}
	
	

	

	
	//d1.getDMY(d,m,y);
	

	
	return 0;


}