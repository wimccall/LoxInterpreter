#pragma once
#include <string>
#include <vector>
#include <map>
#include "Token.h"

class Scanner
{
public:
	Scanner(std::string source);
	std::vector<Token> scanTokens();
	~Scanner();

private:
	bool isAtEnd();
	bool isDigit(char c);
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	void scanToken();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType, Object* literal);
	bool match(char expected);
	char peek();
	char peekNext();
	void string();
	void number();
	void identifier();

	const std::string source;
	std::vector<Token> tokens;
	int start = 0;
	int current = 0;
	int line = 1;
	std::map<std::string, TokenType> keywords;
};

