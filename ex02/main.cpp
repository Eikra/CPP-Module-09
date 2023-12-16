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

void insertionSort(std::vector<unsigned int>& A, int start, int end) {
    for (int i = start; i < end; i++) {
        unsigned int tempVal = A[i + 1];
        int j = i + 1;
        while (j > start && A[j - 1] > tempVal) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = tempVal;
    }
}

void merge(std::vector<unsigned int>& A, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;
    std::vector<unsigned int> LA(A.begin() + start, A.begin() + mid + 1);
    std::vector<unsigned int> RA(A.begin() + mid + 1, A.begin() + end + 1);
    int RIDX = 0;
    int LIDX = 0;
    for (int i = start; i <= end; i++) 
    {
        if (RIDX == n2) 
        {
            A[i] = LA[LIDX];
            LIDX++;
        } 
        else if (LIDX == n1) 
        {
            A[i] = RA[RIDX];
            RIDX++;
        } 
        else if (RA[RIDX] > LA[LIDX]) 
        {
            A[i] = LA[LIDX];
            LIDX++;
        } 
        else 
        {
            A[i] = RA[RIDX];
            RIDX++;
        }
    }
}

void sort(std::vector<unsigned int>& A, int start, int end) {
    if (end - start > 5) {
        int mid = (start + end) / 2;
        sort(A, start, mid);
        sort(A, mid + 1, end);
        merge(A, start, mid, end);
    } else {
        insertionSort(A, start, end);
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
        std::cout << "Before:";
        printContainer(vec);
        
        PmergeMe    sorter;

        std::clock_t start = std::clock();
        ::sort(vec, 0 , vec.size() - 1);
        std::clock_t end = std::clock();
        double elapsed = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
  
        std::clock_t start2 = std::clock();
        std::clock_t end2 = std::clock();
        double elapsed2 = 1000000.0 * (end2 - start2) / CLOCKS_PER_SEC;

        std::cout << "\n\nAfter: ";
        printContainer(vec);

        std::cout << "\n\nTime to process a range of "
                    << vec.size()
                    << " elements with std::vector : "
                    << elapsed
                    << " us\n";
            std::cout << "\nTime to process a range of "
                    << vec.size()
                    << " elements with std::deque : "
                    << elapsed2
                    << " us\n";
        std::cout << "\nAfter: ";
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}