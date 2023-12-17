/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:12:43 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/17 15:31:13 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>

bool isDigit(char c) 
{
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

void    IsNumber(char *s)
{
    int i = 0;
    while (s && s[i])
    {
        if (!isDigit(s[i]))
            throw std::runtime_error("Non Digit Character Entred");
        i++;
    }    
}

unsigned int getNumber(char* &s)
{
    std::istringstream iss(s);
    unsigned int result;
    if (!(iss >> result))
        throw std::runtime_error("Conversion to unsigned int failed");
    return result;
}

void parse(std::vector<unsigned int> &vec, std::deque<unsigned int> &deq , char **av)
{
    int i = 1;
    while (av[i])
    {
        if (av[i][0])
        {
            IsNumber(av[i]);
            vec.push_back(getNumber(av[i]));
            deq.push_back(getNumber(av[i]));
        }
        i++;
    }
}

void    printContainer(std::vector<unsigned int> &vec)
{
    size_t  i = 0;
    size_t  end = vec.size();
    while (i < end)
    {
        std::cout << vec[i] << " ";
        i++;
    }
}

int main(int ac, char **av) 
{
    if (ac < 2)
    {
        std::cout << "Too few argument" << std::endl;
        return 1;
    }
    try
    {
        std::vector<unsigned int>   vec;
        std::deque<unsigned int>    deq;
        parse(vec, deq, av);
        
        std::cout << "Before: ";
        printContainer(vec);
        
        PmergeMe    sorter;

        std::clock_t start2 = std::clock();
        sorter.sort(deq, 0 , deq.size() - 1);
        std::clock_t end2 = std::clock();
        double elapsed2 = 1000000.0 * (end2 - start2) / CLOCKS_PER_SEC;

        std::clock_t start = std::clock();
        sorter.sort(vec, 0 , vec.size() - 1);
        std::clock_t end = std::clock();
        double elapsed = 1000000.0 * (end - start) / CLOCKS_PER_SEC;

        std::cout << "\n\nAfter:  ";
        printContainer(vec);

        std::cout << "\n\nTime to process a range of " << vec.size() << " elements with std::vector : " << elapsed << " us\n";
        
        std::cout << "\nTime to process a range of " << vec.size() << " elements with std::deque : " << elapsed2 << " us\n";
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}

