#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template<typename T>
	class rbnode;

	struct bidirectional_iterator_tag {};

	template <typename T>
	class map_iterator
	{
		public:

			typedef T													value_type;
			typedef typename ft::random_access_iterator_tag				iterator_category;
			typedef typename std::ptrdiff_t								difference_type;
			typedef T*													pointer;
			typedef T&													reference;

		private:
			ft::rbnode<T>	*_root;

		public:

			map_iterator () : _root(nullptr) {}

			map_iterator (ft::rbnode<T> *ptr) : _root(ptr) {}

			map_iterator (map_iterator const &in) : _root(in._root) {}

			~map_iterator () {}

			ft::rbnode<T> *base() const { return this->_root; }

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
				return (_root->_value);
			}

			pointer operator-> () const
			{
				return (_root);
			}
			
			map_iterator& operator++ () 
			{
				if (_root == nullptr)
					return _root;
				if (_root->_child[1])
				{
					_root = _root->_child[1];
					while (_root->_child[0])
						_root->_child[0];
				}
				else 
				{
					if (_root->_parent->_value.first < _root->_value.first)
						return nullptr;
					_root = _root->_parent;
				}
				return _root;
			}
			map_iterator& operator-- ()
			{
				if (_root == nullptr)
					return _root;
				if (_root->_child[0])
				{
					_root = _root->_child[0];
					while (_root->_child[1])
						_root->_child[1];
				}
				else 
				{
					if (_root->_parent->_value.first < _root->_value.first)
						return nullptr;
					_root = _root->_parent;
				}
				return _root;
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
				operator++();
				return tmp;
			}
	};
}



#endif