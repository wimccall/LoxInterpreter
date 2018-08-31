#include "pch.h"
#include "Scanner.h"
#include "Lox.h"

Scanner::Scanner(std::string _source) :
source(_source)
{
	keywords[std::string("and")] = AND;
	keywords[std::string("class")] = CLASS;
	keywords[std::string("else")] = ELSE;
	keywords[std::string("false")] = FALSE;
	keywords[std::string("for")] = FOR;
	keywords[std::string("fun")] = FUN;
	keywords[std::string("if")] = IF;
	keywords[std::string("nil")] = NIL;
	keywords[std::string("or")] = OR;
	keywords[std::string("print")] = PRINT;
	keywords[std::string("return")] = RETURN;
	keywords[std::string("super")] = SUPER;
	keywords[std::string("this")] = THIS;
	keywords[std::string("true")] = TRUE;
	keywords[std::string("var")] = VAR;
	keywords[std::string("while")] = WHILE;
}


Scanner::~Scanner()
{
}

std::vector<Token> Scanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	tokens.push_back(Token(END_OF_FILE, std::string(""), NilLiteral(), line));
	return tokens;
}

bool Scanner::isAtEnd() {
	return current >= source.length();
}

bool Scanner::isDigit(char c) {
	return isdigit(c);
}

bool Scanner::isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		   (c >= 'A' && c <= 'Z') ||
		   c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
	return isAlpha(c) || isDigit(c);
}

void Scanner::scanToken() {
	char c = advance();
	switch (c) {
		case '(': addToken(LEFT_PAREN); break;
		case ')': addToken(RIGHT_PAREN); break;
		case '{': addToken(LEFT_BRACE); break;
		case '}': addToken(RIGHT_BRACE); break;
		case ',': addToken(COMMA); break;
		case '.': addToken(DOT); break;
		case '-': addToken(MINUS); break;
		case '+': addToken(PLUS); break;
		case ';': addToken(SEMICOLON); break;
		case '*': addToken(STAR); break;
		case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
		case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
		case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
		case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
		case '/':
			if (match('*')) {
				while (true) {
					while (!match('*')) {
						advance();
					}
					if (match('/')) break;
				}
			} else if (match('/')) {
				// A comment goes until the end of the line.                
				while ((peek() != '\n') && (!isAtEnd())) advance();
			} else {
				addToken(SLASH);
			}
			break;
		// Ignore whitespace.      
		case ' ':
		case '\r':
		case '\t':                
			break;
		case '\n':
			line++;
			break;
		case '"': string(); break;
		default:
			if (isDigit(c)) {
				number();
			}
			else if (isAlpha(c)) {
				identifier();
			}
			else {
				Lox::error(line, "Unexpected character.");
			}
			break;
	}
}


char Scanner::advance() {
	current++;
	return source.at(current - 1);
}

void Scanner::addToken(TokenType type) {
	addToken(type, NilLiteral());
}

void Scanner::addToken(TokenType type, Object literal) {
	std::string text = source.substr(start, (current- start));
	tokens.push_back(Token(type, text, literal, line));
}

// consumes the character and returns true if it matches. Otherwise doesn't consume the character and returns false.
bool Scanner::match(char expected) {
	if (isAtEnd()) return false;
	if (source.at(current) != expected) return false;

	current++;
	return true;
}

char Scanner::peek() {
	if (isAtEnd()) return '\0';
	return source.at(current);
}

char Scanner::peekNext() {
	if (current + 1 >= source.length()) return '\0';
	return source.at(current + 1);
}

void Scanner::string() {
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') line++;
		advance();
	}

	// Unterminated string.
	if (isAtEnd()) {
		Lox::error(line, "Unterminated string.");
		return;
	}

	// Consume the closing "
	advance();

	// Trim the surrounding quotes
	std::string value = source.substr(start + 1, current - 1);
	addToken(STRING, StringLiteral(value));
}


void Scanner::number() {
	while (isDigit(peek())) advance();

	// Look for a fractional part.                            
	if (peek() == '.' && isDigit(peekNext())) {
		// Consume the "."                                      
		advance();

		while (isDigit(peek())) advance();
	}

	addToken(NUMBER, NumberLiteral(std::stod(source.substr(start, current))));
}

void Scanner::identifier() {
	while (isAlphaNumeric(peek())) advance();

	// See if the identifier is a reserved word.   
	std::string text = source.substr(start, (current - start));

	std::map<std::string, TokenType>::const_iterator i = keywords.find(text);

	TokenType type;
	if (i == keywords.end()) {
		type = IDENTIFIER;
	} else {
		type = keywords[text];
	}
	addToken(type);
}