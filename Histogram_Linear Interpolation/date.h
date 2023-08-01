#pragma once
class Calendar ;
class Date {

	public:
		Date(unsigned int d,unsigned  int m,unsigned int y);

		void getDMY(unsigned int& d,unsigned int& m,unsigned int& y);
		void addDays(int);
		void addMonths(int);
		void addYears(int);
		int dateDiff(Date);
		int weekday();
		bool isGBD(Calendar&);
		void rollToGBD(Calendar&);
		bool isGBD();
		void rollToGBD();
		void addBusinessDays(unsigned int);
		void operator++();
		void operator+(int);
		bool operator!=(Date);
		enum Weekday {Sunday=1, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
	private:
		unsigned int m_serial;
};
