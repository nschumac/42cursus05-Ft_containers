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

		protected:

			container_type	c;

		public:

			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}

			bool empty () const { return c.empty(); }

			size_type size () const { return c.size(); }

			value_type& top () { return c.back(); }

			const value_type& top () const { return c.back(); }

			void push (const value_type& val) { c.push_back(val); }

			void pop () { c.pop_back(); }

			template <class tn, class containern>
			friend bool operator== (const stack<tn, containern>& lhs, const stack<tn, containern>& rhs);
			template <class tn, class containern>
			friend bool operator!= (const stack<tn, containern>& lhs, const stack<tn, containern>& rhs);
			template <class tn, class containern>
			friend bool operator< (const stack<tn, containern>& lhs, const stack<tn, containern>& rhs);
			template <class tn, class containern>
			friend bool operator<= (const stack<tn, containern>& lhs, const stack<tn, containern>& rhs);
			template <class tn, class containern>
			friend bool operator> (const stack<tn, containern>& lhs, const stack<tn, containern>& rhs);
			template <class tn, class containern>
			friend bool operator>= (const stack<tn, containern>& lhs, const stack<tn, containern>& rhs);
	};

		template <class Tn, class ContainerN>
 		bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
  		{
  			return lhs.c == rhs.c;
		}
  
  		template <class Tn, class ContainerN>
  		bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
  		{
  			return lhs.c != rhs.c;
  		}
  		
  		template <class Tn, class ContainerN>
  		bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
  		{
  			return lhs.c < rhs.c;
  		}
  
  		template <class Tn, class ContainerN>
  		bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
  		{
  			return lhs.c <= rhs.c;
  		}
  
  		template <class Tn, class ContainerN>
  		bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
  		{
  			return lhs.c > rhs.c;
  		}
  
  		template <class Tn, class ContainerN>
  		bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs)
  		{
  			return lhs.c >= rhs.c;
  		}
  }
  
  #endif