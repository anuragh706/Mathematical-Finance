#include "date.h"
#include"basic.h"
#include "basic.cpp"
#include<iostream>
#include "Calendar.h"
using namespace std;
Date::Date(unsigned int d=0,unsigned int m=0,unsigned int y=0) {
	
	// add an exception handling method here.
	m_serial = DMY_to_serial(d, m, y);
	//cout << m_serial << endl;
	
}
void Date::addDays(int days) {
	int int_m_serial = static_cast<int> (m_serial);
	int_m_serial = int_m_serial + days;
	m_serial = static_cast<int>(int_m_serial);

}
void Date::addMonths(int months) {

	unsigned int d, m, y;
	
	serial_to_DMY(m_serial, d, m, y);
	
	int user_month = static_cast<int> (m);
	int user_day = static_cast<int> (d);
	int user_year = static_cast<int> (y);
	
	// gets the new month using modulo operator and gets the month in the range of 1 to 12
	int new_month = (12 + ((user_month + months)% 12)-1) % 12 + 1;

	// calculates the effective change

	double frac = (user_month + months % 12)/12.0;
	
	//cout << "Frac:" << frac << endl;
	
	// see if the change in month results in the month beyond 12 or less than equal to 2 
	int years_toadd;
	if (months % 12 == 0) {
	
		years_toadd = 0;
	}
	else if (frac > 1) {
		years_toadd = 1;
	}
	else if (frac<=0)
	{
		years_toadd = -1;
	}
	else
	{
		years_toadd = 0;
	}

	int total_year_movement = int(months / 12.0) + years_toadd;	
	m_serial=DMY_to_serial(user_day, new_month, user_year + total_year_movement);
}

void Date::getDMY(unsigned int& d,unsigned int& m,unsigned int& y) {

	serial_to_DMY(m_serial, d, m, y);

}
void Date::addYears(int years) {
	unsigned int d, m, y;
	serial_to_DMY(m_serial, d, m, y);
	int user_year = static_cast<int>(y);
	int updated_year = user_year + years;
	m_serial = DMY_to_serial(d, m, static_cast<unsigned int>(updated_year));
}

int Date::dateDiff(Date dt) {

	unsigned int d, m, y;
	dt.getDMY(d, m, y);
	unsigned int m_serial_2 = DMY_to_serial(d, m, y);
	int difference = static_cast<int>(m_serial - m_serial_2);
	return abs(difference);
} 
int Date::weekday() {
	int m_serial_2 = static_cast<int>(m_serial);
	return (7 + ((m_serial_2) % 7) - 1) % 7 + 1;
}

bool Date::isGBD() {
	if (weekday() == 1 || weekday() == 7)
		return 0;
	else return 1;
}
void Date::rollToGBD() {

	if (isGBD()) return;
	else if (weekday() == 1) {
		m_serial++;
	}
	else if (weekday() == 7) {
		m_serial = m_serial + 2;
	}
}
void Date::addBusinessDays(unsigned int DaysToAdd) {
	rollToGBD();
	while (DaysToAdd) {

		m_serial = m_serial + 1;
		if (isGBD()) {
			DaysToAdd--;
		}
	}
}

void Date::operator++() {
	m_serial = m_serial + 1;
}
void Date::operator+(int days) {
	m_serial = m_serial + static_cast<unsigned int>(days);
}
bool Date::operator!=(Date d2) {
	
	unsigned int d, m, y;
	d2.getDMY(d, m, y);
	unsigned int m_serial_2=DMY_to_serial(d, m, y);

	if (m_serial == m_serial_2) return 0;
	else 1;
}

bool Date::isGBD(Calendar& c1) {
	if (weekday() == 1 || weekday() == 7 || c1.isHoliday((*this)))
		return 0;
	else return 1;
}

void Date::rollToGBD(Calendar& c1) {
	if (isGBD(c1)) return;
	while (!isGBD(c1)) {
		m_serial++;
	}
}
