#include "pch.h"
#include "Token.h"


Token::Token(TokenType _type, std::string _lexeme, Object _literal, int _line):
	lexeme(_lexeme),
	type(_type),
	literal(_literal),
	line(_line)
{}

Token::~Token()
{
}

std::string Token::toString() {
	return tokenTypeToString(type) + " " + lexeme + " " + literal.toString();
}