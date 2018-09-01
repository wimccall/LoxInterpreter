#include <vector>
#include <iostream>
#include "Token.h"
template <class T>
class Visitor;
template <class T>
class Expr {
public:
   virtual T accept(Visitor<T> *visitor) = 0;
};

template <class T>
class Binary : public Expr<T> {
public:
   Binary(Expr<T>* left, Token op, Expr<T>* right):
      left(left),
      op(op),
      right(right)
      {}


   T accept(Visitor<T> *visitor) {
      return visitor->visitBinaryExpr(this);
   }
   Expr<T>* left;
   Token op;
   Expr<T>* right;
};
template <class T>
class Grouping : public Expr<T> {
public:
   Grouping(Expr<T>* expression):
      expression(expression)
      {}


   T accept(Visitor<T> *visitor) {
      return visitor->visitGroupingExpr(this);
   }
   Expr<T>* expression;
};
template <class T>
class Literal : public Expr<T> {
public:
   Literal(Object* value):
      value(value)
      {}


   T accept(Visitor<T> *visitor) {
      return visitor->visitLiteralExpr(this);
   }
   Object* value;
};
template <class T>
class Unary : public Expr<T> {
public:
   Unary(Token op, Expr<T>* right):
      op(op),
      right(right)
      {}


   T accept(Visitor<T> *visitor) {
      return visitor->visitUnaryExpr(this);
   }
   Token op;
   Expr<T>* right;
};
template<class T>
class Visitor {
public:
   virtual T visitBinaryExpr(Binary<T>* expr) = 0;
   virtual T visitGroupingExpr(Grouping<T>* expr) = 0;
   virtual T visitLiteralExpr(Literal<T>* expr) = 0;
   virtual T visitUnaryExpr(Unary<T>* expr) = 0;
};
