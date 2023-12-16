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
        void    insertionSort(std::vector<unsigned int> &c, int start, int end);

        void    merge(std::vector<unsigned int> &c, int start, int mid, int end);
        
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &src);
        PmergeMe &operator=(const PmergeMe &src);
        ~PmergeMe();

        void    sort(std::vector<unsigned int> &c, int start, int end);
};
