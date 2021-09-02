#include "date.h"

#include <sstream>
#include <iomanip>

using namespace std;

Date::Date() {
	year = 0;
	month = 0;
	day = 0;
};
Date::Date(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}
int Date::GetYear() const {
	return year;
}
int Date::GetMonth() const {
	return month;
}
int Date::GetDay() const {
	return day;
}

Date ParseDate(istream& is) {
	unsigned int day, year, month;
	string temp;
	stringstream ss;
	is >> temp;
	ss << temp;
	year = Getdate(ss, temp);
	month = Getdate(ss, temp);
	day = Getdate(ss, temp);
	return Date(year, month, day);
}

unsigned int Getdate(stringstream& ss, const string& temp) {
	int date;
	string d;
	getline(ss, d, '-');
	for (const char i : d) {
		if (!isdigit(i)) {
			throw runtime_error(temp);
		}
	}
	date = atoi(d.c_str());
	return date;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		}
		else return lhs.GetMonth() < rhs.GetMonth();
	}
	else return lhs.GetYear() < rhs.GetYear();
}

bool operator==(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear() 
		&& lhs.GetMonth() == rhs.GetMonth()
		&& lhs.GetDay() == rhs.GetDay()) {
		return true;
	}
	else return false;
}

bool operator<=(const Date& lhs, const Date& rhs) {
	if (lhs < rhs || lhs == rhs) {
		return true;
	}
	else return false;
}

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.GetYear() << '-'
		<< setw(2) << setfill('0') << date.GetMonth() << '-'
		<< setw(2) << setfill('0') << date.GetDay();
	return stream;
}

string to_string(const Date& date) {
	stringstream ss;
	ss << setw(4) << setfill('0') << date.GetYear() << '-'
		<< setw(2) << setfill('0') << date.GetMonth() << '-'
		<< setw(2) << setfill('0') << date.GetDay();
	string out;
	ss >> out;
	return out;
}