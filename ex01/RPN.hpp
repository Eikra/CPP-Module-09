/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:23:57 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/17 11:23:58 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <stdexcept>
#include <iomanip>

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