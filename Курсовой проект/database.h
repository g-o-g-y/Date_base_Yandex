#pragma once
#include "date.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& cout) const;
	int RemoveIf(function<bool(const Date&, const string&)> f);
	vector<string> FindIf(function<bool(const Date&, const string&)> f) const;
	string Last(const Date& date) const;

private:
	map<Date, vector<string>> data;
	vector<pair<Date, string>> vector_data;
	set<pair<Date, string>> set_data;
};