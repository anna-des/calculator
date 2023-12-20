#include "SimpleArith.hpp"

SimpleArith::SimpleArith(const std::vector<std::string> &v)
{
    for (auto &s : v){
        infix_v.push_back(s);
    }
}

Ops SimpleArith::label_ops(const std::string &s){
    if (s == "^"){
        return Exp;
    }
    if (s == "*"){
        return Mul;
    }
    if (s == "/"){
        return Div;
    }
    if (s == "+"){
        return Add;
    }
    
    // return Sub as default
    return Sub;
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

void SimpleArith::infix_to_postfix(){
    std::stack<std::string> st;
    
    for (auto &s : infix_v){
        
        // if element is number, add to postfix_v
        if (s != "+" && s != "-" && s != "*" && s != "/" && s != "^" && s != "(" && s != ")"){
            postfix_v.push_back(s);
            
        // if element is left parenthesis or bracket,
        // push to stack
        } else if (s == "(" || s == "[" || s == "{"){
            st.push(s);
            
        // if element is right parenthesis or bracket,
        // pop and add to postfix_v from stack until
        // left parenthesis or bracket is encountered
        } else if (s == ")" || s == "]" || s == "}"){
            while (st.top() != "(" && st.top() != "[" && st.top() != "{"){
                postfix_v.push_back(st.top());
                st.pop();
            }
            st.pop();
            
        // if element is operator, compare precedence 
        // of current element vs. that which is already 
        // on top of stack
        } else {
            while (!st.empty() && prec(s) <= prec(st.top())){
                postfix_v.push_back(st.top());
                st.pop();
            }
            st.push(s);
        }
    }
    
    // pop all remaining elements from stack
    while (!st.empty()){
        postfix_v.push_back(st.top());
        st.pop();
    }
    
    // print
    to_string();
}

void SimpleArith::calculate(){
    std::cout << "\n------From Class SimpleArith------\n";
    std::cout << "Calling infix_to_postfix function...\n";
    
    // convert infix to postfix
    infix_to_postfix();
    
    std::stack<double> st;
    double result = 0.0;
    
    for (std::string &s : postfix_v){
        
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
            
            switch(label_ops(s)){
            case Exp:
                std::cout << "\nExponent found -> Val1: " << val1 << " Val2: " << val2;
                result = val2;
                for (int n = 0; n < val1 - 1; n++){
                    result *= val2;
                }
                std::cout << "\nResult of " << val2 << " to the " << val1 << " power: " << result << ". Pushing onto stack...";
                st.push(result);
                break;
            case Mul:
                std::cout << "\nMultiplication request detected...";
                st.push(val2 * val1);
                break;
            case Div:
                std::cout << "\nDivision request detected...";
                st.push(val2 / val1);
                break;
            case Add:
                std::cout << "\nAddition request detected...";
                st.push(val2 + val1);
                break;
            case Sub:
                std::cout << "\nSubtraction request detected...";
                st.push(val2 - val1);
                break;
            default:
                std::cout << "\nError. Not a valid operator.\n";
                break;
            }
        }
    }
    output = st.top();
    std::cout << "\n\nFinal Result: " << output;
}

void SimpleArith::to_string(){
    std::cout << "Infix expression: ";
    for (const std::string &s : infix_v){
        std::cout << s << " ";
    }
    std::cout << "\nPostfix expression: ";
    
    if (!postfix_v.empty()){
        for (const std::string &s : postfix_v){
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
}

SimpleArith::~SimpleArith()
{
}