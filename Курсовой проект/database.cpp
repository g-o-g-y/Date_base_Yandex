#include "database.h"

#include <queue>

using namespace std;

void Database::Add(const Date& date, const string& event) {
	size_t size = set_data.size();
	set_data.insert({date, event});
	if (set_data.size() == size) {
		return;
	}
	/*if (data.count(date) != 0)
		if (find(data.at(date).begin(), data.at(date).end(), event) != data.at(date).end())
			return;*/
	data[date].push_back(event);
}
void Database::Print(ostream& out) const {
	for (const pair<Date, vector<string>>& date : data) {
		for (const string& str : date.second) {
			out << date.first;
			out << " ";
			out << str;
			out << endl;
		}
	}
}
int Database::RemoveIf(function<bool(const Date&, const string&)> f) {
	int counter = 0, c = 0;
	/*auto ParseEvent = [](istream& is) {
		string event;
		is >> ws;
		getline(is, event);
		return event;
	};
	map<Date, vector<string>> deleting_data;
	for (auto i : set_data) {
		istringstream ss(i);
		Date date = ParseDate(ss);
		string event = ParseEvent(ss);
		if (f(date, event)) {
			counter++;
			set_data.erase(to_string(date) + " " + event);
			deleting_data[date].push_back(event);
		}
	}*/

	queue<Date> data_queue;
	set_data.clear();
	for (pair<const Date, vector<string>>& date : data) {
		vector<string>::iterator end = date.second.end();
		vector<string>::iterator it = stable_partition(date.second.begin(), date.second.end(), [f, date](string& event) {
			return !f(date.first, event);
		});
		counter += (end - it);
		date.second = { date.second.begin() , it };
		if (date.second.size() == 0) {
			data_queue.push(date.first);
			c++;
		}
		for (const string& i : date.second) {
			set_data.insert({ date.first, i });
		}
	}
	for (int i = 0; i < c; ++i) {
		data.erase(data_queue.front());
		data_queue.pop();
	}


	/*queue<Date> data_queue;
	for (pair<const Date, vector<string>>& date : data) {
		vector<pair<string, bool>> temp;
		for (const string& st : date.second)
			temp.push_back({ st, true });
		auto it = temp.begin();
		while (it != temp.end()) {
			if (f(date.first, (*it).first)) {
				(*it).second = false;
				counter++;
			}
			++it;
		}
		it = stable_partition(temp.begin(), temp.end(), [](const pair<string,bool>& a) {
			return a.second;
		});
		date.second.clear();
		for (auto i = temp.begin(); i != it; ++i)
			date.second.push_back((*i).first);
		if (date.second.size() == 0) {
			data_queue.push(date.first);
			c++;
		}
	}
	for (int i = 0; i < c; ++i) {
		data.erase(data_queue.front());
		data_queue.pop();
	}*/
	/*for (pair<const Date, vector<string>>& date : data) {
		queue<unsigned> queue;
		unsigned temp = 0, k = 0;
		auto it = date.second.begin();
		while (it != date.second.end()) {
			if (f(date.first, *it)) {
				queue.push(temp + k);
				k += temp;
				temp = 0u;
				counter++;
			}
			else temp++;
			++it;
		}
		
		while (queue.size() != 0) {
			date.second.erase(date.second.begin() + queue.front());
			queue.pop();
		}
		if (date.second.size() == 0) {
			data_queue.push(date.first);
			c++;
		}
	}
	for (int i = 0; i < c; ++i) {
		data.erase(data_queue.front());
		data_queue.pop();
	}*/
	return counter;
}
vector<string> Database::FindIf(function<bool(const Date&, const string&)> f) const {
	vector<string> out;
	for (const pair<Date, vector<string>>& date : data) {
		for (const string& str : date.second) {
			if (f(date.first, str))
				out.push_back(to_string(date.first) + " " + str);
		}
	}
	return out;
}
string Database::Last(const Date& date) const {
	auto it = data.upper_bound(date);
	if (it == data.begin())
		throw invalid_argument("No entries");
		--it;
	const vector<string> events = (*it).second;
	return to_string((*it).first) + " " + events.back();
}