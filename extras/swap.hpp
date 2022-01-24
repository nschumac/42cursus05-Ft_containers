#ifndef SWAP_HPP
#define SWAP_HPP

namespace ft
{

	template < class T >
	void my_swap(T & first, T &second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}


}


#endif

