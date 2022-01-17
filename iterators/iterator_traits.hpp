#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <cstdint>

namespace ft
{

	struct random_access_iterator_tag {};

	template < typename T >
	struct iterator_traits
	{
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef std::ptrdiff_t				difference_type;
		typedef random_access_iterator_tag	iterator_category;
	};

}

#endif