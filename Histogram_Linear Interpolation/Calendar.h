#pragma once
#include "Date.h"
#include<set>
using namespace std;
class Calendar {

	public:
		bool isHoliday(Date);
		void addHoliday(Date);
	private:
		set< int> calendar;
};
