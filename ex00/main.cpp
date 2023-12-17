/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:38:43 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/17 15:24:09 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

size_t  characterCount(const std::string& line, char c)
{
    size_t characterCount = 0;
    
    for (size_t i = 0; i < line.length(); i++) {
        if(line[i] == c)
            characterCount++;
    }
    return (characterCount);
}

size_t  minusCount(const std::string& line)
{
    size_t characterCount = 0;
    
    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] == '-')
            characterCount++;
        if (line[i] == '|')
            return (characterCount);
    }
    return (characterCount);
}

bool isNumericCharacter(char c) 
{
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

bool isWhitespace(char c) 
{
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

bool    is_validcharacter(const std::string& line)
{
    for (size_t i = 0; i < line.length(); ++i)
    {
        if (!isNumericCharacter(line[i]) && !isWhitespace(line[i]) && line[i] != '-' && line[i] != '.' && line[i] != '|')
            return (false);
    }
    
    return (true);
}

std::string strtrim(const std::string& input) {
    size_t start = 0;
    size_t end = input.length();

    while (start < end && std::isspace(static_cast<unsigned char>(input[start]))) {
        ++start;
    }

    while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1]))) {
        --end;
    }

    return input.substr(start, end - start);
}

void    checkDateFormat(std::string date)
{
    std::string str[3];
    double  month, day;
    size_t c = 0;
    size_t i = -1;

    if (characterCount(date, '-') != 2)
        throw std::runtime_error("Error: invalid date format.");
    
    while (++i < date.length() && date[i])
    {
        if (date[i] == '-')
            break;
        c++;
    }
    if (c != 4)
        throw std::runtime_error("Error: invalid date format.");
    str[0] = date.substr(0, 4);
    
    c = 0;
    while (++i < date.length() && date[i])
    {
        if (date[i] == '-')
            break;
        c++;
    }
    if (c != 2)
        throw std::runtime_error("Error: invalid date format.");
    str[1] = date.substr(5, 2);

    c = 0;
    while (++i < date.length() && date[i])
    {
        if (date[i] == '-')
            break;
        c++;
    }
    if (c != 2)
        throw std::runtime_error("Error: invalid date format.");
    str[2] = date.substr(8, 2);
    
    month = atof(str[1].c_str());
    day = atof(str[2].c_str());
    if (!month || !day || month > 12 || day > 31)
        throw std::runtime_error("Error: invalid date format.");

    if (!(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 30)
        throw std::runtime_error("Error: invalid date format.");
    if(month == 2 && day > 29)
        throw std::runtime_error("Error: invalid date format.");
}

void    checkInvalidNumber(const char *s)
{
    int i = 0;

    while(s && isWhitespace(s[i]))
        i++;
    while(s && isNumericCharacter(s[i]))
        i++;
    while(s && isWhitespace(s[i]))
        i++;
    if (s && isNumericCharacter(s[i]))
        throw std::runtime_error("Error: invalid number.");
}

std::map<std::string, double> parseLine(const std::string& line)
{
    std::map<std::string, double> exchangeRates;
    
    if (!is_validcharacter(line) || characterCount(line, '|') != 1 || minusCount(line) != 2  || characterCount(line, '.') > 1 )
        throw std::runtime_error("Error: bad input => " + line);

    size_t pipePosition = line.find('|');

    std::string date = line.substr(0, pipePosition);
    date = strtrim(date);
    if (date.length() != 10)
        throw std::runtime_error("Error: invalid date format.");
    checkDateFormat(date);

    std::string numberString = line.substr(pipePosition + 1);
    checkInvalidNumber(numberString.c_str());
    double rate = atof(numberString.c_str());
    if (rate < 0)
        throw std::runtime_error("Error: not a positive number.");
    if (rate > 1000.0)
        throw std::runtime_error("Error: too large a number.");
    
    exchangeRates[date] = rate;
    
    return (exchangeRates);
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        try
        {
            BitcoinExchange exchange("data.csv");

            std::ifstream   inputFile(av[1]);
            if (!inputFile.is_open())
                throw std::runtime_error("Error: could not open input file.");
            
            std::string header;
            std::getline(inputFile, header);
            if (header != "date | value")
                std::cerr << "Error: Invalid database header\n";
            
            std::string line;
            while (std::getline(inputFile, line))
            {
                try
                {
                    std::map<std::string, double> data = parseLine(line);
                    std::map<std::string, double>::iterator it = data.begin();
                    double  exchaneRate = exchange.getExchangeRate(it->first);
                    double  result = it->second * exchaneRate;
                    std::cout << it->first << " => " << it->second << " = " << result << std::endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
            inputFile.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
        return 0;
    }
    std::cout << "Usage: " << av[0] << " input_file.txt" << std::endl;
    return 1;
}