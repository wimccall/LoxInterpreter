#pragma once
#include "Expr.h"

class AstPrinter : public Visitor<std::string>
{
public:
	AstPrinter();
	~AstPrinter();
	std::string print(Expr<std::string>* expr);
	std::string parenthesize(std::string name, std::vector<Expr<std::string>*> exprs);
	std::string visitBinaryExpr(Binary<std::string>* expr) override {
		std::vector<Expr<std::string>*> e;
		e.push_back(expr->left);
		e.push_back(expr->right);
		return parenthesize(expr->op.lexeme, e);
	}
	std::string visitGroupingExpr(Grouping<std::string>* expr) override {
		std::vector<Expr<std::string>*> e;
		e.push_back(expr->expression);
		return parenthesize("group", e);
	}
	std::string visitLiteralExpr(Literal<std::string>* expr) override {
		return expr->value->toString();
	}
	std::string visitUnaryExpr(Unary<std::string>* expr) override {
		std::vector<Expr<std::string>*> e;
		e.push_back(expr->right);
		return parenthesize(expr->op.lexeme, e);
	}
};

