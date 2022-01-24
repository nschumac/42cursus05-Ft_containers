#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <cstddef>

#include "iterator_traits.hpp"
#include "iterator.hpp"

namespace ft
{

	template < typename T>
	class vector_iterator : public ft::iterator<random_access_iterator_tag, T>
	{
		public:

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;

		private:

			pointer _ptr;

		public:

			vector_iterator (pointer ptr = nullptr) : _ptr(ptr) {}
			vector_iterator (const vector_iterator& in) :_ptr(in._ptr) {}

			~vector_iterator () {}


			pointer base() const { return this->_ptr; }


			vector_iterator& operator++ () { ++this->_ptr; return *this; }
			vector_iterator& operator-- (){ --this->_ptr; return *this; }

			vector_iterator operator++ (int) { vector_iterator tmp(*this); operator++(); return tmp; }
			vector_iterator operator-- (int) { vector_iterator tmp(*this); operator--(); return tmp; }

            bool operator==(const vector_iterator& in) const    { return (in._ptr == this->_ptr); }
            bool operator!=(const vector_iterator& in) const    { return (in._ptr != this->_ptr); }
            bool operator<(const vector_iterator& in) const     { return (in._ptr > this->_ptr); }
            bool operator>(const vector_iterator& in) const     { return (in._ptr < this->_ptr); }
            bool operator<=(const vector_iterator& in) const    { return (in._ptr >= this->_ptr); }
            bool operator>=(const vector_iterator& in) const    { return (in._ptr <= this->_ptr); }

			vector_iterator operator+ (difference_type nb) const { return this->_ptr + nb; }

			vector_iterator operator- (difference_type nb) const { return this->_ptr - nb; }

			difference_type operator-(vector_iterator const & in) { return this->_ptr - in._ptr; }

			reference operator* () const { return *this->_ptr; }
			reference operator[] (difference_type i) const { return *(operator+(i)); }
			pointer operator-> () const { return &(this->operator*()); }

			vector_iterator &operator= (const vector_iterator& in) { _ptr = in._ptr; return *this; }
			vector_iterator &operator+= (int i) { _ptr += i; return *this; }
			vector_iterator &operator-= (int i) { _ptr -= i; return *this; }

			// conversion function for non-const -> const
			operator vector_iterator<const T> () const { return (vector_iterator<const T>(this->_ptr)); }

	};

	template < typename T>
	ft::vector_iterator<T> operator- (typename ft::vector_iterator<T>::difference_type n, const vector_iterator<T> &in)
	{
		return (in - n);
	}

	template < typename T>
	ft::vector_iterator<T> operator+ (typename ft::vector_iterator<T>::difference_type n, const vector_iterator<T> &in)
	{
		return (in + n);
	}

	template < typename T>
	typename ft::iterator_traits<vector_iterator<T> >::difference_type operator- (const ft::vector_iterator<T> first, const ft::vector_iterator<T> second)
	{
		return (first.base() - second.base());
	}

	template < typename T, typename U >
	typename ft::iterator_traits<vector_iterator<T> >::difference_type operator- (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
	{
		return (first.base() - second.base());
	}

	template < typename T, typename U >
	bool operator!= (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
	{
		return (first.base() != second.base());
	}

	template < typename T, typename U >
	bool operator== (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
	{
		return (first.base() == second.base());
	}

	template < typename T, typename U >
	bool operator< (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
	{
		return (first.base() < second.base());
	}

	template < typename T, typename U >
	bool operator<= (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
	{
		return (first.base() <= second.base());
	}

	template < typename T, typename U >
	bool operator> (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
	{
		return (first.base() > second.base());
	}

	template < typename T, typename U >
	bool operator>= (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
	{
		return (first.base() >= second.base());
	}

	template < class Iterator >
	typename ft::iterator_traits<Iterator>::difference_type distance (Iterator first, Iterator last)
	{
		typename ft::iterator_traits<Iterator>::difference_type diff = 0;

		while (first != last)
		{
			++first;
			++diff;
		}

		return diff;
	}
}


#endif