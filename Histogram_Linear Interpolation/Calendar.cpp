#include "Calendar.h"
#include "basic.h"
void Calendar::addHoliday(Date d1) {
	unsigned int d, m, y;
	d1.getDMY(d, m, y);
	unsigned int m_serial = DMY_to_serial(d, m, y);
	calendar.insert(m_serial);
}
bool Calendar::isHoliday(Date d1) {
	unsigned int d, m, y;
	d1.getDMY(d, m, y);
	unsigned int m_serial = DMY_to_serial(d, m, y);
	auto it = calendar.find(m_serial);
	if (it == calendar.end()) return 0;
	else return 1;
}