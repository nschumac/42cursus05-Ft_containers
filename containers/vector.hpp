#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <cstddef>


namespace fd
{

	template<typename T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference      	reference;
    	typedef typename allocator_type::const_reference	const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        //iterator typs need to be made
        //
        //here
		typedef typename allocator_type::size_type      	size_type;

		int	_n;
		
    private:
        allocator_type _alloc;
        pointer _vector;
        size_type _capacity;
        size_type _size;

	public:
		/*
		** CONSTRUCTORS
		*/
		vector();
		
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
                const allocator_type& alloc = allocator_type());
		
		/*
		** CONSTRUCTORS
		*/


        // Capacity
        size_type size () const { return this->_size; }

        size_type max_size () const { return this->_alloc.max_size(); }

        size_type capacity () const { return this->_capacity; }

        void resize (size_type n, value_type val = value_type());

        bool empty () const { return (this->_size == 0) }



        //Element access
        
        reference operator[] (size_type n) { return this->_vector[n] }

        const_reference operator[] (size_type n) const { return this->_vector[n] }

        reference at (size_type n)
        {
            if (size_type < 0 || size_type >= this->_size)
                throw std::out_of_range("Vec idx is out of range");
            return this->vector[n];
        }

        const_reference at (size_type n) const
        {
            if (size_type < 0 || size_type >= this->_size)
                throw std::out_of_range("Vec idx is out of range");
            return this->vector[n];
        }

        reference front() { return this->_vector[0] }

        const_reference front() const { return this->_vector[0] }

        reference back() { return this->_vector[_size - 1] }

        const_reference back() const { return this->_vector[_size - 1] }


        // Modifiers

        template <class InputIterator>
            void assign (InputIterator first, InputIterator last);

        void assign (size_type n, const value_type& val);



        vector& operator=(const vector& in);
		


		~vector()
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(&_vector[i]);
        }
	};
} // namespace fd

#endif

