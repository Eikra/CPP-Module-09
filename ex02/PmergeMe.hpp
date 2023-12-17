/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:09:29 by iecharak          #+#    #+#             */
/*   Updated: 2023/12/17 11:15:48 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <ctime>
#include <deque>
#include <exception>

class PmergeMe
{
    private:
        template <typename T>
        void    insertionSort(T &c, int start, int end)
        {
            for (int i = 0; i < end; i++)
            {
                
                int j = i + 1;
                unsigned int tmp = c[j];
                while(j > start && c[j - 1] > tmp)
                {
                    c[j] = c[j - 1];
                    j--;
                }
                c[j] = tmp;
            }
        }

        template <typename T>
        void    merge(T &c, int start, int mid, int end)
        {
            T   leftCon(c.begin() + start, c.begin() + mid + 1);
            T   rightCon(c.begin() + mid + 1, c.begin() + end + 1);

            int left = 0;
            int leftEnd = leftCon.size();
            int right = 0;
            int rightEnd = rightCon.size();

            for (int i = start; i <= end; i++)
            {
                if (right >= rightEnd)
                {
                    c[i] = leftCon[left];
                    left++;
                }
                else if (left >= leftEnd)
                {
                    c[i] = rightCon[right];
                    right++;
                }
                else if (leftCon[left] > rightCon[right])
                {
                    c[i] = rightCon[right];
                    right++;
                }
                else 
                {
                    c[i] = leftCon[left];
                    left++;
                }
            }
        }
        
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &src);
        PmergeMe &operator=(const PmergeMe &src);
        ~PmergeMe();
        template <typename T>
        void    sort(T &c, int start, int end)
        {
            if (end - start > 5)
            {
                int mid = (end + start) / 2;
                sort(c, start, mid);
                sort(c, mid + 1, end);
                merge(c, start, mid, end);
            }
            else
                insertionSort(c, start, end);
        }
};

#endif
