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
	private:

		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference      	reference;
    	typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::size_type      	size_type;

		int	_n;
		

	public:
		/*
		** CONSTRUCTORS
		*/
		vector();
		
		vector(const allocator_type& alloc = allocator_type());
		
		vector(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type());
		
		vector(const vector& in);

		template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type());
		
		/*
		** CONSTRUCTORS
		*/





		vector& operator=(const vector& in);
		


		~vector();
	};
} // namespace fd

#endif

