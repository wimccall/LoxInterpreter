#pragma once
#include <string>

class Object {
public:
	std::string getType() const;
	virtual std::string toString() const = 0;;

private:
	const std::string type;
};

class StringLiteral : public Object {
public:
	StringLiteral(std::string val);
	std::string getValue() const {
		return value;
	}
	std::string toString() const override {
		return value;
	}

private:
	const std::string type = "string";
	const std::string value;
};

class NumberLiteral : public Object {
public:
	NumberLiteral(double val);
	double getValue() const {
		return value;
	}
	std::string toString() const override {
		return std::to_string(value);
	}

private:
	const std::string type = "number";
	const double value;
};


class NilLiteral : public Object {
public:
	NilLiteral();
	std::string getValue() const {
		return "nil";
	}
	std::string toString() const override {
		return type;
	};

private:
	const std::string type = "nil";
};