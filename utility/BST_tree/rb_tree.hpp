#ifndef RB_TREE_HPP
# define RB_TREE_HPP

//
# include <iostream>
//

# include <memory>
# include "node.hpp"
# include "../functionnal.hpp"
# include "../Iterators/Binary_Search_Tree_Iterator.hpp"

namespace	ft
{
	namespace
	{
		template< class T, class Compare = ft::less< T > , class T_Alloc = typename std::allocator< T >,
						class key = typename T::first_type, typename N = ft::node< T >, class N_Alloc = typename std::allocator< N > >
		class rb_tree
		{

		public :

			typedef				T												value_type;
			typedef				N												node_type;
			typedef 			T_Alloc											value_allocator_type;
			typedef 			N_Alloc											node_allocator_type;
			typedef	typename	value_allocator_type::pointer					pointer;
			typedef	typename	value_allocator_type::const_pointer				const_pointer;
			typedef typename	node_allocator_type::pointer					node_pointer;
			typedef typename	node_allocator_type::const_pointer				const_node_pointer;

			typedef 			Compare											key_compare;
			typedef				key												key_type;
			typedef				size_t											size_type;
		
			typedef				Binary_Search_Tree_Iterator<node_type>			iterator;
			typedef				Binary_Search_Tree_Iterator<const node_type>	const_iterator;

			typedef typename	value_type::second_type							mapped_type;

	/*
				**		Construction		**
	*/

			explicit rb_tree(const key_compare& compare = key_compare(), const value_allocator_type& v_alloc = value_allocator_type(),
								const node_allocator_type& n_alloc = node_allocator_type())
				:_comp(compare),
				_value_alloc(v_alloc),
				_node_alloc(n_alloc)
			{
				_end_node = _node_alloc.allocate(1);
				_node_alloc.construct(_end_node, node_type());
				_root = _end_node;
				_end_node->right = _end_node;
				_end_node->left = _end_node;
				_end_node->parent = _end_node;
				_end_node->red = false;
			}

			rb_tree(rb_tree const& src):rb_tree()
			{
				*this = src;
			}

			rb_tree&	operator=(rb_tree const& rhs)
			{
				if (this != &rhs)
					this->copy(rhs);
				return *this;
			}

			void	copy(rb_tree const& src)
			{
				pointer	new_val;

				if (!(empty()))
					clear();
				_comp = src.get_comp();
				_value_alloc = src.get_value_allocator();
				_node_alloc = src.get_node_allocator();
				if (!(src.empty()))
					_copy(src.get_root());
				return ;
			}

	/*
				**		destruction		**
	*/

			virtual ~rb_tree()
			{
				clear();
				_node_alloc.destroy(_end_node);
				_node_alloc.deallocate(_end_node, 1);
			}

			void	clear()
			{
				if (empty())
					return ;
				if (_root->left != _end_node)
					_clear(_root->left);
				if (_root->right != _end_node)
					_clear(_root->right);
				_node_remover(_root);
				_root = _end_node;
				_end_node->right = _end_node;
				_end_node->left = _end_node;
				_end_node->parent = _end_node;
			}

	/*
				**		infos		**
	*/

			bool	empty() const
			{
				return _root == _end_node;
			}

			size_type	size() const
			{
				return _size(_root);
			}

			size_type	max_size() const
			{
				return _node_alloc.max_size();
			}

			size_type	count(const key_type& k) const
			{
				if (_find(k) != _end_node)
					return 1;
				return 0;
			}

	/*
				**		Iterators		**
	*/

			iterator	begin()
			{
				iterator	it(_end_node->left);

				return it;
			}

			const_iterator	begin() const
			{
				const_iterator	it(_end_node->left);

				return it;
			}

			iterator	end()
			{
				iterator	it(_end_node);

				return it;
			}

			const_iterator	end() const
			{
				const_iterator	it(_end_node);

				return it;
			}

			iterator	find(const key_type& k)
			{
				iterator	pos(_find(k));

				return pos;
			}

			const_iterator	find(const key_type& k) const
			{
				const_iterator	pos(_find(k));

				return pos;
			}

			iterator	lower_bound(const key_type& k)	const
			{
				iterator		it(begin());
				iterator		ite(end());

				while (it != ite && _comp(k, (*it).first))
					it++;
				return it;
			}

			iterator	upper_bound(const key_type& k)	const
			{
				iterator		it(begin());
				iterator		ite(end());

				while (it != ite && !_comp((*it).first), k)
					it++;
				return it;
			}

	/*
				**		ElementAccess		**
	*/

			mapped_type&	operator[](const key_type& k)
			{
				node_pointer	ptr(_find(k));
				value_type*		new_val(NULL);

				if (ptr != _end_node)
					return ptr->value->second;
				new_val = _value_alloc.allocate(sizeof(value_type));
				_value_alloc.construct(new_val, make_pair(k, mapped_type()));
				insert(new_val);
				return new_val->second;
			}

	/*
				**		Modifiers		**
	*/

			bool	insert(pointer value)
			{
				if (_find(value->first) != _end_node)
					return false;
				if (empty())
					return _balance(_root_init(value));
				return _balance(_insert(value));
			}

			void	erase(iterator to_remove)
			{
				node_pointer	ptr(node_accessor(to_remove).get_node());

				if (ptr == _root)
					_root_erase();
				else
				{
					if (to_remove == _end_node->left)
						_end_node->left = to_remove->right != _end_node ? to_remove->parent : to_remove->parent->right;
					if (to_remove == _end_node->right)
						_end_node->right = to_remove->left != _end_node ? to_remove->parent : to_remove->left;
					if (to_remove->left != _end_node && to_remove->right != _end_node)
						_swap_places(to_remove, to_remove->inorder_successor());
					_node_erase(to_remove);
				}
				return ;
			}

	/*
				**		get Functions		**
	*/

			node_pointer	get_end_node()	const
			{
				return	_end_node;
			}

			node_pointer	get_root()	const
			{
				return	_root;
			}

			node_pointer	get_comp()	const
			{
				return	_comp;
			}

			node_pointer	get_value_allocator()	const
			{
				return	_value_alloc;
			}

			node_pointer	get_node_allocator()	const
			{
				return	_node_alloc;
			}

			void	tmp() const																								//LA
			{
				std::cout << _size(_root->left) << "	|	" << _size(_root->right) << std::endl;
			}

		private:

	/*
				**		private attributes		**
	*/

			node_pointer			_end_node;
			node_pointer			_root;
			key_compare				_comp;
			value_allocator_type	_value_alloc;
			node_allocator_type		_node_alloc;

			class node_accessor : Binary_Search_Tree_Iterator< node_type >
			{
				friend	class	rb_tree< value_type, key_compare, value_allocator_type, key_type, node_type, node_allocator_type >;

				protected :

					node_accessor(Binary_Search_Tree_Iterator< node_type > const & src)
						:Binary_Search_Tree_Iterator< node_type >(src)
					{}

					node_pointer	get_node()
					{
						return Binary_Search_Tree_Iterator< node_type >::_ptr;
					}
			};

	/*
				**		clear() helper		**
	*/

			void	_clear(node_pointer ptr)
			{
				if (ptr->left != _end_node)
					_clear(ptr->left);
				if (ptr->right != _end_node)
					_clear(ptr->right);
				_node_remover(ptr);
			}

	/*
				**		size() helper		**
	*/

			size_type	_size(node_pointer ptr) const
			{
				size_type	size(1);

				if (!ptr->value)
					return 0;
				size += _size(ptr->left);
				size += _size(ptr->right);
				return size;
			}

	/*
				**		find() helper		**
	*/

			node_pointer	_find(const key_type& k)	const
			{
				node_pointer	ptr(_root);
				bool			is_left;

				while (ptr != _end_node)
				{
					if ((is_left = _comp(k, ptr->key())) == _comp(ptr->key(), k))
						return ptr;
					if (is_left)
						ptr = ptr->left;
					else
						ptr = ptr->right;
				}
				return ptr;
			}

	/*
				**		copy() helper		**
	*/

			void	_copy(node_pointer	src)
			{
				pointer	new_val(_value_alloc.allocate(1));

				_value_alloc.construct(new_val, make_pair(src->key(), src->value->second));
				_root_init(new_val);
				if (src->left != src.get_end_node())
					_root->left = _copy(_root, src->left);
				if (src->right != src.get_end_node())
					_root->right = _copy(_root, src->right);
				_end_node->left = _root->leftmost();
				_end_node->right = _root->rightmost();
				return ;
			}

			node_pointer	_copy(node_pointer parent, node_pointer src)
			{
				node_pointer	new_node(_node_alloc.allocate(1));
				pointer			new_val(_value_alloc.allocate(1));

				_value_alloc.construct(new_val, make_pair(src->key(), src->value->second));
				_node_alloc.construct(new_node, node_type(new_val));
				new_node->parent = parent;
				new_node->left = src->left->value ?
					_copy(new_node, src->left) : _end_node;
				new_node->right = src->right->value ?
					_copy(new_node, src->right) : _end_node;
				return new_node;
			}

	/*
				**		balancing functions		**
	*/
/**/
			void	_balance(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				if (ptr != _root)
				{
					if (sibling == _end_node)
					{
						if (parent->red == false)
						{
							ptr->double_black = false;
							parent->double_black = true;
							if (parent != _root)
								sibling = parent == parent->parent->left ? parent->parent->right : parent->parent->left;
							return _balance(parent, parent->parent, sibling);
						}
						parent->red = false;
					}
					else if (sibling->red == false)
					{
						if (sibling->left->red || sibling->right->red)
						{
							if (sibling == parent->right)
							{
								if (sibling->right->red)
									_rr_del(ptr, parent, sibling);
								else
									_rl_del(ptr, parent, sibling);
							}
							else
							{
								if (sibling->left->red)
									_ll_del(ptr, parent, sibling);
								else
									_lr_del(ptr, parent, sibling);
							}
						}
						else
						{
							sibling->red = true;
							if (parent->red == false)
							{
								ptr->double_black = false;
								parent->double_black = true;
								if (parent != _root)
									sibling = parent == parent->parent->left ? parent->parent->right : parent->parent->left;
								return _balance(parent, parent->parent, sibling);
							}
							else
								parent->red = false;
						}
					}
					else
					{
						parent->red = true;
						sibling->red = false;
						if (sibling == parent->left)
						{
							sibling->right->parent = parent;
							parent->left = sibling->right;
							sibling->parent = parent->parent;
							if (parent != _root)
								parent == parent->parent->left ? parent->parent->left = sibling : parent->parent->right = sibling;
							parent->parent = sibling;
							sibling->right = parent;
						}
						else
						{
							sibling->left->parent = parent;
							parent->right = sibling->left;
							sibling->parent = parent->parent;
							if (parent != _root)
								parent == parent->parent->left ? parent->parent->left = sibling : parent->parent->right = sibling;
							parent->parent = sibling;
							sibling->left = parent;
						}
						return _balance(ptr, parent, sibling);
					}
				}
				ptr->double_black = false;
				return ;
			}

			void	_rr_del(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				sibling->right->red = false;
				sibling->parent = parent->parent;
				if (parent == _root)
					_root = sibling;
				else
					parent == parent->parent->left ? parent->parent->right = sibling : parent->parent->left = sibling;
				parent->right = sibling->left;
				sibling->left->parent = parent;
				sibling->left = parent;
				parent->parent = sibling;
			}

			void	_rl_del(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				node_pointer	red(sibling->left);

				red->red = false;
				if (red->right != _end_node)
				{
					red->right->parent = sibling;
					sibling->left = red->right;
				}
				if (red->left != _end_node)
				{
					red->left->parent = parent;
					parent->right = red->left;
				}
				red->parent = parent->parent;
				if (parent == _root)
					_root = red;
				else
					parent == parent->parent->left ? parent->parent->right = red : parent->parent->left = red;
				red->left = parent;
				parent->parent = red;
				red->right = sibling;
				sibling->parent = red;
			}

			void	_ll_del(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				sibling->left->red = false;
				sibling->parent = parent->parent;
				if (parent == _root)
					_root = sibling;
				else
					parent == parent->parent->left ? parent->parent->right = sibling : parent->parent->left = sibling;
				parent->left = sibling->right;
				sibling->right->parent = parent;
				sibling->right = parent;
				parent->parent = sibling;
			}

			void	_lr_del(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				node_pointer	red(sibling->right);

				red->red = false;
				if (red->left != _end_node)
				{
					red->left->parent = sibling;
					sibling->right = red->left;
				}
				if (red->right != _end_node)
				{
					red->right->parent = parent;
					parent->left = red->right;
				}
				red->parent = parent->parent;
				if (parent == _root)
					_root = red;
				else
					parent == parent->parent->left ? parent->parent->right = red : parent->parent->left = red;
				red->right = parent;
				parent->parent = red;
				red->left = sibling;
				sibling->parent = red;
			}

			bool	_balance(node_pointer ptr)
			{
				if (ptr == _root)
					ptr->red = false;
				else if (ptr->parent->red)
				{
					node_pointer	grandparent(ptr->grandparent());

					if (ptr->uncle()->red)
					{
						ptr->uncle()->red = false;
						ptr->parent->red = false;
						grandparent->red = true;
						return	_balance(grandparent);
					}
					else if (grandparent->left != _end_node && ptr == grandparent->left->left)
						return _ll_rotation(ptr);
					else if (grandparent->left != _end_node && ptr == grandparent->left->right)
						return _lr_rotation(ptr);
					else if (grandparent->right != _end_node && ptr == grandparent->right->right)
						return _rr_rotation(ptr);
					return _rl_rotation(ptr);
				}
				return true;
			}

			bool	_ll_rotation(node_pointer ptr)
			{
				node_pointer	grandparent(ptr->grandparent());
				bool			tmp(grandparent->red);

				_r_rotation(grandparent);
				grandparent->red = ptr->parent->red;
				ptr->parent->red = tmp;
				return _balance(ptr);
			}

			bool	_lr_rotation(node_pointer ptr)
			{
				_l_rotation(ptr->parent);
				return _ll_rotation(ptr->left);
			}

			bool	_rr_rotation(node_pointer ptr)
			{
				node_pointer	grandparent(ptr->grandparent());
				bool			tmp(grandparent->red);

				_l_rotation(grandparent);
				grandparent->red = ptr->parent->red;
				ptr->parent->red = tmp;
				return _balance(ptr);
			}
			bool	_rl_rotation(node_pointer ptr)
			{
				_r_rotation(ptr->parent);
				return _rr_rotation(ptr->right);
			}

			void	_l_rotation(node_pointer ptr)
			{
				node_pointer	right(ptr->right);

				right->parent = ptr->parent;
				if (ptr->parent != _end_node)
					ptr == ptr->parent->left ?	ptr->parent->left = right :	ptr->parent->right = right;
				else
				{
					_root = right;
					right->parent = _end_node;
				}
				if (right->left != _end_node)
					right->left->parent = ptr;
				ptr->right = right->left;
				right->left = ptr;
				ptr->parent = right;
				return ;
			}

			void	_r_rotation(node_pointer ptr)
			{
				node_pointer	left(ptr->left);

				left->parent = ptr->parent;
				if (ptr->parent != _end_node)
					ptr == ptr->parent->left ?	ptr->parent->left = left :	ptr->parent->right = left;
				else
				{
					_root = left;
					left->parent= _end_node;
				}
				if (left->right != _end_node)
					left->right->parent = ptr;
				ptr->left = left->right;
				left->right = ptr;
				ptr->parent = left;
				return ;
			}

	/*
				**		insert() helper		**
	*/

			node_pointer	_root_init(pointer value)
			{
				_root = _node_alloc.allocate(1);
				_node_alloc.construct(_root, node_type(value));
				_root->parent = _end_node;
				_root->right = _end_node;
				_root->left = _end_node;
				_end_node->left = _root;
				_end_node->right = _root;
				_end_node->parent = _root;
				return _root;
			}

			node_pointer	_insert(pointer value)
			{
				node_pointer	new_parent;
				node_pointer	ptr(_root);
				bool			is_left;
		
				if (_comp(value->first, _end_node->left->key()))
					return _new_leftmost(value);
				if (_comp(_end_node->right->key(), value->first))
					return _new_rightmost(value);
				while (ptr != _end_node)
				{
					new_parent = ptr;
					is_left = _comp(value->first, ptr->key());
					ptr = is_left ? ptr->left : ptr->right;
				}
				return _node_init(value, new_parent, is_left);
			}

			node_pointer	_new_leftmost(pointer value)
			{
				node_pointer	parent(_end_node->left);
				node_pointer	new_node(_node_alloc.allocate(1));

				_node_alloc.construct(new_node, node_type(value));
				new_node->parent = parent;
				parent->left = new_node;
				new_node->right = _end_node;
				new_node->left = _end_node;
				_end_node->left = new_node;
				return new_node;
			}

			node_pointer	_new_rightmost(pointer value)
			{
				node_pointer	parent(_end_node->right);
				node_pointer	new_node(_node_alloc.allocate(1));

				_node_alloc.construct(new_node, node_type(value));
				new_node->parent = parent;
				parent->right = new_node;
				new_node->right = _end_node;
				new_node->left = _end_node;
				_end_node->right = new_node;
				return new_node;
			}

			node_pointer _node_init(pointer value, node_pointer new_parent, bool is_left = 0)
			{
				node_pointer	new_node(_node_alloc.allocate(1));

				_node_alloc.construct(new_node, node_type(value));
				new_node->left = _end_node;
				new_node->right = _end_node;
				new_node->parent = new_parent;
				if (is_left)
					new_parent->left = new_node;
				else
					new_parent->right = new_node;
				return new_node;
			}

	/*
				**		erase() helper		**
	*/

			void	_root_erase()
			{
				node_pointer	tmp(_root);

				if (_root->left != _end_node || _root->right != _end_node)
				{
					_swap_places(_root, _root->inorder_successor());
					_root = _root->root();
					_node_erase(tmp);
				}
				else
					clear();
				return ;
			}

			void	_node_erase(node_pointer ptr)
			{
				node_pointer	parent(ptr->parent);
				node_pointer	sibling(_end_node);
				node_pointer	balancer(_end_node);

				if (ptr->left == _end_node && ptr->right == _end_node)
				{
					ptr == parent->left ? parent->left = _end_node : parent->right = _end_node;
					if (ptr->red == false)
						balancer->double_back = true;
				}
				else
				{
					balancer = ptr->left != _end_node ?
						ptr->left : ptr->right;
					ptr == parent->left ?
						parent->left = balancer : parent->right = balancer;
					balancer->parent = parent;
					if (ptr->red == false && balancer->red == false)
						balancer->double_back = true;
					else
						balancer->red = false;
				}
				sibling = ptr == parent->left ?
					parent->right : parent->left;
				_node_remover(ptr);
				if (balancer->double_black)
					_balance(balancer, parent, sibling);
				return ;
			}

			void	_swap_places(node_pointer np1, node_pointer np2)
			{
				node_pointer	np1_parent(np1->parent);
				node_pointer	np1_left(np1->left);
				node_pointer	np1_right(np1->right);
				bool			np1_red(np1->red);

				if (np1->parent != _end_node)
					np1 == np1->parent->left ? np1->parent->left = np2 : np1->parent->right = np2;
				if (np2->parent != _end_node)
					np2 == np2->parent->left ? np2->parent->left = np1 : np2->parent->right = np1;
				np1->parent = np2->parent;
				np1->left = np2->left;
				np1->left->parent = np1;
				np1->right = np2->right;
				np1->right->parent = np1;
				np1->red = np2->red;
				np2->parent = np1_parent;
				np2->left = np1_left;
				np2->left->parent = np2;
				np2->right = np1_right;
				np2->right->parent = np2;
				np2->red = np1_red;
			}

			void	_node_remover(node_pointer ptr)
			{
				_value_alloc.destroy(ptr->value);
				_value_alloc.deallocate(ptr->value, 1);
				_node_alloc.destroy(ptr);
				_node_alloc.deallocate(ptr, 1);
			}

		};
	}
}

#endif
