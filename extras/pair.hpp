#ifndef PAIR_HPP
# define PAIR_HPP

#include "enable_if.hpp"
namespace ft
{

	template <class T1, class T2>
	class pair
	{
		public:

			typedef T1			first_type;
			typedef T2			second_type;

			first_type	first;
			second_type	second;

		public:

			pair() : first(), second() {}

			template <class U, class V>
			pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

			pair (const first_type& a, const second_type& b) : first(a), second(b) {}

			~pair () {}

			pair& operator= (const pair& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return *this;
			}

	};

			template <class first, class second>
			bool operator== (const ft::pair<first, second>& lhs, const ft::pair<first, second>& rhs)
			{
				return (lhs.first == rhs.first && lhs.second == rhs.second);
			}
			template <class first, class second>
			bool operator!= (const ft::pair<first, second>& lhs, const ft::pair<first, second>& rhs)
			{
				return !(lhs == rhs);
			}
			template <class first, class second>
			bool operator< (const ft::pair<first, second>& lhs, const ft::pair<first, second>& rhs)
			{
				return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
			}
			template <class first, class second>
			bool operator<= (const ft::pair<first, second>& lhs, const ft::pair<first, second>& rhs)
			{
				return !(rhs<lhs);
			}
			template <class first, class second>
			bool operator> (const ft::pair<first, second>& lhs, const ft::pair<first, second>& rhs)
			{
				return rhs<lhs;
			}
			template <class first, class second>
			bool operator>= (const ft::pair<first, second>& lhs, const ft::pair<first, second>& rhs)
			{
				return !(lhs<rhs);
			}

	template <class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 x1, T2 x2)
	{
		return (ft::pair<T1, T2> (x1, x2));
	}

}


#endif