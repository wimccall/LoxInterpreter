#include "AstPrinter.h"

AstPrinter::AstPrinter()
{
}


AstPrinter::~AstPrinter()
{
}

std::string AstPrinter::print(Expr<std::string>* expr) {
	return expr->accept(this);
}

std::string AstPrinter::parenthesize(std::string name, std::vector<Expr<std::string>*> exprs) {
	std::string ret;
	ret.append("(").append(name);

	for (int i = 0; i < exprs.size(); i++) {
		ret.append(" ");
		ret.append(exprs[i]->accept(this));
	}

	ret.append(")");

	return ret;
}

int main() {
	Expr<std::string>* expression = new Binary<std::string>(
		new Unary<std::string>(
			Token(MINUS, std::string("-"), new NilLiteral(), 1),
			new Literal<std::string>(new NumberLiteral(123))),
		Token(STAR, std::string("*"), new NilLiteral(), 1),
		new Grouping<std::string>(
			new Literal<std::string>(new NumberLiteral(45.67))));

	std::cout << AstPrinter().print(expression);
}