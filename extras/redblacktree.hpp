#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP


namespace ft
{
	#define BLACK false
	#define RED true

	#define ISBLACK(x) (!x || x->color == BLACK)
	#define ISRED(x) (x && x->color == RED)
	#define GETDIR(x) (x->parent->child[0] == x ? 0 : 1)

	template < class T >
	class node
	{
		public:

			typedef T					value_type;

			value_type					value;
			node<T>						*parent;
			/*
			** left is 0 and right is 1
			*/
			node<T>						*child[2];
			bool						color;

			node() : value(), parent()
			{
				this->child[0] = nullptr;
				this->child[1] = nullptr;
				this->color = nullptr;
			}

			node(T value, node *parent = nullptr,
				node *child1 = nullptr, node *child2 = nullptr, bool color = RED)
				: value(value), parent(parent)
			{
				this->child[0] = child1;
				this->child[1] = child2;
				this->color = color;
			}

			node (node const & in)
			{
				*this = in;
			}

			node & operator= (node const & in)
			{
				this->value = in.value;
				this->parent = in.parent;
				this->child[0] = in.child[0];
				this->child[1] = in.child[1];
				this->color = in.color;
				return *this;
			}

			int childAmount() const
			{
				return (this->child[0] != nullptr) + (this->child[1] != nullptr);
			}

			bool hasTwoChild() const
			{
				return this->childAmount() == 2;
			}
	};


	template <class T, class Compare, class Alloc>
	class tree
	{
		public:

		//	typedef map_iterator<T>									iterator;
		//	typedef map_iterator<const T>							const_iterator;

			typedef Alloc											allocator_type;
			typedef typename Alloc::template rebind<node<T> >::other	node_allocator_type;

			typedef Compare											compare_type;
			typedef node<T>											node_type;

		private:

			node_allocator_type	_nodealloc;
			node_type			*_root;
			compare_type		_keyComp;

			/*
			** prints tree in a form
			*/
			void	print(const std::string& prefix, node<T>* x, bool isleft) const
			{
				if (x)
				{
					std::cout << prefix;
					std::cout << (isleft ? "├──" : "└──");
					std::cout << x->value.first << (x->color == BLACK ? " black" : " red" ) << std::endl;
					print(prefix + (isleft ? "│   " : "    "), x->child[0], true);
					print(prefix + (isleft ? "│   " : "    "), x->child[1], false);
				}
			}

			/*
			** Searches for Element value
			** if it cannot find element it returns the parent of the position
			** returns nullptr if tree has no elements
			*/
			node<T>	*find(T const &p)
			{
				node<T>	*cur = this->_root;
				bool	dir;
				if (!cur)
					return nullptr;
				while (true)
				{
					// found element
					if (p == cur->value)
						return cur;
					else if (_keyComp(p, cur->value))
						dir = false;
					else
						dir = true;
					// element doesnt exist yet
					// returns parent here
					if (cur->child[dir] == nullptr)
						return cur;
					cur = cur->child[dir];
				}
			}

			/*
			** constructs new node with allocator
			*/
			node<T>	*createNode(T const & p)
			{
				node<T> *ret = this->_nodealloc.allocate(1);
				ret->parent = nullptr;
				ret->child[0] = nullptr;
				ret->child[1] = nullptr;
				ret->color = RED;
				allocator_type alloc(this->_nodealloc);
				alloc.construct(&ret->value, p);
				return ret;
			}

			/*
			** destroys and deallocates node
			*/
			void	destroyNode(node<T> *node)
			{
				allocator_type alloc(this->_nodealloc);
				alloc.destroy(&node->value);
				this->_nodealloc.deallocate(node);
			}

			/*
			** rotates tree at specific root
			** dir specifies either left or right rotation
			*/
			void	rotate(node<T> *p, int dir)
			{
				node<T> *g = p->parent;
				node<T> *s = p->child[1 - dir];
				node<T> *c;

				c = s->child[dir];
				p->child[1 - dir] = c;
				if (c != nullptr)
					c->parent = p;
				s->child[dir] = p;
				p->parent = s;
				s->parent = g;
				if (g != nullptr)
					g->child[p == g->child[0] ? 0 : 1] = s;
				else
					this->_root = s;
			}

			/*
			** fixes tree so that after insertion the rules still hold
			*/
			void	fix_treeInsert(node<T> *cur)
			{
				do {
					node<T> *p = cur->parent;

					/*
					** parent is black means cur stays red and nothing needs to change
					*/

					if (ISBLACK(p))
						return ;

					/*
					** parent is red so violation of two red nodes in a row
					*/

					node<T> *g = p->parent;
					if (!g)
					{
						/*
						** grandpa doesnt exist p is root
						** set root to BLACK
						*/

						p->color = BLACK;
						return;
					}

					int dir = GETDIR(p);
					node<T> *u = g->child[1 - dir];
					if (ISBLACK(u))
					{
						/*
						** parent is red and uncle is BLACK
						*/

						if (p->child[1 - dir] == cur)
						{
							/*
							** -> setup is either left right or right left
							** -> rotate to make tree left left or right right
							** switch positions of parent with new child / cur
							*/
						
							rotate(p, dir);
							cur = p;
							p = g->child[dir];
						}
						/*
						** tree is setup so that 
						** newnode and parent are either left left or right right
						*/
						rotate(g, 1 - dir);
						p->color = BLACK;
						g->color = RED;
						return ;
					}

					/*
					** uncle is RED and parent as well
					** -> color swap
					*/
					if (ISRED(p) && ISRED(u))
					{
						p->color = BLACK;
						u->color = BLACK;
						g->color = RED;
					}

					/*
					** Iterate to next red level
					*/
					cur = g;
				} while (cur->parent != nullptr);
				/*
				** set root BLACK
				*/
				cur->color = BLACK;
			}

			/*
			** finds successor of a certain node
			** successor is the smallest node that is bigger than current node
			** ONLY CALL WITH NODE THAT HAS CHILD
			*/
			node<T> *findSuccessor(node<T> *node)
			{
				node = node->child[1];
				while (node->child[0])
					node = node->child[0];
				return node;
			}

			/*
			** shifts node n2 into positon of n1
			*/
			void shift(node<T> *n1, node<T> *n2)
			{
				if (n1->parent == nullptr)
					this->_root = n2;
				else if (n1 == n1->parent->child[0])
					n1->parent->child[0] = n2;
				else
					n1->parent->child[1] = n2;
				if (n2 != nullptr)
					n2->parent = n1->parent;
			}


			/*
			** if node is not the root and colored black with no children
			** this case is used
			*/
			void complex_removal(node<T> *cur)
			{
				/*
				** since it is not root it has a parent
				*/
				node<T> *p = cur->parent;
				int dir = GETDIR(cur);

				/*
				** remove the child directly
				*/
				p->child[dir] = nullptr;

				node<T> *s;
				node<T> *d;
				node<T> *c;
				do
				{
					s = p->child[1 - dir];
					d = s->child[1 - dir];
					c = s->child[dir];
					if (ISRED(s) || ISRED(d) || ISRED(c) || ISRED(p))
						break;
					/*
					** s+d+c+p+node is black
					*/
					s->color = RED;
					cur = p;
					if (!cur->parent)
						return ;
					p = cur->parent;
					dir = GETDIR(cur);
				} while (true);

				/*
				** if parent is red 
				** compensate by setting sibling to parent to black
				*/
				if (ISRED(p))
				{
					s->color = RED;
					p->color = BLACK;
					return;
				}

				if (ISRED(s) && ISBLACK(c) && ISBLACK(d))
				{
					rotate(p, dir);
					p->color = RED;
					s->color = BLACK;
					s = c;
					d = s->child[1 - dir];
					c = s->child[dir];
					if (!ISRED(d) && !ISRED(c))
					{
						s->color = RED;
						p->color = BLACK;
					}
				}

				if (ISRED(c) && ISBLACK(s) && ISBLACK(d))
				{
					rotate(s, 1 - dir);
					s->color = RED;
					c->color = BLACK;
					d = s;
					s = c;
				}

				if (ISRED(d) && ISBLACK(s))
				{
					rotate(p, dir);
					s->color = p->color;
					p->color = BLACK;
					d->color = BLACK;
				}
			}


			/*
			** romoves node from tree
			*/
			void remove_node(node<T> *cur)
			{
				if (cur->parent != nullptr && ISBLACK(cur) && cur->childAmount() == 0)
				{
					complex_removal(cur);
					return ;
				}

				/*
				** if node is root and only node in tree
				*/
				if (cur->parent == nullptr && cur->childAmount() == 0)
					return ;

				/*
				** node has two children
				** -> find successor and switch them
				*/
				if (cur->hasTwoChild())
				{
					node<T> *successor = findSuccessor();
					T tmp = successor->value;
					successor->value = cur->value;
					cur->value = tmp;
					cur = successor;
				}
				/*
				** node now has one child or non
				** this can be shifted up to replace the node
				** if node is red it has no child 
				** if black it has one
				*/

				if (ISRED(cur))
				{
					shift(cur, nullptr);
					return ;
				}

				/*
				** node is black and must have one child
				*/
				int child = 0;
				if (cur->child[1])
					child = 1;
				/*
				** shift child up to correct position
				*/
				shift(cur, cur->child[child]);

				/*
				** set color to original color
				*/
				cur->child[child]->color = cur->color;
			}


		public:

			explicit tree (Compare keyComp = Compare(), Alloc alloc = Alloc())
				: _nodealloc(alloc), _root(nullptr), _keyComp(keyComp)  {}

			tree (T p, Compare keyComp = Compare(), Alloc alloc = Alloc())
				: _nodealloc(alloc), _root(nullptr), _keyComp(keyComp)
			{
				insert(p);
			}

			void	insert(T const & p)
			{
				node<T>	*pos = find(p);
				node<T> *newnode = createNode(p);
				if (pos == nullptr)
					this->_root = newnode;
				else
				{
					pos->child[!_keyComp(p, pos->value)] = newnode;
					newnode->parent = pos;
				}
				fix_treeInsert(newnode);
			}

			bool	remove(T const &p)
			{
				/*
				** finds either the node or the parent of where it would be
				** if nullptr is returned it means there are no nodes
				*/
				node<T> *pos = find(p);

				if (pos == nullptr || pos->value != p)
					return false;
				remove_node(pos);
				destroyNode(pos);
				return true;
			}

			void printTree()
			{
				print("", this->_root, false);
			}

	};
	


}




#endif