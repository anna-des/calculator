#include <iostream> // cout
#include <stack> // stack, push, pop, top
#include <string> 
#include <vector>
#include <cstdlib> // abs
#include <cmath> // pow
#include <iomanip> // setprecision

#include "SimpleArith.hpp"


SimpleArith::SimpleArith(const std::vector<std::string> &v)
{
    for (auto &s : v){
        infixV_.push_back(s);
    }
}

Ops SimpleArith::labelOps(const std::string &s){
    if (s == "^"){
        return Ops::Exp;
    }
    if (s == "*"){
        return Ops::Mul;
    }
    if (s == "/"){
        return Ops::Div;
    }
    if (s == "+"){
        return Ops::Add;
    }
    
    // return Sub as default
    return Ops::Sub;
}

int SimpleArith::prec(const std::string &s){ // precedence of operators
    if (s == "^"){
        return 3;
    } else if (s == "*" || s == "/"){
        return 2;
    } else if (s == "+" || s == "-"){
        return 1;
    } else {
        return -1;
    }
}

void SimpleArith::infixToPostfix(){
    std::stack<std::string> st;
    
    for (auto &s : infixV_){
        
        // if element is number, add to postfixV_
        if (s != "+" && s != "-" && s != "*" && s != "/" && s != "^" && s != "(" && s != ")"){
            postfixV_.push_back(s);
            
        // if element is left parenthesis or bracket,
        // push to stack
        } else if (s == "(" || s == "[" || s == "{"){
            st.push(s);
            
        // if element is right parenthesis or bracket,
        // pop and add to postfixV_ from stack until
        // left parenthesis or bracket is encountered
        } else if (s == ")" || s == "]" || s == "}"){
            while (st.top() != "(" && st.top() != "[" && st.top() != "{"){
                postfixV_.push_back(st.top());
                st.pop();
            }
            st.pop();
            
        // if element is operator, compare precedence 
        // of current element vs. that which is already 
        // on top of stack
        } else {
            while (!st.empty() && prec(s) <= prec(st.top())){
                postfixV_.push_back(st.top());
                st.pop();
            }
            st.push(s);
        }
    }
    
    // pop all remaining elements from stack
    while (!st.empty()){
        postfixV_.push_back(st.top());
        st.pop();
    }
}

void SimpleArith::calculate(){
    // convert infix to postfix
    infixToPostfix();
    
    std::stack<double> st;
    double result = 0.0;
    
    for (std::string &s : postfixV_){
        
        // if element is number, push to stack
        if (s != "+" && s != "-" && s != "*" && s != "/" && s != "^"){
            st.push(std::stod(s));
            
        // else, pop two elements from stack and apply the operator
        // push the result back onto the stack
        } else {
            double val1 = st.top();
            st.pop();
            double val2 = st.top();
            st.pop();
            
            switch(labelOps(s)){
            case Ops::Exp:
                result = pow(val2, val1);
                st.push(result);
                break;
            case Ops::Mul:
                st.push(val2 * val1);
                break;
            case Ops::Div:
                st.push(val2 / val1);
                break;
            case Ops::Add:
                st.push(val2 + val1);
                break;
            case Ops::Sub:
                st.push(val2 - val1);
                break;
            default:
                break;
            }
        }
    }
    output_ = st.top();
}

void SimpleArith::toString(){
    std::cout << "\n------From Class SimpleArith------\n\n";
    
    std::cout << "Infix expression: ";
    for (const std::string &s : infixV_){
        std::cout << s << " ";
    }
    std::cout << "\nPostfix expression: ";
    
    if (!postfixV_.empty()){
        for (const std::string &s : postfixV_){
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nFinal Result: " << std::setprecision(15) << output_;
}

SimpleArith::~SimpleArith()
{
}