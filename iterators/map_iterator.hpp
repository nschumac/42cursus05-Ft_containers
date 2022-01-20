#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "../extras/redblacktree.hpp"

namespace ft
{
	template<typename T>
	class node;

	struct bidirectional_iterator_tag {};

	template <typename T>
	class map_iterator
	{
		public:

			typedef typename T::value_type								value_type;
			typedef typename ft::random_access_iterator_tag				iterator_category;
			typedef typename std::ptrdiff_t								difference_type;
			typedef value_type*											pointer;
			typedef value_type&											reference;

		private:
			T * _root;

		public:

			map_iterator () : _root(nullptr) {}

			map_iterator (T * ptr) : _root(ptr) {}

			map_iterator (map_iterator const &in) : _root(in._root) {}

			~map_iterator () {}

			T* base() const { return this->_root; }

			map_iterator& operator= (map_iterator const &in) 
			{
				_root = in._root;
				return *this;
			}

			bool operator== (map_iterator const &in)
			{
				return (_root == in._root);
			}
			bool operator!= (map_iterator const &in)
			{
				return (_root != in._root);
			}

			reference operator* () const
			{
				return (_root->value);
			}

			pointer operator-> () const
			{
				return (&operator*());
			}
			
			map_iterator& operator++ () 
			{
				if (!_root)
					return *this;
				if (_root->child[1] != nullptr)
				{
					_root = _root->child[1];
					while (_root->child[0] != nullptr)
						_root = _root->child[0];
				}
				else
				{
					T *cur;
					cur = _root->parent;
					while (cur != nullptr &&cur->child[1] == _root)
					{
						_root = cur;
						cur = _root->parent;
					}
					_root = cur;
				}
				return *this;
			}
			map_iterator& operator-- ()
			{
				if (!_root)
					return *this;
				if (_root && _root->child[0] != nullptr)
				{
					_root = _root->child[0];
					while (_root->child[1] != nullptr)
						_root = _root->child[1];
				}
				else 
				{
					T *cur;
					cur = _root->parent;
					while (cur != nullptr && cur->child[0] == _root)
					{
						_root = cur;
						cur = _root->parent;
					}
					_root = cur;
				}
				return *this;
			}
			map_iterator operator++ (int)
			{
				map_iterator tmp(*this);
				operator++();
				return tmp;
			}
			map_iterator operator-- (int)
			{
				map_iterator tmp(*this);
				operator--();
				return tmp;
			}
	};
}



#endif