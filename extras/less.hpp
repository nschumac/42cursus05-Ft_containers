#ifndef LESS_HPP
# define LESS_HPP

#include "binary_function.hpp"

namespace ft
{
	template <class T> 
	struct less : ft::binary_function <T, T, bool>
	{
 		bool operator() (const T& x, const T& y) const {return x < y;}
	};
}
#endif