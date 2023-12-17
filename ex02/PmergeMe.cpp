/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:24:35 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/17 11:42:29 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &src){(void)src;}

PmergeMe &PmergeMe::operator=(const PmergeMe &src){(void)src; return *this;}

PmergeMe::~PmergeMe(){}

