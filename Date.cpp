#include "Date.h"

Date::Date(int day, int month, int year)
	: m_day(day), m_month(month), m_year(year)
{
}

Date::Date(const std::string& str)
{
	//get year
	size_t pos1 = 0;
	size_t pos2 = str.find('-', pos1);
	m_year = stoi(str.substr(pos1, pos2 - pos1));

	//get month
	pos1 = pos2 + 1;
	pos2 = str.find('-', pos1);
	m_month = stoi(str.substr(pos1, pos2 - pos1));

	//get day
	pos1 = pos2 + 1;
	m_day = stoi(str.substr(pos1));
}

void Date::setDay(int day)
{
	m_day = day;
}

void Date::setMonth(int month)
{
	m_month = month;
}

void Date::setYear(int year)
{
	m_year = year;
}

int Date::getDay() const
{
	return m_day;
}

int Date::getMonth() const
{
	return m_month;
}

int Date::getYear() const
{
	return m_year;
}

std::string Date::toString() const
{
	//get month part
	std::string monthS = std::to_string(m_month);
	//add 0 at the beginning if the number is one-digit
	if (monthS.size() == 1) monthS.insert(0, 1, '0'); 

	//get day part
	std::string dayS = std::to_string(m_day);
	//add 0 at the beginning if the number is one-digit
	if (dayS.size() == 1) dayS.insert(0, 1, '0');

	//get year part
	std::string yearS = std::to_string(m_year);
	
	//put the parts together
	return yearS + "-" + monthS + "-" + dayS;
}

bool Date::operator==(const Date& date2) const
{
	return (m_year == date2.m_year && m_month == date2.m_month && m_day == date2.m_day);
}

bool Date::operator<(const Date& date2) const
{
	if (m_year < date2.m_year)
	{
		return true;
	}
	else if (m_year == date2.m_year)
	{
		if (m_month < date2.m_month)
		{
			return true;
		}
		else if (m_month == date2.m_month)
		{
			if (m_day < date2.m_day)
			{
				return true;
			}
		}
	}

	return false;
}

bool Date::operator>(const Date& date2) const
{
	if (m_year > date2.m_year)
	{
		return true;
	}
	else if (m_year == date2.m_year)
	{
		if (m_month > date2.m_month)
		{
			return true;
		}
		else if (m_month == date2.m_month)
		{
			if (m_day > date2.m_day)
			{
				return true;
			}
		}
	}

	return false;
}

bool Date::operator<=(const Date& date2) const
{
	return *this < date2 || *this == date2;
}

bool Date::operator>=(const Date& date2) const
{
	return *this > date2 || *this == date2;
}
