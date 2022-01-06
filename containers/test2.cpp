#include "vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> test(4, 10);
    
    std::cout << test.size() << std::endl;
    for (ft::vector<int>::const_iterator itr = test.cbegin(); itr != test.cend(); itr++)
        std::cout << *itr << std::endl;

    ft::vector<int>::iterator it1 = test.begin();
    ft::vector<int>::iterator it2 = test.end();

    ft::vector<int> test2(it1, it2);
    std::cout << "3" << std::endl;
    for (ft::vector<int>::const_iterator itr = test2.cbegin(); itr != test2.cend(); itr++)
        std::cout << *itr << std::endl;
    return 0;
}
