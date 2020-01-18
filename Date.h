#pragma once

#include <string>

//class representing a date
class Date
{
private:

	int m_day;
	int m_month;
	int m_year;

public:

	explicit Date(int day = 0, int month = 0, int year = 0);

	//constructs a date from a string format (YYYY-MM-DD)
	explicit Date(const std::string& str);

	void setDay(int day);

	void setMonth(int month);

	void setYear(int year);

	int getDay() const;

	int getMonth() const;

	int getYear() const;

	//converts this date to a string format (YYYY-MM-DD)
	std::string toString() const;

	//comparison operators for the Date class, used for sorting and searching

	bool operator==(const Date& date2) const;

	bool operator<(const Date& date2) const;

	bool operator>(const Date& date2) const;

	bool operator<=(const Date& date2) const;

	bool operator>=(const Date& date2) const;
};


