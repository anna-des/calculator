#ifndef SIMPLEARITH_HPP
#define SIMPLEARITH_HPP

#include <string> 
#include <vector>

enum class Ops {Exp, Mul, Div, Add, Sub}; // exponent, multiplication, division, addition, subtraction

class SimpleArith
{
public:
    SimpleArith(const std::vector<std::string> &v);
    void toString(); // print
    void calculate(); // the meat and potatoes
    
    ~SimpleArith();
    
private:
    std::vector<std::string> infixV_; // initial infix expression
    std::vector<std::string> postfixV_; // postfix expression
    double output_; // final output
    
    Ops labelOps(const std::string &s); // label operators (string -> enum value)
    void infixToPostfix(); // convert infix expression to postfix
    int prec(const std::string &s); // return precedence of given operator
};

#endif // SIMPLEARITH_HPP
