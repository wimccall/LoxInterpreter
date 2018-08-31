#include "DynamicTyping.h"

NilLiteral::NilLiteral()
{
};

NumberLiteral::NumberLiteral(double val) :
	value(val) {}

StringLiteral::StringLiteral(std::string val) :
	value(val) {}

std::string Object::getType() const {
	return type;
}