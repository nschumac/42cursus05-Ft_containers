#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>
#include <string>


#include "../extras/pair.hpp"
#include "../extras/less.hpp"
#include "../extras/bstree.hpp"
#include "../extras/swap.hpp"
#include "../extras/lexicographical_compare.hpp"
#include "../extras/equal.hpp"

namespace ft
{



	template < class Key,
	           class T,
	           class Compare = ft::less<Key>,
	           class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:

			/*		Member Types		*/

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
					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};


			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

					/*		Iterators		*/
			typedef typename tree<value_type, value_compare>::iterator iterator;
			typedef typename tree<value_type, value_compare>::const_iterator const_iterator;
			typedef typename tree<value_type, value_compare>::reverse_iterator reverse_iterator;
			typedef typename tree<value_type, value_compare>::const_reverse_iterator const_reverse_iterator;
			typedef typename iterator::difference_type			difference_type;
					/*		Iterators		*/

			typedef size_t										size_type;

			/*		Member Types		*/

		private:

			key_compare						_keycomp;
			size_type						_size;
			allocator_type					_alloc;
			ft::tree<ft::pair<const Key, T>, value_compare, allocator_type>	_tree;
			const value_compare				_val_comp;

		public:

			/*		Constructors		*/

			explicit map (const key_compare& comp = key_compare(),
            	const allocator_type& alloc = allocator_type())
				: _keycomp(comp), _size(0), _alloc(alloc), _tree(_keycomp), _val_comp(_keycomp) {}

			template <class InputIterator>
  			map (InputIterator first, InputIterator last,
    			const key_compare& comp = key_compare(),
    			const allocator_type& alloc = allocator_type())
				: _keycomp(comp), _size(0), _alloc(alloc), _tree(_keycomp), _val_comp(_keycomp)
			{
				insert(first, last);
			}

			map (const map& x)
				: _keycomp(x._keycomp), _size(0), _alloc(x._alloc), _tree(_keycomp), _val_comp(_keycomp)
			{
				this->insert(x.begin(), x.end()); // sets size
			}

			/*		Constructors		*/

			/*		Destructor		*/

			~map () {}

			/*		Destructor		*/

			/*		Assign-Operator		*/

			map &operator= (map const & in)
			{
				_tree.clear();
				this->_size = in._size;
				this->_keycomp = in._keycomp;
				this->_alloc = in._alloc;
				const_iterator beg = in.begin();
				while (beg != in.end())
				{
					_tree.insert(*beg);
					beg++;
				}
				return *this;
			}

			/*		Assign-Operator		*/

			/*		Capacity-Functions		*/

			bool empty () const { return _size == 0; }

			size_type size () const { return _size; }

			size_type max_size () const
			{
				return _tree.max_size();
			}

			/*		Capacity-Functions		*/

			/*		Observer-Functions		*/

			key_compare	key_comp () const { return _keycomp; }

			value_compare value_comp () const { return value_compare(key_compare()); }

			/*		Observer-Functions		*/

			/*		Modifier-Functions		*/

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				iterator found = this->find(val.first);
				if (found != this->end())
					return ft::make_pair(found, false);
				_size++;
				return _tree.insert(val);
			}

			iterator insert (iterator position, const value_type& val)
			{
				return insert(val).first;
				(void)position;
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			void erase(iterator position)
			{
				if (this->find(position->first) == this->end())
					return ;
				if (_tree.remove(position.base()))
					--_size;
			}

			void erase (iterator first, iterator last)
			{
				for (; first != last;)
				{
					if(this->find(first->first) != this->end() && _tree.remove((first++).base()))
						--_size;
				}
			}

			size_type	erase (const key_type& k)
			{
				iterator found = this->find(k);
				if (found == this->end())
					return 0;
				_tree.remove(found.base());
				--_size;
				return 1;
			}

			void swap (map& x)
			{
				ft::my_swap(this->_keycomp, x._keycomp);
				ft::my_swap(this->_size, x._size);
				ft::my_swap(this->_tree, x._tree);
			}

			void clear()
			{
				this->_size = 0;
				_tree.clear();
			}

			/*		Modifier-Functions		*/

			/*		Operation-Functions		*/

			iterator find (const key_type& k)
			{
				return _tree.find(ft::make_pair(k, mapped_type()));
			}

			const_iterator find (const key_type& k) const
			{
				return _tree.find(ft::make_pair(k, mapped_type()));
			}

			size_type count (const key_type& k) const
			{
				return find(k) != end();
			}

			iterator upper_bound (const key_type& k)
			{
				iterator beg = this->begin();
				while (beg != this->end())
				{
					if (_keycomp(k, beg->first))
						return beg;
					beg++;
				}
				return beg;
			}
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator beg = this->begin();
				while (beg != this->end())
				{
					if (_keycomp(k, beg->first))
						return beg;
					beg++;
				}
				return beg;
			}
			iterator lower_bound (const key_type& k)
			{
				iterator beg = this->begin();
				while (beg != this->end())
				{
					if (!_val_comp(*beg, ft::make_pair(k, mapped_type())))
						return beg;
					beg++;
				}
				return beg;

			}
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator beg = this->begin();
				while (beg != this->end())
				{
					if (!_val_comp(*beg, ft::make_pair(k, mapped_type())))
						return beg;
					beg++;
				}
				return beg;
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			ft::pair<iterator, iterator> equal_range(const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			/*		Operation-Functions		*/

			/*		Allocator-Functions		*/

			allocator_type get_allocator() const
			{
				return this->_alloc;
			}

			/*		Allocator-Functions		*/

			/*		Element-Access-function		*/

			mapped_type &operator[](const key_type& k)
			{
				return (this->insert(ft::make_pair<key_type, mapped_type>(k, mapped_type())).first)->second;
			}

			/*		Element-Access-function		*/

			/*		Iterator-Functions		*/

			iterator begin() { return _tree.begin(); }
			iterator end() { return _tree.end(); }
			const_iterator begin() const { return const_iterator(_tree.begin()); }
			const_iterator end() const { return const_iterator(_tree.end()); }

			reverse_iterator rbegin() { return reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

			/*		Iterator-Functions		*/


			//void printtree()
			//{
			//	_tree.printTree();
			//}
	};

			/*		Relational Operators		*/

			template <class oKey, class U, class Comp, class oAlloc>
	  		bool operator== (const map<oKey, U, Comp, oAlloc>& lhs, const map<oKey, U, Comp, oAlloc>& rhs)
			{
				if (lhs.size() != rhs.size())
				  	return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}
			template <class oKey, class U, class Comp, class oAlloc>
	  		bool operator!= (const map<oKey, U, Comp, oAlloc>& lhs, const map<oKey, U, Comp, oAlloc>& rhs)
			{
				return !(operator==(lhs, rhs));
			}
			template <class oKey, class U, class Comp, class oAlloc>
	  		bool operator< (const map<oKey, U, Comp, oAlloc>& lhs, const map<oKey, U, Comp, oAlloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
			template <class oKey, class U, class Comp, class oAlloc>
	  		bool operator> (const map<oKey, U, Comp, oAlloc>& lhs, const map<oKey, U, Comp, oAlloc>& rhs)
			{
				return (rhs < lhs);
			}
			template <class oKey, class U, class Comp, class oAlloc>
	  		bool operator<= (const map<oKey, U, Comp, oAlloc>& lhs, const map<oKey, U, Comp, oAlloc>& rhs)
			{
				return !(lhs > rhs);
			}
			template <class oKey, class U, class Comp, class oAlloc>
	  		bool operator>= (const map<oKey, U, Comp, oAlloc>& lhs, const map<oKey, U, Comp, oAlloc>& rhs)
			{
				return !(lhs < rhs);
			}

			/*		Relational Operators */


	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif