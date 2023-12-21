#ifndef SIMPLEARITH_HPP
#define SIMPLEARITH_HPP

#include <iostream> // cout
#include <stack> // stack, push, pop, top
#include <string> 
#include <vector>

enum class Ops {Exp, Mul, Div, Add, Sub}; // exponent, multiplication, division, addition, subtraction

class SimpleArith
{
    std::vector<std::string> infixV_; // initial infix expression
    std::vector<std::string> postfixV_; // postfix expression
    double output_; // final output
    
public:
    SimpleArith(const std::vector<std::string> &v);
    void toString(); // print
    void calculate(); // the meat and potatoes
    
    ~SimpleArith();
    
private:
    Ops labelOps(const std::string &s); // label operators (string -> enum value)
    void infixToPostfix(); // convert infix expression to postfix
    int prec(const std::string &s); // return precedence of given operator
};

#endif // SIMPLEARITH_HPP
