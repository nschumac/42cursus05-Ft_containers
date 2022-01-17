#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>
#include <string>

#include "../extras/pair.hpp"
#include "../extras/less.hpp"
#include "../extras/redblacktree.hpp"

namespace ft
{



	template < class Key,                                     // map::key_type
	           class T,                                       // map::mapped_type
	           class Compare = ft::less<Key>,                     // map::key_compare
	           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
	           > 
	class map
	{
		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare										key_compare;

			struct value_compare : ft::binary_function <value_type, value_type, bool>
			{
				private:
					friend class map;
				protected:
					key_compare comp;
				public:
					value_compare (key_compare c) : comp(c) {}
					bool operator() (const value_type& x, const value_type& y) { return comp(x.first, y.first); }
			};


			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			// ITERATOR
			//typedef typename rbtree<ft::pair<Key,T>, value_compare>::iterator iterator;
			//typedef typename rbtree<ft::pair<Key,T>, value_compare>::const_iterator const_iterator;
			//typedef typename iterator::difference_type			difference_type;
			typedef size_t										size_type;
			//ITERATOR


		private:

			key_compare						_keycomp;
			size_type						_size;
			allocator_type					_alloc;	
			ft::tree<ft::pair<const Key, T>, value_compare, allocator_type>	_tree;

		public:
			explicit map (const key_compare& comp = key_compare(),
            	const allocator_type& alloc = allocator_type())
				: _keycomp(comp), _size(0), _alloc(alloc), _tree(_keycomp) {}

			template <class InputIterator>
  			map (InputIterator first, InputIterator last,
    			const key_compare& comp = key_compare(),
    			const allocator_type& alloc = allocator_type())
			{

			}

			map (const map& x)
			{

			}

			bool empty () const { return _size == 0; }

			size_type size () const { return _size; }

			size_type max_size () const { return _alloc.max_size(); }

			key_compare	keycomp () const { return _keycomp; }
			
			value_compare valcomp () const { return value_compare(key_compare()); }

			void insert (ft::pair<Key, T> const & p)
			{
				_tree.insert(p);
				_size++;
			}

			// size_type	erase (const key_type& k)
			// {
			// 	if (_tree->remove(ft::pair<Key, T>(k, 0)) && --_size)
			// 		return 1;
			// 	return 0;
			// }

			void printtree()
			{
				_tree.printTree();
			}

			// iterator begin() { return iterator(_tree->getmin()); }
			// iterator end() { return iterator(nullptr); }

	};

}

#endif