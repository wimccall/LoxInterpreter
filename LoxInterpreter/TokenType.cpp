#include "TokenType.h"
#include <string>

std::string tokenTypeToString(TokenType type) {
	switch (type) {
	case 0: return "LEFT_PAREN";
	case 1: return "RIGHT_PAREN";
	case 2: return "LEFT_BRACE";
	case 3: return "RIGHT_BRACE";
	case 4: return "COMMA";
	case 5: return "DOT";
	case 6: return "MINUS";
	case 7: return "PLUS";
	case 8: return "SEMICOLON";
	case 9: return "SLASH";
	case 10: return "STAR";
	case 11: return "BANG";
	case 12: return "BANG_EQUAL";
	case 13: return "EQUAL";
	case 14: return "EQUAL_EQUAL";
	case 15: return "GREATER";
	case 16: return "GREATER_EQUAL";
	case 17: return "LESS";
	case 18: return "LESS_EQUAL";
	case 19: return "IDENTIFIER";
	case 20: return "STRING";
	case 21: return "NUMBER";
	case 22: return "AND";
	case 23: return "CLASS";
	case 24: return "ELSE";
	case 25: return "FALSE";
	case 26: return "FUN";
	case 27: return "FOR";
	case 28: return "IF";
	case 29: return "NIL";
	case 30: return "OR";
	case 31: return "PRINT";
	case 32: return "RETURN";
	case 33: return "SUPER";
	case 34: return "THIS";
	case 35: return "TRUE";
	case 36: return "VAR";
	case 37: return "WHILE";
	case 38: return "END_OF_FILE";
	}
}