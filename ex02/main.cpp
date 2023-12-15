#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

std::list<long> mergeLists(std::list<long>& left, std::list<long>& right)
{
    std::list<long> result;

    // Merge the two vectors until one of them becomes empty
    while (!left.empty() && !right.empty())
	{
        if (left.front() <= right.front())
		{
            result.push_back(left.front());
            left.erase(left.begin());
        }
		else
		{
            result.push_back(right.front());
            right.erase(right.begin());
        }
    }

    // Add any remaining elements from the left vector
    while (!left.empty())
	{
        result.push_back(left.front());
        left.erase(left.begin());
    }

    // Add any remaining elements from the right vector
    while (!right.empty())
	{
        result.push_back(right.front());
        right.erase(right.begin());
    }
    return result;
}


std::list<long> mergeInsertList(std::list<long>& lst) {
    // Base case: a list with zero or one elements is already sorted
    if (lst.size() <= 1) {
        return lst;
    }

    // Divide the list into two halves
    int mid = lst.size() / 2;
	std::list<long> left;
	std::list<long> right;

    for (int i = 0; i < mid; i++) {
        left.push_back(lst.front());
        lst.pop_front();
    }
    right = lst;

    // Recursively sort the left and right halves
    left = mergeInsertList(left);
    right = mergeInsertList(right);

    // Merge the sorted halves
    return mergeLists(left, right);
}

int main() {

    std::list<long> foo;
    foo.push_back(2);
    foo.push_back(1);
    foo.push_back(4);
    foo.push_back(3);
    // foo.push_back(6);
    // foo.push_back(5);
    // foo.push_back(8);
    // foo.push_back(7); 
    // foo.push_back(9); 
    std::cout << "Before:\n";
    std::list<long>::iterator it = foo.begin();
    while (it != foo.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "\nAfter:\n";
    foo = mergeInsertList(foo);
     it = foo.begin();
    while (it != foo.end())
    {
        std::cout << *it << " ";
        it++;
    }
    
    return 0;
}