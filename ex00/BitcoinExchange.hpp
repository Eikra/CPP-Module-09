/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:24:42 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/10 10:36:44 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>

class   BitcoinExchange
{
    private:
        std::map<std::string, double>   exchangeRates;
        std::ifstream                   file;
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &src);
        BitcoinExchange &operator=(const BitcoinExchange &src);
    public:
        BitcoinExchange(const std::string& databaseFile);
        ~BitcoinExchange();
        double  getExchangeRate(const std::string& date);
};

#endif