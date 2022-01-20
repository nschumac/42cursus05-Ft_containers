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
			typedef typename tree<ft::pair<const Key,T>, value_compare, allocator_type>::iterator iterator;
			typedef typename tree<ft::pair<const Key,T>, value_compare, allocator_type>::const_iterator const_iterator;
			typedef typename tree<ft::pair<const Key,T>, value_compare, allocator_type>::reverse_iterator reverse_iterator;
			typedef typename tree<ft::pair<const Key,T>, value_compare, allocator_type>::const_reverse_iterator const_reverse_iterator;
			typedef typename iterator::difference_type			difference_type;
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
				: _keycomp(comp), _size(0), _alloc(alloc), _tree(_keycomp)
			{
				while (first != last)
				{
					_tree.insert(*first);
					_size++;
					first++;
				}
			}

			map (const map& x)
				: _keycomp(x._keycomp), _size(x._size), _alloc(x._alloc), _tree(_keycomp)
			{
				iterator beg = x.begin();

				while (beg != x.end())
				{
					_tree.insert(*beg);
					beg++;
				}
			}

			~map () {}

			map &operator= (map const & in)
			{
				_tree.clear();
				this->_size = in._size;
				this->_keycomp = in._keycomp;
				this->_alloc = in._alloc;
				iterator beg = in.begin();

				while (beg != in.end())
				{
					_tree.insert(beg);
					beg++;
				}
			}

			bool empty () const { return _size == 0; }

			size_type size () const { return _size; }

			size_type max_size () const { return _alloc.max_size(); }

			key_compare	key_comp () const { return _keycomp; }
			
			value_compare value_comp () const { return value_compare(key_compare()); }


			ft::pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<iterator, bool> shiiiiiat = _tree.insert(val);
				if (shiiiiiat.second == true)
					_size++;
				return shiiiiiat;
			}

			iterator insert (iterator position, const value_type& val)
			{
				return insert(val).first;
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			void erase(iterator position)
			{
				_tree.remove(*position);
			}

			void erase (iterator first, iterator last)
			{
				for (; first != last; ++first)
					_tree.remove(*first);
			}

			size_type	erase (const key_type& k)
			{
				if (_tree.remove(ft::make_pair(k, 0)) && --_size)
					return 1;
				return 0;
			}

			void swap (map& x)
			{
				map tmp(*this);
				this->_alloc = x._alloc;
				this->_keycomp = x._keycomp;
				this->_size = x._size;
				this->_tree = x._tree;
				x._size = tmp._size;
				x._keycomp = tmp._keycomp;
				x._tree = tmp._tree;
				x._alloc = tmp._alloc;
			}

			void clear()
			{
				this->_size = 0;
				_tree.clear();
			}

			iterator find (const key_type& k)
			{
				return iterator(_tree.realfind(ft::make_pair(k, 0)));
			}

			const_iterator find (const key_type& k) const
			{
				return const_iterator();
			}

			size_type count (const key_type& k) const
			{
				return find(k) != end();
			}

			

			allocator_type get_allocator() const
			{
				return this->_alloc;
			}

			void printtree()
			{
				_tree.printTree();
			}

			mapped_type &operator[](const key_type& k)
			{
				return (this->insert(ft::make_pair(k, mapped_type())).first)->second;
			}

			iterator upper_bound (const key_type& k)
			{
				return iterator();
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return const_iterator();
			}
			iterator lower_bound (const key_type& k)
			{
				return iterator(_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return const_iterator(_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			ft::pair<iterator, iterator> equal_range(const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			iterator begin() { return iterator(_tree.begin()); }
			iterator end() { return iterator(_tree.end()); }
			const_iterator begin() const { return const_iterator(_tree.begin()); }
			const_iterator end() const { return const_iterator(_tree.end()); }

			reverse_iterator rbegin() { return reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	};

}

#endif