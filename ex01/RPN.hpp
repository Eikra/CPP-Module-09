#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <stdexcept>

class RPN
{
public:
    RPN();
    ~RPN();
    int     calculate(const std::string& expression);
    
private:
    bool    isOperator(char c);
    int     performOperation(char op, int operand1, int operand2);
    bool    isDigit(char c);
    bool    isWhitespace(char c);
    int     safeDivide(int operand1, int operand2);


    RPN    &operator=(const RPN &src);
    RPN(const RPN &src);
};

#endif