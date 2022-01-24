#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "vector_iterator.hpp"

namespace ft
{
	template < class Iterator >
	class reverse_iterator
	{
		public:

			typedef Iterator														iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;

		private:

			iterator_type	_itr;

		public:

			reverse_iterator() : _itr() {}

			explicit reverse_iterator (iterator_type it) : _itr(it) {}

			template < class Iter >
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _itr(rev_it.base()) {}

			iterator_type base() const { return (iterator_type(_itr)); }

			reference operator* () const { iterator_type copy(_itr); copy--; return *copy; }

			reverse_iterator operator+ (difference_type n) const { return reverse_iterator(_itr.operator-(n)); }

			reverse_iterator& operator++ () { _itr.operator--(); return *this; }

			reverse_iterator operator++ (int) { reverse_iterator tmp(*this); ++(*this); return tmp; }

			reverse_iterator& operator+= (difference_type n) { _itr.operator-=(n); return *this; }

			reverse_iterator operator- (difference_type n) const { return reverse_iterator(_itr.operator+(n)); }

			reverse_iterator& operator-- () { _itr.operator++(); return *this; }

			reverse_iterator operator-- (int) { reverse_iterator tmp(*this); --(*this); return tmp; }

			reverse_iterator& operator-= (difference_type n) { _itr.operator+=(n); return *this; }

			pointer operator-> () const { return &(operator*()); }

			reference operator[] (difference_type n) const { return this->base()[-n - 1]; }
	};

	template < class T>
	typename ft::reverse_iterator<T>::difference_type operator- (const ft::reverse_iterator<T>& first, const ft::reverse_iterator<T>& second)
	{
		return (second.base() - first.base());
	}
	template < class T, class U >
	typename ft::reverse_iterator<T>::difference_type operator- (const ft::reverse_iterator<T>& first, const ft::reverse_iterator<U>& second)
	{
		return (second.base() - first.base());
	}
	template < class T>
	ft::reverse_iterator<T> operator+ (typename ft::reverse_iterator<T>::difference_type n, const ft::reverse_iterator<T>& second)
	{
		return (second + n);
	}
	template < class T, class U >
	bool operator== (const ft::reverse_iterator<T> first, const ft::reverse_iterator<U>& second)
	{
		return (first.base() == second.base());
	}
	template < class T, class U >
	bool operator!= (const ft::reverse_iterator<T> first, const ft::reverse_iterator<U> second)
	{
		return (first.base() != second.base());
	}
	template < class T, class U >
	bool operator< (const ft::reverse_iterator<T> first, const ft::reverse_iterator<U> second)
	{
		return (first.base() > second.base());
	}
	template < class T, class U >
	bool operator<= (const ft::reverse_iterator<T> first, const ft::reverse_iterator<U> second)
	{
		return (first.base() >= second.base());
	}
	template < class T, class U >
	bool operator> (const ft::reverse_iterator<T> first, const ft::reverse_iterator<U> second)
	{
		return (first.base() < second.base());
	}
	template < class T, class U >
	bool operator>= (const ft::reverse_iterator<T> first, const ft::reverse_iterator<U> second)
	{
		return (first.base() <= second.base());
	}
}

#endif