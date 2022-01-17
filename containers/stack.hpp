#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:

			typedef T									value_type;
			typedef Container							container_type;
			typedef typename container_type::size_type	size_type;

		private:

			container_type	_ctnr;

		public:

			explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {}

			bool empty () const { return _ctnr.empty(); }

			size_type size () const { return _ctnr.size(); }

			value_type& top () { return _ctnr.back(); }

			const value_type& top () const { return _ctnr.back(); }

			void push (const value_type& val) { _ctnr.push_back(val); }

			void pop () { _ctnr.pop_back(); }

			template <class Tn, class ContainerN>
			friend bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
			{
				return lhs._ctnr == rhs._ctnr;
			}

			template <class Tn, class ContainerN>
			friend bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
			{
				return lhs._ctnr != rhs._ctnr;
			}
			
			template <class Tn, class ContainerN>
			friend bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
			{
				return lhs._ctnr < rhs._ctnr;
			}

			template <class Tn, class ContainerN>
			friend bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
			{
				return lhs._ctnr <= rhs._ctnr;
			}

			template <class Tn, class ContainerN>
			friend bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
			{
				return lhs._ctnr > rhs._ctnr;
			}

			template <class Tn, class ContainerN>
			friend bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
			{
				return lhs._ctnr >= rhs._ctnr;
			}
	};
}

#endif