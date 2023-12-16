#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &src){(void)src;}

PmergeMe &PmergeMe::operator=(const PmergeMe &src){(void)src; return *this;}

PmergeMe::~PmergeMe(){}

void    PmergeMe::insertionSort(std::vector<unsigned int> &c, int start, int end)
{
    for (int i = start;i < end; i++)
    {
        int j = i + 1;
        unsigned int tmp = c[j];
        while (j > start && c[j - 1] > tmp)
        {
            c[j] = c[j - 1];
            j--;
        }
        c[j] = tmp;
    }
}

void   PmergeMe:: merge(std::vector<unsigned int> &c, int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;

    std::vector<unsigned int>   leftCon(c.begin() + start, c.begin() + mid + 1);
    std::vector<unsigned int>   rightCon(c.begin() + mid + 1, c.begin() + end + 1);

    int left = 0;
    int right = 0;
    for (int i = start; i <= end; i++)
    {
        if (right == n2)
        {
            c[i] = leftCon[left];
            right++;
        }
        else if (left == n1)
        {
            c[i] = rightCon[right];
        }
        else if (rightCon[right] > leftCon[left])
        {
            c[i] = leftCon[left];
            left++;
        }
        else
        {
            c[i] = rightCon[right];
            right++;
        }
    }
}

void    PmergeMe::sort(std::vector<unsigned int> &c, int start, int end)
{
    if ((end - start) > 5)
    {
        int mid = (end - start) / 2;
        sort(c, start, mid);
        sort(c, mid + 1, end);
        merge(c, start, mid, end);
    }
    else
        insertionSort(c, start, end);
}

