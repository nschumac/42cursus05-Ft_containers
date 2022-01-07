#include "vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> test(10, 10);

    ft::vector<int>::iterator it1 = test.begin();
    ft::vector<int>::iterator it2 = test.end();
    *it1 = 5;

    test.insert(it1, 5, 50);
    for (ft::vector<int>::const_iterator itr = test.cbegin(); itr != test.cend(); itr++)
        std::cout << *itr << std::endl;
    ft::vector<int> test2(4,5);

    test2.insert(test2.begin(), test.begin(), test.end());
    std::cout << test2.size() << std::endl;
    for (ft::vector<int>::const_iterator itr = test2.cbegin(); itr != test2.cend(); itr++)
        std::cout << *itr << std::endl;
    return 0;
}
