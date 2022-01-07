#include "vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> test(10, 10);

    ft::vector<int>::iterator it1 = test.begin();
    ft::vector<int>::iterator it2 = test.end();
    *it1 = 5;

	ft::vector<int>::const_iterator cit = test.begin();
    test.insert(test.begin(), 5, 50);
	std::cout << "test:" ;
    for (ft::vector<int>::const_iterator itr = test.begin(); itr != test.end(); itr++)
        std::cout << *itr << ",";
    ft::vector<int> test2(4,5);

std::cout << "\n";
    test2.insert(test2.begin(), test.begin(), test.end());
	std::cout << "test2:" ;
    for (ft::vector<int>::const_iterator itr = test2.begin(); itr != test2.end(); itr++)
        std::cout << *itr << ",";
    return 0;
}
