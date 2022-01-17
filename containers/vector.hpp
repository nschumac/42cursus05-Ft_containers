#ifndef	VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>

#include "../iterators/vector_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../extras/enable_if.hpp"

namespace ft
{

	template < typename T, class Allocator = std::allocator<T> >
	class vector
	{

		public:

			typedef T												value_type;

			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::size_type				size_type;

			typedef typename ft::vector_iterator<value_type>		iterator;
			typedef typename ft::vector_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:

			pointer					_vector;
			allocator_type			_alloc;
			size_type				_capacity;
			size_type				_size;

			void reallocate (size_type size)
			{
				if (size > this->max_size())
					throw std::length_error("size to big");
				pointer tmp = _alloc.allocate(size);
				for (size_type i = 0; i < this->_size; ++i)
					_alloc.construct(&tmp[i], _vector[i]);
				size_type sizetmp = this->_size;
				this->~vector();
				this->_size = sizetmp;
				this->_capacity = size;
				this->_vector = tmp;
			}

		public:

			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc) , _capacity(0), _size(0)
			{
				this->_vector = this->_alloc.allocate(this->_capacity);
			}

			explicit vector (size_type n, const value_type & val = value_type(),
					const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(n), _size(n)
			{
				this->_vector = this->_alloc.allocate(this->_capacity);

				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.construct(&this->_vector[i], val);
			}

			vector (const vector& in) : _alloc(in._alloc), _capacity(in._capacity), _size(in._size)
			{
				this->_vector = this->_alloc.allocate(this->_capacity);

				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.construct(&this->_vector[i], in._vector[i]);
			}

			template < class InputIterator >
			vector (InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0,
					const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				this->_capacity = ft::distance(first, last);
				this->_size = this->_capacity;

				this->_vector = this->_alloc.allocate(this->_capacity);

				for (size_type pos = 0; first != last; pos++, first++)
					this->_alloc.construct(&this->_vector[pos], *first);
			}

			iterator begin () { return iterator(this->_vector); }
			iterator end () { return iterator(&this->_vector[this->_size]); }
			const_iterator begin () const { return const_iterator(&this->_vector[0]); }
			const_iterator end () const { return const_iterator(&this->_vector[this->_size]); }
			
			reverse_iterator rbegin () { return reverse_iterator(&this->_vector[this->_size]); }
			reverse_iterator rend () { return reverse_iterator(&this->_vector[0]); }
			const_reverse_iterator rbegin () const { return const_reverse_iterator(&this->_vector[this->_size]); }
			const_reverse_iterator rend () const { return const_reverse_iterator(&this->_vector[0]); }

			allocator_type get_allocator () { return this->_alloc; }
			size_type size () const { return this->_size; }
			size_type max_size () const { return this->_alloc.max_size(); }
			size_type capacity () const { return this->_capacity; }
			bool empty () const { return this->_size == 0; }

			void resize (size_type n, value_type val = value_type())
			{
				size_type tmp_size = this->_size;
				if (n < this->_size)
				{
					for (size_type i = n; i < this->_size; i++)
						this->_alloc.destroy(&this->_vector[i]);
					this->_size = n;
				}
				else if (n > this->_capacity)
				{
					reallocate(n);
					this->_size = tmp_size;
					for (size_type i = this->_size; i < n + this->_size; ++i)
						this->_alloc.construct(&this->_vector[i], val);
				}
				else if (n > this->_size)
				{
					for (size_type i = this->_size; i < n + this->_size; ++i)
						this->_alloc.construct(&this->_vector[i], val);
				}
				this->_size = n;	
			}

			void reserve (size_type n)
			{
				if (n > this->_capacity)
					reallocate(n);
			}

			reference operator[] (size_type n) { return this->_vector[n]; }
			const_reference operator[] (size_type n) const { return this->_vector[n]; }

			reference at (size_type n)
			{
				if (n < 0 || n >= this->_size)
					throw std::out_of_range("Vec idx is out of range");
				return this->_vector[n];
			}

			const_reference at (size_type n) const
			{
				if (n < 0 || n >= this->_size)
					throw std::out_of_range("Vec idx is out of range");
				return this->_vector[n];
			}
			
			reference front() { return this->_vector[0]; }
			const_reference front() const { return this->_vector[0]; }
			reference back() { return this->_vector[_size - 1]; }
			const_reference back() const { return this->_vector[_size - 1]; }


			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0)
			{
				typename InputIterator::difference_type diff = ft::distance(first, last);
				resize(diff);
				for (size_type i = 0; i < this->_size; i++, first++)
					this->_vector[i] = *first;
			}

			void assign (size_type n, const value_type& val)
			{
				resize(n);
				for (size_type i = 0; i < this->_size; i++)
					this->_vector[i] = val;
			}

			void push_back (const value_type& val)
			{
				size_type org_size = this->_size;
				if (this->_size + 1 > this->_capacity)
					resize(this->_capacity <= 0 ? 1 : this->_capacity * 2);
				this->_size = org_size;
				this->_alloc.construct(&this->_vector[this->_size], val);
				this->_size++;
			}

			void pop_back ()
			{
				this->_alloc.destroy(&this->back());
				this->_size--;
			}

			void clear ()
			{
				for (;this->_size > 0 ; --this->_size)
					this->_alloc.destroy(&_vector[this->_size - 1]);
			}

			iterator insert (iterator position, const value_type& value)
			{
				typename iterator::difference_type diff = ft::distance(this->begin(), position);
				resize(++this->_size);

				value_type tmp1 = value;
				value_type tmp2;

				for (value_type tmp = static_cast<value_type>(diff); tmp < static_cast<typename iterator::difference_type>(this->_size); tmp++)
				{
					tmp2 = this->_vector[tmp];
					this->_vector[tmp] = tmp1;
					tmp1 = tmp2;
				}
				return &this->_vector[diff];
			}

			void insert (iterator position, size_type n, const value_type& value)
			{
				typename iterator::difference_type diff = ft::distance(iterator(_vector), position);
				resize(this->_size + n);

				ft::vector<value_type> tmp;
				for (size_type i = diff; i < this->_size; i++)
					tmp.push_back(this->_vector[i]);
				n += diff;
				for (; diff < static_cast<typename iterator::difference_type>(n); diff++)
					this->_vector[diff] = value;
				for (size_type i = 0; i < tmp.size(); i++, diff++)
					this->_vector[diff] = tmp[i];
			}

			template < class InputIterator >
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0)
			{
				typename iterator::difference_type diff = ft::distance(iterator(_vector), position);
				typename iterator::difference_type n = ft::distance(first, last);
				resize(this->_size + n);
				ft::vector<value_type> tmp;
				for (size_type i = diff; i < this->_size; i++)
					tmp.push_back(this->_vector[i]);
				for (; first != last; diff++, first++)
					this->_vector[diff] = *first;
				for (size_type i = 0; i < tmp.size(); i++, diff++)
					this->_vector[diff] = tmp[i];
			}

			iterator erase (iterator position)
			{
				iterator posp1 = position;
				posp1++;
				for (iterator cop = position; cop != this->end(); cop++, posp1++)
					if (posp1 != this->end())
						*cop = *posp1;
				this->_size--;
				return position;
			}

			iterator erase (iterator first, iterator last)
			{
				typename iterator::difference_type diff = ft::distance(first, last);

				for (iterator i1 = first, it2 = last; it2 != this->end(); it2++, i1++)
					*i1 = *it2;
				this->_size = this->_size - diff;
				return first;
			}

			void swap (vector & in)
			{
				pointer buf = in._vector;
				size_type sizebuf = in._size;
				size_type capacitybuf = in._capacity;
				in._vector = this->_vector;
				in._size = this->_size;
				in._capacity = this->_capacity;
				this->_vector = buf;
				this->_size = sizebuf;
				this->_capacity = capacitybuf;
			}


			vector& operator= (const vector& in)
			{
				resize(in._size);
				iterator cur = this->begin();
				for (const_iterator it = in.begin(); it != in.end(); it++, cur++)
				{
					*cur = *it;
				}
				return (*this);
			}

			~vector()
			{
				clear();
			}

			template <class U, class Alloc>
	  		friend bool operator== (const vector<U,Alloc>& lhs, const vector<U,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
				  	return false;
				for (const_iterator first = lhs.begin(), second = rhs.begin(); first != lhs.end(); first++, second++)
					if (*first != *second)
						return false;
				return true;
			}
			template <class U, class Alloc>
	  		friend bool operator!= (const vector<U,Alloc>& lhs, const vector<U,Alloc>& rhs)
			{
				return !(operator==(lhs, rhs));
			}
			template <class U, class Alloc>
	  		friend bool operator< (const vector<U,Alloc>& lhs, const vector<U,Alloc>& rhs)
			{
				const_iterator first = lhs.begin(), second = rhs.begin();
				for (; first != lhs.end(); first++, second++)
				{
					if (*first < *second)
						return true;
					else if (*first > *second || second == rhs.end())
						return false;
				}
				return second != rhs.end();
			}
			template <class U, class Alloc>
	  		friend bool operator> (const vector<U,Alloc>& lhs, const vector<U,Alloc>& rhs)
			{
				return (rhs < lhs);
			}
			template <class U, class Alloc>
	  		friend bool operator<= (const vector<U,Alloc>& lhs, const vector<U,Alloc>& rhs)
			{
				return !(lhs > rhs);
			}
			template <class U, class Alloc>
	  		friend bool operator>= (const vector<U,Alloc>& lhs, const vector<U,Alloc>& rhs)
			{
				return !(lhs < rhs);
			}
	};

}

#endif