#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "../extras/bstree.hpp"


namespace ft
{
	template <typename T>
	class node;


	template <typename T, typename Pointer = typename ft::iterator<ft::bidirectional_iterator_tag, typename T::value_type>::pointer,
			typename Reference = typename ft::iterator<ft::bidirectional_iterator_tag, typename T::value_type>::reference >
	class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T >
	{
		public:

			typedef typename T::value_type																	value_type;
			typedef Pointer																					pointer;
			typedef Reference																				reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

		private:

			T * _root;

		public:

			bst_iterator (T * ptr = nullptr) : _root(ptr) {}

			bst_iterator (const bst_iterator& in) : _root(in._root) {}

			~bst_iterator () {}

			T* base() const { return this->_root; }

			bst_iterator& operator= (const bst_iterator &in) 
			{
				if (*this == in)
					return *this;
				_root = in._root;
				return *this;
			}

			bool operator== (bst_iterator const &in)
			{
				return (_root == in._root);
			}
			bool operator!= (bst_iterator const &in)
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
			
			bst_iterator& operator++ () 
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
					while (cur != nullptr && cur->child[1] == _root)
					{
						_root = cur;
						cur = _root->parent;
					}
					_root = cur;
				}
				return *this;
			}
			bst_iterator& operator-- ()
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
			bst_iterator operator++ (int)
			{
				bst_iterator tmp(*this);
				operator++();
				return tmp;
			}
			bst_iterator operator-- (int)
			{
				bst_iterator tmp(*this);
				operator--();
				return tmp;
			}

			operator bst_iterator<T, const typename T::value_type *, const typename T::value_type &> () const {return bst_iterator<T, const typename T::value_type *, const typename T::value_type &>(this->_root);} 
	};
}



#endif