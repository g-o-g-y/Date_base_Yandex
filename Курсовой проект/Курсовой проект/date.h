#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Date {
public:
	Date();
	Date(int y, int m, int d);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& stream, const Date& date);
string to_string(const Date& date);

unsigned int Getdate(stringstream& ss, const string& temp);

Date ParseDate(istream& is);