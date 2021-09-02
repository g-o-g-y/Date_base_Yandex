#include "node.h"

using namespace std;

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less && date < _date) {
		return true;
	}
	else if (_cmp == Comparison::LessOrEqual && date <= _date) {
		return true;
	}
	else if (_cmp == Comparison::Greater && _date < date) {
		return true;
	}
	else if (_cmp == Comparison::GreaterOrEqual && _date <= date) {
		return true;
	}
	else if (_cmp == Comparison::Equal && _date == date) {
		return true;
	}
	else if (_cmp == Comparison::NotEqual && !(_date == date)) {
		return true;
	}
	return false;
}
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less && event < _event) {
		return true;
	}
	else if (_cmp == Comparison::LessOrEqual && event <= _event) {
		return true;
	}
	else if (_cmp == Comparison::Greater && _event < event) {
		return true;
	}
	else if (_cmp == Comparison::GreaterOrEqual && _event <= event) {
		return true;
	}
	else if (_cmp == Comparison::Equal && _event == event) {
		return true;
	}
	else if (_cmp == Comparison::NotEqual && !(_event == event)) {
		return true;
	}
	return false;
}
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	if (_op == LogicalOperation::And)
		return _lhs->Evaluate(date, event) && _rhs->Evaluate(date, event);
	else 
		return _lhs->Evaluate(date, event) || _rhs->Evaluate(date, event);
}
bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}