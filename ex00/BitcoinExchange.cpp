/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:48:18 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/10 10:37:38 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string& databaseFile)
{
    file.open(databaseFile);
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");

    std::string header;
    std::getline(file, header);

    if (header != "date,exchange_rate")
        throw std::runtime_error ("Invalid database header");

    std::string line;
    while (std::getline(file, line))
    {
        size_t commaPosition = line.find(',');
        if (commaPosition != std::string::npos)
        {
            std::string date = line.substr(0, commaPosition);
            std::string numberString = line.substr(commaPosition + 1);
            double rate = std::stod(numberString);
            exchangeRates[date] = rate;
        }
        else 
            throw std::runtime_error ("Invalid input string format in database.");
    }
    file.close();

}

double  BitcoinExchange::getExchangeRate(const std::string& date)
{
    std::map<std::string, double>::const_iterator   it = exchangeRates.lower_bound(date);

    if (it == exchangeRates.begin() && date < it->first)
        throw std::out_of_range("Error: date not found in database.");

    if (it == exchangeRates.end())
        throw std::out_of_range("Error: date not found in database.");
    
    while (it != exchangeRates.begin() && it->first > date)
        --it;
    return it->second;
}

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src){(void)src;}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src){(void)src;return *this;}

BitcoinExchange::~BitcoinExchange(){}