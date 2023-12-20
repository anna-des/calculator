#ifndef SIMPLEARITH_HPP
#define SIMPLEARITH_HPP

#include <iostream> // cout
#include <stack> // stack, push, pop, top
#include <string> 
#include <vector>
#include <map>

enum Ops {Exp, Mul, Div, Add, Sub}; // exponent, multiplication, division, addition, subtraction

class SimpleArith
{
    std::vector<std::string> infix_v; // initial infix expression
    std::vector<std::string> postfix_v; // postfix expression
    double output; // final output
    
public:
    SimpleArith(const std::vector<std::string> &v);
    void to_string(); // print
    void calculate(); // the meat and potatoes
    
    ~SimpleArith();
    
private:
    Ops label_ops(const std::string &s); // label operators (string -> enum value)
    void infix_to_postfix(); // convert infix expression to postfix
    int prec(const std::string &s); // return precedence of given operator
};

#endif // SIMPLEARITH_HPP
