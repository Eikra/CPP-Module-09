/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:24:06 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/17 14:58:46 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>

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
    std::stack<int>     operands;
    //std::stack<char>    operators;
    std::stack<char>    expr;

    size_t  i = 0;
    size_t   j = expression.length() - 1;

    while (i < expression.length())
    {
        if (isWhitespace(expression[j]))
        {
            i++;
            j--;
            continue;
        }
        else if (!isDigit(expression[j]) && !isOperator(expression[j]))
            throw std::runtime_error("Error");
        else
        {
            expr.push(expression[j]);
            j--;
            i++;
        }
    }
    
    if (expr.size() <= 2)
        throw std::runtime_error("Error");
    
    while (1)
    {
        if (!expr.size() && operands.size() > 1)
            throw std::runtime_error("Error");
        if (!expr.size())
            break;
        else if (isDigit(expr.top()))
        {
            operands.push(expr.top() - 48);
            expr.pop();
            continue;
        }
        if (isOperator(expr.top()))
        {
            if (operands.size() < 2)
                throw std::runtime_error("Error");
            int result = operands.top();
            operands.pop();
            
            result = performOperation(expr.top(), operands.top(), result);
            
            operands.pop();
            expr.pop();

            operands.push(result);
        }
    }
    return operands.top();
}

int RPN::performOperation(char op, int operand1, int operand2) 
{
    //std:: cout << operand1 << " " << op << " " << operand2 << '\n';
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
