#pragma once
#include "date.h"

#include <memory>

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	Or,
	And,
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date)
		: _cmp(cmp)
		, _date(date)
	{}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _cmp;
	const Date _date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string event)
		: _cmp(cmp)
		, _event(event)
	{}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _cmp;
	const string _event;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& op, shared_ptr<Node> lhs, shared_ptr<Node> rhs)
		: _op(op)
		, _lhs(lhs)
		, _rhs(rhs)
	{}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const LogicalOperation _op;
	shared_ptr<const Node> _lhs, _rhs;
};
