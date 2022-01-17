#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <cstddef>

#include "iterator_traits.hpp"

namespace ft
{

	template < typename T>
	class vector_iterator
	{

		public:

			typedef T													value_type;
			typedef typename ft::random_access_iterator_tag				iterator_category;
			typedef typename std::ptrdiff_t								difference_type;
			typedef T*													pointer;
			typedef T&													reference;

		private:

			pointer _ptr;

		public:

			vector_iterator (pointer ptr = nullptr) : _ptr(ptr) {}
			vector_iterator (vector_iterator const& in) :_ptr(in._ptr) {}

			~vector_iterator () {}


			pointer base() const { return this->_ptr; }


			vector_iterator& operator++ () { ++this->_ptr; return *this; }
			vector_iterator& operator-- (){ --this->_ptr; return *this; }

			vector_iterator operator++ (int) { vector_iterator tmp(*this); ++this->_ptr; return tmp; }
			vector_iterator operator-- (int) { vector_iterator tmp(*this); --this->_ptr; return tmp; }

            bool operator==(const vector_iterator& in) const    { return (in._ptr == this->_ptr); }
            bool operator!=(const vector_iterator& in) const    { return (in._ptr != this->_ptr); }
            bool operator<(const vector_iterator& in) const     { return (in._ptr > this->_ptr); }
            bool operator>(const vector_iterator& in) const     { return (in._ptr < this->_ptr); }
            bool operator<=(const vector_iterator& in) const    { return (in._ptr >= this->_ptr); }
            bool operator>=(const vector_iterator& in) const    { return (in._ptr <= this->_ptr); }

			vector_iterator operator+ (int const nb) const
			{
				vector_iterator ret(*this);
				return ret._ptr += nb;
			}

			vector_iterator operator- (int const nb) const
			{
				vector_iterator ret(*this);
				return ret._ptr -= nb;
			}

			difference_type operator-(vector_iterator const & in)
			{
				return this->_ptr - in._ptr;
			}

			reference operator* () const { return *this->_ptr; }
			reference operator[] (int i) const { return this->_ptr[i]; }
			pointer operator-> () const { return &(this->operator*()); }

			vector_iterator &operator= (const vector_iterator& in) { _ptr = in._ptr; return *this; }
			vector_iterator &operator+= (int i) { _ptr += i; return *this; }
			vector_iterator &operator-= (int i) { _ptr -= i; return *this; }

			friend vector_iterator operator+ (int const nb, vector_iterator const & in)
			{
				vector_iterator ret(in);
				return ret._ptr += nb;
			}
			friend vector_iterator operator- (int const nb, vector_iterator const & in)
			{
				vector_iterator ret(in);
				return ret._ptr -= nb;
			}

			// incase we have vector we want to convert to const vector
			operator vector_iterator<const T> () const { return (vector_iterator<const T>(this->_ptr)); }

	};

	template < typename T>
	typename ft::iterator_traits<T>::difference_type operator- (const ft::vector_iterator<T> first, const ft::vector_iterator<T> second)
	{
		return (first.base() - second.base());
	}
	template < typename T, typename U >
	typename ft::iterator_traits<T>::difference_type operator- (const ft::vector_iterator<T> first, const ft::vector_iterator<U> second)
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