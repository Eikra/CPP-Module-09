#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}

RPN    &RPN::operator=(const RPN &src){(void)src; return *this;}

RPN::RPN(const RPN &src){(void)src;}

bool RPN::isOperator(char c) 
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPN::isDigit(char c) 
{
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

bool RPN::isWhitespace(char c) 
{
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

int     RPN::calculate(const std::string& expression)
{
    std::stack<int>    operands;
    std::stack<char>    operators;

    size_t  i = expression.length();
    size_t  j = 0;
    i--;

    while (j < expression.length())
    {
        if (isWhitespace(expression[i]))
        {
            i--;
            j++;
            continue;
        }
        else if (isDigit(expression[i]))
            operands.push(static_cast<int>(expression[i]) - 48);
        else if (isOperator(expression[i]))
            operators.push(expression[i]);
        else 
            throw std::runtime_error("Error");
        i--;
        j++;
    }

    if (operands.size() != (operators.size() + 1) || (!operands.size() && !operators.size()))
        throw std::runtime_error("Error");

    if (operands.size() == 1)
        return operands.top();
    std::cout << operands.top() << " ";
    int result = operands.top();
    operands.pop();
    while (operators.size())
    {
        std::cout << operators.top() << " ";
        std::cout << operands.top() << " ";
        
        result = performOperation(operators.top(), result, operands.top());
        operands.pop();
        operators.pop();
    }
    std::cout <<  "\n ";
    return result;
}

int RPN::performOperation(char op, int operand1, int operand2) 
{
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return safeDivide(operand1, operand2);
        default:
            return 0; 
    }
}

int RPN::safeDivide(int operand1, int operand2) 
{
    if (operand2 != 0) 
        return operand1 / operand2; 

    throw std::runtime_error( "Error: Division by zero");
}