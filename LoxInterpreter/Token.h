#pragma once
#include "TokenType.h"
#include "DynamicTyping.h"
#include <string>

class Token
{
public:
	Token(TokenType type, std::string lexeme, Object literal, int line);
	~Token();
	std::string toString();

	const TokenType type;
	const std::string lexeme;
	const int line;
	const Object literal;
};

