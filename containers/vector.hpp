#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <cstddef>

#include "../iterators/vector_iterator.hpp"
#include "../iterators/reverse_vector_iterator.hpp"
#include "../extras/enable_if.hpp"

namespace ft
{

	template<typename T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

		typedef T											    value_type;
		typedef Allocator									    allocator_type;
		typedef typename allocator_type::reference      	    reference;
    	typedef typename allocator_type::const_reference	    const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;

        typedef typename ft::vector_iterator<T, false>          iterator;
        typedef typename ft::vector_iterator<T, true>           const_iterator;

        typedef typename ft::reverse_vector_iterator<T, false>          reverse_iterator;
        typedef typename ft::reverse_vector_iterator<T, true>           const_reverse_iterator;

		typedef typename allocator_type::size_type      	    size_type;

		
    private:
        allocator_type _alloc;
        pointer _vector;
        size_type _capacity;
        size_type _size;


        void reallocate (size_type size)
        {
            if (size > max_size())
                throw std::length_error("size to big");
            pointer tmp = _alloc.allocate(size);
            for (int i = 0; i < this->_size; i++)
                _alloc.construct(&tmp[i], _vector[i]);
            this->~vector();
            _capacity = size;
            _vector = tmp;
        }

	public:
		/*
		** CONSTRUCTORS
		*/
		
        // default
		explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc) , _capacity(0), _size(0)
        {
            _vector = _alloc.allocate(_capacity);
        }
		
        // fill
		explicit vector(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
        {
            _vector = _alloc.allocate(_capacity);

            for (size_type i = 0; i < _size; ++i)
                _alloc.construct(&_vector[i], val);
        }

		
        // copy constructor
		vector(const vector& in) : _alloc(in._alloc), _size(in._size), _capacity(in._capacity)
        {
            _vector = _alloc.allocate(_capacity);

            for (size_type i = 0; i < _size; ++i)
                _alloc.construct(&_vector[i], in[i]);
        }

		template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0,
                const allocator_type& alloc = allocator_type()) : _alloc(alloc)
        {
            this->_capacity = last - first;
            this->_size = _capacity;


            _vector = _alloc.allocate(_capacity);
            for (size_type i = 0; first != last; i++, first++)
                _alloc.construct(&_vector[i], *first);

        }
		
		/*
		** CONSTRUCTORS
		*/

        /*
         * Iterators
        */

        iterator begin () {return iterator(this->_vector);}
        const_iterator cbegin () { return const_iterator(this->_vector); }

        iterator end () {return iterator(&this->_vector[this->_size]);}
        const_iterator cend () { return const_iterator(&this->_vector[this->_size]); }

        reverse_iterator rbegin () { return reverse_iterator(&this->_vector[this->_size - 1]); }
        const_reverse_iterator crbegin () { return const_reverse_iterator(&this->_vector[this->_size - 1]); }

        reverse_iterator rend () { return reverse_iterator(&this->_vector[-1]); }
        const_reverse_iterator crend () { return const_reverse_iterator(&this->_vector[-1]); }
        // Capacity

        size_type size () const { return this->_size; }

        size_type max_size () const { return this->_alloc.max_size(); }

        size_type capacity () const { return this->_capacity; }

        void resize (size_type n, value_type val = value_type())
        {
            if (n < _size)
                reallocate(n);
            else if (n > _capacity)
            {
                reallocate(n);
                for (int i = _size; i < n; ++i)
                    _alloc.construct(&_vector[i], val);
            }
            else if (n > _size)
            {
                for (int i = _size; i < n; ++i)
                    _alloc.construct(&_vector[i], val);
            }
        }

        void reserve (size_type n)
        {
            if (n > _capacity)
            {
                reallocate(n);
            }
        }


        bool empty () const { return (this->_size == 0); }



        //Element access
        
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


        // Modifiers

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last);

        void assign (size_type n, const value_type& val);

        void push_back (const value_type& val)
        {
            if (_size + 1 > _capacity)
                reallocate(_capacity <= 0 ? 1 : _capacity * 2);
            _alloc.construct(&_vector[_size], val);
            _size++;
        }
            
        void pop_back ()
        {
            _alloc.destroy(&_vector[_size - 1]);
            _size--;
        }

        void clear()
        {
            for (int i = 0; i < _size; i++)
                _alloc.destroy(&_vector[i]);
            _size = 0;
        }


        iterator insert (iterator position, const value_type& value)
        {
            if (this->_size + 1 > this->_capacity)
                reallocate(this->_size + 1);

            value_type tmp;
            value_type tmp2;
            tmp2 = value;
            iterator ret = position;
            this->_size++;
            for (; position != this->end(); position++)
            {
                tmp = *position;
                _alloc.destroy(position.getPointer());
                _alloc.construct(position.getPointer(), tmp2);
                tmp2 = tmp;
            }
            return ret;
        }

        void insert (iterator position, size_type n, const value_type& value)
        {
            if (this->_size + n > this->_capacity)
                reallocate(this->_size + n);
            
            vector <value_type> tmp;
			iterator tmpitr = position;
            this->_size += n;
            for (size_type count = 0; position != this->end(); position++, count++)
            {
                tmp.push_back(*position);
                _alloc.destroy(position.getPointer());
				if (count < n)
                	_alloc.construct(position.getPointer(), value);
            }
            for (size_type i = 0; i < tmp.size() && tmpitr != this->end(); i++, tmpitr++)
            {
                _alloc.destroy(tmpitr.getPointer());
                _alloc.construct(tmpitr.getPointer(), tmp[i]);
            } 
        }

        template < class InputIterator >
		void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0)
		{

		}

        

        allocator_type get_allocator() const { return this->_alloc; }

        vector& operator=(const vector& in);
		
		~vector()
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(&_vector[i]);
        }
	};
} // namespace fd

#endif

