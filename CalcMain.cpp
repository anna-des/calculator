#include <stdio.h>
#include <iostream> // cin, cout
#include <string> // getline
#include <cctype>
#include <vector> // vector
#include <algorithm> // remove
#include <stack>

#include "SimpleArith.hpp"

// GLOBAL VARIABLES
const char DEC_POINT = '.';

bool isOperator(const char &c){
    if (c == '+' || c == '*' || c == '/' || c == '^'){
        return true;
    }
    return false;
}

// check parentheses, brackets, curly brackets are matching
// NOTE: used exclusively for checkParen()
bool isMatching(char x, char y){
    return ((x == '(' && y == ')') || (x == '{' && y == '}') || (x == '[' && y == ']'));
}

// check for valid parenthesis, brackets, and curly brackets using a stack
bool checkParen(const std::string &s){
    std::stack<char> st;
    
    for (unsigned int i = 0; i < s.length(); i++){
        if (s[i] == '(' || s[i] == '[' || s[i] == '{'){
            st.push(s[i]);
        } else if (s[i] == ')' || s[i] == ']' || s[i] == '}'){
            if (st.empty()){
                return false;
            }
            if (isMatching(st.top(), s[i])){
                st.pop();
            } else {
                return false;
            }
        }
    }

    return st.empty();
}

// EXCEPTION CHECKER
bool checkString(const std::string &s){
    
    // if first character is operator (not a negative sign)
    if (isOperator(s[0])){
        std::cout << "\nFirst element cannot be +,*,/,^. (If you are putting a + to indicate a positive "
                  << "number, that's redundant. Leave that particular + out.\n";
        return false;
    }
    // if first character is '-' and next character is not a digit
    if (s[0] == '-' && !std::isdigit(static_cast<unsigned char>(s[1]))){
        std::cout << "Error with first element.\n";
        return false;
    }
    // if last character is operator (or negative/minus sign)
    if (isOperator(s[s.length()-1]) || s[s.length()-1] == '-'){
        std::cout << "\nLast element can't be an operator, silly.\n";
    }
    // if first character is decimal point
    if (s[0] == DEC_POINT){
        std::cout << "\nPlease put a 0 before the . for a decimal.\n";
        return false;
    }
    // if last character is decimal point
    if (s[s.length()-1] == DEC_POINT){
        std::cout << "\nLast element can't be a decimal point, silly.\n";
        return false;
    }
    // if parentheses, square brackets, or curly brackets are not valid
    if (!checkParen(s)){
        std::cout << "\nParentheses, square brackets, or curly brackets not found to be valid.\n";
        return false;
    }
    
    int decCounter = 0; // to be used in DECIMAL SECTION
    for (unsigned int i = 0; i < s.length(); i++){
        // if there are 2 or more operators in a row
        if (i < s.length() - 1 && isOperator(s[i]) && isOperator(s[i+1])){
            std::cout << "\nOperator problem detected. Most likely two or more operators in a row.\n";
            return false;
        }
        // if it is '-' followed by operator 
        if (i < s.length() - 1 && s[i] == '-' && isOperator(s[i+1])){
            std::cout << "\nOperator problem detected: operator immediately following a negative/minus sign.\n";
            return false;
        }
        // if it is an operator followed immediately by ')'
        if (i < s.length() - 1 && isOperator(s[i]) && s[i+1] == ')'){
            std::cout << "\nYou can't place a right parenthesis right after an operator, silly.\n";
            return false;
        }
        // if there is no preceding number before given decimal point
        if (s[i] == DEC_POINT && !std::isdigit(static_cast<unsigned char>(s[i-1]))){
            std::cout << "\nDecimal not found to be valid. (If you are wanting to input a decimal less than 1, " 
                      << "please put a 0 before the . )\n";
            return false;
        }
        
        
        // DECIMAL SECTION
        
        // ensuring against repeated decimals in one number, i.e. 1.2.3.4
        if (decCounter > 0 && s[i] == DEC_POINT){
            std::cout << "\nDecimal error detected.\n";
            return false;
        } else if (decCounter == 0 && s[i] == DEC_POINT){
            decCounter++;
        } else if (decCounter > 0 && (isOperator(s[i]) || s[i] == '-')){
            decCounter--;
        }
        // if there is no number immediately following decimal point
        if (s[i] == DEC_POINT && !std::isdigit(static_cast<unsigned char>(s[i+1])) ){
            std::cout << "\nDecimal not found to be valid.\n";
            return false;
        }
    }
    return true;
}

// get string input
std::string getStringInput(){
    // get input
    std::string s = "";
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cout << "Please enter string: \n";
    std::getline(std::cin, s);
    
    // remove whitespace
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

    // if input fails checks, continue to prompt until correct input is given
    while (!checkString(s) || s == ""){
        std::cout << "Try again.\nPlease enter string:\n";
        std::getline(std::cin, s);
    }
    std::cout << "\nString appears to pass checks. Moving on...\n";
    
    return s;
}

// convert input string from user to string vector (with concatenated digits)
std::vector<std::string> initialVectInsert(std::string s){
    std::vector<std::string> v;
    
    std::string temp = "";
    for (unsigned int i = 0; i < s.length(); i++){
        temp = s[i];
        
        // FOR POSITIVE NUMBERS: while current char is digit and not the last char in string
        while ((std::isdigit(static_cast<unsigned char>(s[i])) || s[i] == DEC_POINT) && i < s.length() - 1){
            
            // if next char is digit or decimal point, add next char to temp string
            // else, move on
            if (std::isdigit(static_cast<unsigned char>(s[i+1])) || s[i+1] == DEC_POINT){
                temp += s[i+1];
                i++;
            } else {
                break;
            }
        }
        
        // FOR NEGATIVE NUMBERS: if current char is not last char in string, current char is '-',
        // next char is digit, AND either current char is first char in string or previous char is not a digit
        if (i < s.length() - 1 && s[i] == '-' && std::isdigit(static_cast<unsigned char>(s[i+1])) && (i == 0 || !std::isdigit(static_cast<unsigned char>(s[i-1])))){
            
            // add next char to temp string, increment, then follow same procedure as with positive numbers
            temp += s[i+1];
            i++;
            
            // while current char is digit and not the last char in string
            while ((std::isdigit(static_cast<unsigned char>(s[i])) || s[i] == DEC_POINT) && i < s.length() - 1){
            
                // if next char is digit or decimal point, add next char to temp string
                // else, move on
                if (std::isdigit(static_cast<unsigned char>(s[i+1])) || s[i+1] == DEC_POINT){
                    temp += s[i+1];
                    i++;
                } else {
                    break;
                }
            }
        }
        
        // add temp string to vector and reset
        v.push_back(temp);
        temp = "";
    }
    
    return v;
}

// print vector
void printVect(std::vector<std::string> &v){
    for (const std::string &s : v){
        std::cout << s << " ";
    }
}

// MAIN MENU
int menu(){
    std::cout << "\n\n------------Menu------------\n";
    std::cout << "0. Quit Program\n";
    std::cout << "1. Simple Arithmetic\n";
    
    int choice;
    std::cout << "\nPlease input the number of your selection: ";
    std::cin >> choice;
    while (std::cin.fail() || choice < 0 || choice > 1){
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "\nPlease input valid selection number: ";
        std::cin >> choice;
    }
    return choice;
}

// 0. Quit Program
void programEnd(){
    std::cout << "\n\n-----------Thank you for using my Calculator.-----------\n";
}

// 1. Simple Arithmetic
void optionOne(){
    std::vector<std::string> v(initialVectInsert(getStringInput()));
    
    // *****TEMP*********
    std::cout << "\nHere is what you entered: \n";
    printVect(v);
    std::cout << "\nSize of vector: " << v.size() << "\n";
    // ******************
    
    if (v.size() == 1){ // if there's only one element, no use activating a whole arithmetic class
        std::cout << "Final Result: " << v.front() << "\n";
    } else if (v.size() == 2){ // ***ideally a redundant layer of security, keep for the moment
        std::cout << "Error: Not enough elements to perform valid operation.\n";
    } else { // at least 3 elements needed for evaluation
        SimpleArith sa(v);
        sa.calculate(); 
    }
}

// MAIN
int main(int argc, char **argv)
{
    std::cout << "---Welcome to Calculator!---";
    int choice = menu();    
    while (choice != 0){
        if (choice == 1){
            optionOne();
        }
        std::cout << "\n\nReturning to Menu...";
        choice = menu();
    }
    
    
    programEnd();
	return 0;
}

