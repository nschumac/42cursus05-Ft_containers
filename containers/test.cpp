#include <iostream>
#include "vector.hpp"
#include <vector>

int main(void)
{

    std::vector<int> test1;
    test1.reserve(1);
    test1[0] = 10;
    test1.pop_back();
    for (int i = 0; i < 10; i++)
    {
        std::cout << "size: " << test1.size() << std::endl;
        test1.push_back(i);
        std::cout << "cap: " << test1.capacity() << std::endl;
    }
    for (int i = 0; i < test1.size(); i++)
        std::cout << "val: " << test1[i];
    std::cout << std::endl;
    std::cout << test1[0] << std::endl;
    std::cout << test1.max_size() << std::endl;
    std::cout << test1.size() << std::endl;
    std::cout << test1.capacity() << std::endl;

    std::vector<int>::iterator it1 = test1.begin();
    std::vector<int>::const_iterator cit1 = test1.cbegin();
    std::cout<< "....................." << std::endl;

    test1.insert(test1.begin(), 10);
    for (int i = 0; i < test1.size(); i++)
        std::cout << "val: " << test1[i];

    std::cout << std::endl;

    test1.insert(test1.begin(), 10, 100);
    for (int i = 0; i < test1.size(); i++)
        std::cout << "val: " << test1[i];

    std::cout<< "....................." << std::endl;
    std::cout << std::endl;



    auto it10 = test1.rbegin();
    auto it11 = test1.rend();

    std::cout << "-----------------" << std::endl;
    std::cout << *test1.begin() << std:: endl;
    std::cout <<"begin:" <<  *it10 << ":" << *it10.base() << std::endl;
    std::cout << "end:" << *it11 << ":" << *it11.base() << std::endl;
    std::cout << "-----------------" << std::endl;


    try
    {
        std::cout << *cit1;
    }
    catch (std::exception &f)
    {
        std::cout << "exception caught" << std::endl;
    }


    std::cout << *it1 << std::endl;
    it1++;
    std::cout << *it1 << std::endl;
    std::cout << it1[0] << std::endl;
    std::cout << it1[4] << std::endl;

    ft::vector<int> test;
    test.reserve(1);
    test[0] = 10;
    test.pop_back();
    for (int i = 0; i < 10; i++)
    {
        std::cout << "size: " << test.size() << std::endl;
        test.push_back(i);
        std::cout << "cap: " << test.capacity() << std::endl;
    }
    for (int i = 0; i < test.size(); i++)
        std::cout << "val: " << test[i];
    std::cout << std::endl;
    std::cout << test[0] << std::endl;
    std::cout << test.max_size() << std::endl;
    std::cout << test.size() << std::endl;
    std::cout << test.capacity() << std::endl;

    ft::vector<int>::iterator it = test.begin();
    ft::vector<int>::const_iterator cit = test.cbegin();

    std::cout<< "....................." << std::endl;
    test.insert(test.begin(), 10);
    for (int i = 0; i < test.size(); i++)
        std::cout << "val: " << test[i];

    std::cout << std::endl;


    test.insert(test.begin(), 10, 100);
    std::cout << *test.begin() << test[0] << std::endl;

    for (int i = 0; i < test.size(); i++)
        std::cout << "val: " << test[i];

    std::cout<< "....................." << std::endl;
    std::cout << std::endl;
    
    auto cit10 = test.rbegin();
    auto cit11 = test.rend();

    std::cout << "-----------------" << std::endl;
    std::cout << *test.begin() << std:: endl;
    std::cout <<"begin:" <<  *cit10 << ":" << *cit10.base() << std::endl;
    std::cout << "end:" << *cit11 << ":" << *cit11.base() << std::endl;
    std::cout << "-----------------" << std::endl;

    try
    {
        std::cout << *cit;
    }
    catch (std::exception &f)
    {
        std::cout << "exception caught" << std::endl;
    }
    std::cout << *it << std::endl;
    it++;
    std::cout << *it << std::endl;
    std::cout << it[0] << std::endl;
    std::cout << it[4] << std::endl;

    try {
        test.at(1) = 10;
    }catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

}
