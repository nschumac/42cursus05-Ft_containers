#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

#include "../iterators/map_iterator.hpp"


namespace ft
{


	#define BLACK false
	#define RED true

	#define ISBLACK(x) (!x || x->_color == BLACK)
	#define ISRED(x) (x && x->_color == RED)
	#define HASNOCHILD(x) (x->_child[0] == nullptr && x->_child[1] == nullptr)
	#define HASTWOCHILD(x) (x->_child[0] != nullptr && x->_child[1] != nullptr)
	#define HASONECHILD(x) (!HASTWOCHILD(x) && !HASNOCHILD(x))
	#define GETDIR(x) ((x->_parent->_child[0] == x) ? 0 : 1)

	template < class T >
	class rbnode
	{

		public:

			typedef	T		value_type;

		public:

			value_type	_value;
			rbnode		*_parent;
			rbnode		*_child[2]; // left is 0 right is 1
			bool		_color; // false is black true is red

			rbnode(T value, rbnode *parent = nullptr,
				rbnode *child1 = nullptr, rbnode *child2 = nullptr, bool color = RED)
				:  _value(value), _parent(parent)
			{
				_child[0] = child1;
				_child[1] = child2;
				_color = color;
			}

			rbnode (rbnode const & in)
			{
				*this = in;
			}

			rbnode& operator=(rbnode const & in)
			{
				_value = in._value;
				_parent = in._parent;
				_child[0] = in._child[0];
				_child[1] = in._child[1];
				_color = in._color;
				return *this;
			}
	};

	/*
	**	RULES:
	**	Every node is red or black
	**	root is always black {not really idk }
	**	new insertions are always red
	**	every path from root-leaf has the same number of BLACK nodes
	**	NO path has two consecutive RED nodes
	**	null nodes are black {leafs mainly}
	**
	**	REBALANCE:
	**	black uncle -> Rotate {after a rotation -> nodes end up as black red red (PARENT is BLACK CHILDREN RED)}
	**	red uncle -> colorflip {after a colorflip -> nodes ned up as red black black (PARENT is RED CHILDREN BLACK)}
	**	always go from "problem CHILD" 
	*/ 
	template <class T, class Compare > 
	class rbtree {

		public:

			typedef map_iterator<T>				iterator;
			typedef map_iterator<const T>		const_iterator;

		private:

			rbnode <T>		*_root;

			Compare			_keyComp;

			void rotateDirRoot(rbnode<T> *root, int dir)
			{
				rbnode<T> *g = root->_parent;
				rbnode<T> *s = root->_child[1 - dir];
				rbnode<T> *c;

				if (s == nullptr)
					exit(-1);

				c = s->_child[dir];
				root->_child[1 - dir] = c;
				if (c != nullptr)
					c->_parent = root;
				s->_child[dir] = root;
				root->_parent = s;
				s->_parent = g;
				if (g != nullptr)
					g->_child[ root == g->_child[0] ? 0 : 1] = s;
				else
					_root = s;
			}

			void fix_tree(rbnode<T> *curnode)
			{
				do {
					rbnode<T> *p = curnode->_parent;
					if (ISBLACK(p))
						return ;
					// parent is red
					rbnode<T> *g = p->_parent;
					if (!g)
					{
						// grandpa doesnt exist p is root
						// set root to BLACK 
						p->_color = BLACK;
						return;
					}
					// p is red and g exists
					int dir = g->_child[0] == p ? 0 : 1;
					rbnode<T> *u = g->_child[1 - dir];
					// u is black p is red
					if (ISBLACK(u))
					{
						// p red u black; curnode is either left right or right left
						if (p->_child[1 - dir] == curnode)
						{
							rotateDirRoot(p, dir); // switch p with curnode
							curnode = p;
							p = g->_child[dir];
						}
						// p red u black; curnode is left left or right right
						rotateDirRoot(g, 1 - dir);
						p->_color = BLACK;
						g->_color = RED;
						return ;
					}
					// u is red p is red 
					// color swap
					if (ISRED(p) && ISRED(u))
					{
						p->_color = BLACK;
						u->_color = BLACK;
						g->_color = RED;
					}
					curnode = g;
				} while (curnode->_parent != nullptr);
				curnode->_color = BLACK;
			}

			// biggest ndoe that is smaller than current node
			rbnode<T> *tree_predecessor(rbnode<T> *node)
			{
				if (node->_child[0] != nullptr)
				{
					node = node->_child[0];
					while (node->_child[1])
						node = node->_child[1];
					return node;
				}
				return nullptr;
			}
			// smallest node that is bigger than current 
			rbnode<T> *tree_successor(rbnode<T> *node)
			{
				if (node->_child[1] != nullptr) // has right child, return most left child of this tree part
				{
					node = node->_child[1];
					while (node->_child[0])
						node = node->_child[0];
					return node;
				}
				return nullptr;
			}


			//when N is not the root, colored black and has only NIL children
			void complex_removal(rbnode<T> *node)
			{
				rbnode<T> *p = node->_parent;
				int dir = GETDIR(node);
				p->_child[dir] = nullptr;
				rbnode<T> *s;
				rbnode<T> *d;
				rbnode<T> *c;
				do {
					s = p->_child[1 - dir];
					d = s->_child[1 - dir];
					c = s->_child[dir];
					if (ISRED(s) || ISRED(d) || ISRED(c) || ISRED(p))
						break;
					
					// EVERYONE BLACK
					s->_color = RED;
					node = p;
					if (!node->_parent) // we are at root
						return;
					p = node->_parent;
					dir = GETDIR(node);
				} while (true);

				if (ISRED(p))
				{
					s->_color = RED;
					p->_color = BLACK;
					return;
				}
				if (ISRED(s) && ISBLACK(c) && ISBLACK(d))
				{
					rotateDirRoot(p, dir);
					p->_color = RED;
					s->_color = BLACK;
					s = c;
					d = s->_child[1 - dir];
					c = s->_child[dir];
					if (!ISRED(d) && !ISRED(c))
					{
						s->_color = RED;
						p->_color = BLACK;
					}
				}

				if (ISRED(c) && ISBLACK(s) && ISBLACK(d))
				{
					rotateDirRoot(s, 1 - dir);
					s->_color = RED;
					c->_color = BLACK;
					d = s;
					s = c;
				}
				if (ISRED(d) && ISBLACK(s))
				{
					rotateDirRoot(p, dir);
					s->_color = p->_color;
					p->_color = BLACK;
					d->_color = BLACK;
				}
			}

			// n1 is to remove node, n2 is the one it gets replaced with
			void shift(rbnode<T> *n1, rbnode<T> *n2)
			{
				// n1 is root
				if (n1->_parent == nullptr)
					_root = n2;
				else if (n1 == n1->_parent->_child[0]) // n1 is left child
					n1->_parent->_child[0] = n2;
				else
					n1->_parent->_child[1] = n2; // n1 is right child
				if (n2 != nullptr)
					n2->_parent = n1->_parent;
			}

			void remove_node(rbnode<T> *node)
			{
				if (node->_parent != nullptr && ISBLACK(node) && HASNOCHILD(node))
				{
					complex_removal(node);
					return ;
				}

				if (node->_parent == nullptr && HASNOCHILD(node))
				{
					_root = nullptr;
					delete node;
					return ;
				}
				// switch node and successor everything switched D:
				if (HASTWOCHILD(node))
				{
					rbnode<T> *suc = tree_successor(node);
					rbnode<T> tmp = *suc;

					suc->_color = node->_color;
					suc->_parent = node->_parent;
					suc->_parent->_child[GETDIR(node)] = suc;
					if (node->_child[1] == suc)
						suc->_child[1] = node;
					else
						suc->_child[1] = node->_child[1];
					suc->_child[0] = node->_child[0];
					suc->_child[0]->_parent = suc;
					suc->_child[1]->_parent = suc;

					if (node->_child[1] == suc)
						node->_parent = suc;
					else
						node->_parent = tmp._parent;
					node->_child[0] = nullptr;
					node->_child[1] = tmp._child[1];
					if (node->_child[1])
						node->_child[1]->_parent = node;
					// now node has one child
				}

				// has one or no children just shift it up
				if (ISRED(node))
				{
					node->_parent->_child[GETDIR(node)] = nullptr;
					delete node;
					return ;
				}
				else
				{
					if (node->_child[0])
					{
						shift(node, node->_child[0]);
						node->_child[0]->_color = node->_color;
					}
					else
					{
						shift(node, node->_child[1]);
						if (node->_child[1])
							node->_child[1]->_color = node->_color;
					}
				}
			}

			// print tree with keys
			void shit(rbnode<T> *root, int space)
			{
    			if (root == NULL)
    			    return;
    			space += 10;
    			shit(root->_child[0], space);
    			std::cout<<std::endl;
    			for (int i = 10; i < space; i++)
    			    std::cout<<" ";
    			std::cout<<root->_value.first<<"\n";
    			shit(root->_child[1], space);
			}
			// print tree with red and blue tags
			void shit2(rbnode<T> *root, int space)
			{
    			if (root == NULL)
    			    return;
    			space += 10;
    			shit2(root->_child[0], space);
    			std::cout<<std::endl;
    			for (int i = 10; i < space; i++)
    			    std::cout<<" ";
				std::string bruh = (root->_color ? "R" : "B");
    			std::cout << bruh << "\n";
				shit2(root->_child[1], space);
			}
			
			void	print(const std::string& prefix, rbnode<T>* x, bool isLeft) const
			{
				if (x)
				{
					std::cout << prefix;
					std::cout << (isleft ? "├──" : "└──");
					std::cout << x->_value.first << (x->_color == black ? " black" : " red" ) << std::endl;
					print(prefix + (isleft ? "│   " : "    "), x->_child[0], true);
					print(prefix + (isleft ? "│   " : "    "), x->_child[1], false);
				}
			}

		public:

			// print tree as rb and keys
			void printRBTree()
			{
				shit(_root, 0);
				std::cout << "----------------------------------------------";
				shit2(_root, 0);
			}
			
			rbtree (Compare keyComp) : _root(nullptr), _keyComp(keyComp) {}
			rbtree (T p, Compare keyComp)
			{
				_root = new rbnode<T>(p);
				_keyComp = keyComp;
			}
			// iterates through tree and finds correct position
			// then fixes the current tree os Red Black is given
			// see rules above
			void	insert(T const & p)
			{
				rbnode <T> *cur = _root;
				bool rl = false;
				if (!cur) // input if no node in tree
				{
					_root = new rbnode <T> (p);
					_root->_color = BLACK;
					return ;
				}
				while (true)
				{
					if (_keyComp(p, cur->_value)) // new key is smaller than cur(parent)
						rl = false; //left
					else
						rl = true; //right
					if (cur->_child[rl] == nullptr)
					{
						cur->_child[rl] = new rbnode <T> (p, cur);
						fix_tree(cur->_child[rl]);
						return;
					}
					cur = cur->_child[rl];
				}
			}

			bool	remove(T p)
			{
				rbnode <T> *cur = _root;
				bool	rl = false;

				while (cur)
				{
					if (_keyComp(p, cur->_value)) // new key is smaller than cur(parent)
						rl = false; //left
					else
						rl = true; //right
					if (cur->_value.first == p.first)
					{
						remove_node(cur);
						return true;
					}
					cur = cur->_child[rl];
				}
				return false;
			}

			rbnode<T> *getmin()
			{
				rbnode<T> *ret = _root;
				while (ret && ret->_child[0])
					ret = ret->_child[0];
				return ret;
			}
	};

}

#endif