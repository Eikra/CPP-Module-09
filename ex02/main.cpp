#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

// Function to perform binary search and insert an element into a sorted list
template<typename T>
typename std::list<T>::iterator binarySearchAndInsert(std::list<T>& sortedList, const T& element) {
    typename std::list<T>::iterator it = std::lower_bound(sortedList.begin(), sortedList.end(), element);
    return sortedList.insert(it, element);
}

// Function to perform Merge-Insertion sort on a std::list
template<typename T>
std::list<T> mergeInsertionSort(const std::list<T>& inputList) {
    // Base case: if the input list has 0 or 1 element, it is already sorted
    if (inputList.size() <= 1) {
        return inputList;
    }

    // Step 1: Group elements into pairs and find the larger element in each pair
    std::list<T> largerElements;
    typename std::list<T>::const_iterator it = inputList.begin();
    while (std::distance(it, inputList.end()) >= 2) {
        T element1 = *it;
        ++it;
        T element2 = *it;
        ++it;

        // Compare and find the larger element
        T largerElement = (element1 < element2) ? element2 : element1;

        // Add the larger element to the list
        largerElements.push_back(largerElement);
    }

    // Step 2: Recursively sort the larger elements
    largerElements = mergeInsertionSort(largerElements);

    // Step 3: Insert the element paired with the first and smallest element of the sorted sequence
    largerElements.push_front(inputList.front());

    // Step 4: Insert the remaining elements into the sorted sequence using binary search
    it = std::next(inputList.begin());
    while (it != inputList.end()) {
        // Binary search and insert the element into the sorted sequence
        binarySearchAndInsert(largerElements, *it);
        ++it;
    }
    return largerElements;
}

void PmergeMe(std::vector<long> &vec)
{
    std::vector<long>   toSort;
    size_t              size  = 0;

    while ((size + 1) < vec.size())
    {
        if (vec[size] > vec[size + 1])
        {
            toSort.push_back(vec[size + 1]);
            toSort.push_back(vec[size]);
        }
        else
        {
            toSort.push_back(vec[size]);
            toSort.push_back(vec[size + 1]);
        }
            
        size++;
        size++;
    }
    if (vec.size() > toSort.size())
        toSort.push_back(vec.back());
    std::vector<long>::iterator it = toSort.begin();
    while (it != toSort.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "\nlol\n";
}

int main() {

    std::vector<long> foo;
    foo.push_back(2);
    foo.push_back(1);
    foo.push_back(4);
    foo.push_back(3);
    foo.push_back(6);
    foo.push_back(5);
    foo.push_back(8);
    foo.push_back(7); 
    foo.push_back(9); 
    std::cout << "Before:\n";
    std::vector<long>::iterator it = foo.begin();
    while (it != foo.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "\nAfter:\n";
    PmergeMe(foo);
    

    return 0;
}