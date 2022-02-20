#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>
# include "node.hpp"
# include "../Iterators/Binary_Search_Tree_Iterator.hpp"
# include "../functionnal.hpp"

namespace	ft
{
	namespace
	{
		template< class T, class Compare = ft::less< T > , class T_Alloc = typename std::allocator< T >,
					typename N = ft::node< T >, class N_Alloc = typename std::allocator< N > >
		class rb_tree
		{

		public :

			typedef				T												key_type;
			typedef				N												node_type;
			typedef 			T_Alloc											value_allocator_type;
			typedef 			N_Alloc											node_allocator_type;
			typedef	typename	value_allocator_type::pointer					pointer;
			typedef	typename	value_allocator_type::const_pointer				const_pointer;
			typedef typename	node_allocator_type::pointer					node_pointer;
			typedef typename	node_allocator_type::const_pointer				const_node_pointer;

			typedef 			Compare											key_compare;
			typedef				size_t											size_type;
		
			typedef				Binary_Search_Tree_Iterator<node_type>			iterator;
			typedef				Binary_Search_Tree_Iterator<const node_type>	const_iterator;

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
				_end_node->nill = true;
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
				return iterator(_root->leftmost());
			}

			const_iterator	begin() const
			{
				return const_iterator(_root->leftmost());
			}

			iterator	end()
			{
				return iterator(_end_node);
			}

			const_iterator	end() const
			{
				return const_iterator(_end_node);
			}

			iterator	find(const key_type& k)
			{
				return iterator(_find(k));
			}

			const_iterator	find(const key_type& k) const
			{
				return const_iterator(_find(k));
			}

			iterator	lower_bound(const key_type& k)
			{
				iterator		it(begin());
				iterator		end(this->end());

				while (it != end)
				{
					if (!(_comp((*it).first, k)))
						break;
					it++;
				}
				return it;
			}

			const_iterator	lower_bound(const key_type& k)	const
			{
				return const_iterator(lower_bound(k));
			}

			iterator	upper_bound(const key_type& k)
			{
				iterator		it(begin());
				iterator		end(this->end());

				while (it != end)
				{
					if (_comp(k, (*it).first))
						break;
					it++;
				}
				return it;
			}

			const_iterator	upper_bound(const key_type& k)	const
			{
				return const_iterator(upper_bound(k));
			}

			ft::pair< iterator, iterator >
			equal_range(const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			ft::pair< const_iterator, const_iterator >
			equal_range(const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

	/*
				**		Modifiers		**
	*/

			bool	insert(pointer value)
			{
				if (empty())
					return _balance(_root_init(value));
				return _balance(_insert(value));
			}

			void	erase(iterator to_remove)
			{
				node_pointer	ptr(_find(to_remove->first));

				if (ptr == _end_node->left)
					_end_node->left = _inorder_successor(ptr);
				if (ptr == _end_node->right)
					_end_node->right = _inorder_predecessor(ptr);
				if (ptr == _root)
					_root_erase();
				else
				{
					if (ptr->left != _end_node && ptr->right != _end_node)
						_swap_places(ptr, _inorder_successor(ptr));
					_node_erase(ptr);
				}
				return ;
			}

			void	swap(rb_tree &x)
			{
				node_pointer			tmp_root(_root);
				node_pointer			tmp_end_node(_end_node);
				key_compare				tmp_comp(_comp);
				value_allocator_type	tmp_value_alloc(_value_alloc);
				node_allocator_type		tmp_node_alloc(_node_alloc);

				_root =			x.get_root();
				_end_node =		x.get_end_node();
				_comp =			x.get_comp();
				_value_alloc =	x.get_value_allocator();
				_node_alloc =	x.get_node_allocator();

				x._root =			tmp_root;
				x._end_node =		tmp_end_node;
				x._comp =			tmp_comp;
				x._value_alloc =	tmp_value_alloc;
				x._node_alloc =		tmp_node_alloc;
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

			key_compare	get_comp()	const
			{
				return	_comp;
			}

			value_allocator_type	get_value_allocator()	const
			{
				return	_value_alloc;
			}

			node_allocator_type	get_node_allocator()	const
			{
				return	_node_alloc;
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

				if (ptr == _end_node)
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
				bool			is_less;

				while (ptr != _end_node)
				{
					if ((is_less = _comp(k, ptr->key())) == _comp(ptr->key(), k))
						return ptr;
					if (is_less == true)
						ptr = ptr->left;
					else
						ptr = ptr->right;
				}
				return ptr;
			}

	/*
				**		balancing functions		**
	*/

			void	_left_rotate(node_pointer ptr)
			{
				node_pointer	new_parent(ptr->right);

				if (ptr->red != new_parent->red)
				{
					ptr->red = !ptr->red;
					new_parent->red = !new_parent->red;
				}
				new_parent->parent = ptr->parent;
				if (ptr->parent == _end_node)
					_root = new_parent;
				else
					ptr->is_left_child() ? ptr->parent->left = new_parent : ptr->parent->right = new_parent;
				ptr->right = new_parent->left;
				ptr->right->parent = ptr;
				ptr->parent = new_parent;
				new_parent->left = ptr;
			}

			void	_right_rotate(node_pointer ptr)
			{
				node_pointer	new_parent(ptr->left);

				if (ptr->red != new_parent->red)
				{
					ptr->red = !ptr->red;
					new_parent->red = !new_parent->red;
				}
				new_parent->parent = ptr->parent;
				if (ptr->parent == _end_node)
					_root = new_parent;
				else
					ptr->is_left_child() ? ptr->parent->left = new_parent : ptr->parent->right = new_parent;
				ptr->left = new_parent->right;
				ptr->left->parent = ptr;
				ptr->parent = new_parent;
				new_parent->right = ptr;
			}

			void	_rr_del(node_pointer parent, node_pointer sibling)
			{
				sibling->right->red = false;
				_left_rotate(parent);
			}

			void	_rl_del(node_pointer parent, node_pointer sibling)
			{
				_right_rotate(sibling);
				_left_rotate(parent);
			}

			void	_ll_del(node_pointer parent, node_pointer sibling)
			{
				sibling->left->red = false;
				_right_rotate(parent);
			}

			void	_lr_del(node_pointer parent, node_pointer sibling)
			{
				_left_rotate(sibling);
				_right_rotate(parent);
			}

			bool	_ll_insert(node_pointer ptr)
			{
				_right_rotate(ptr->grandparent());

				return true;
			}

			bool	_lr_insert(node_pointer ptr)
			{
				_left_rotate(ptr->parent);
				return _ll_insert(ptr->left);
			}

			bool	_rr_insert(node_pointer ptr)
			{
				_left_rotate(ptr->grandparent());
				return true;
			}

			bool	_rl_insert(node_pointer ptr)
			{
				_right_rotate(ptr->parent);
				return _rr_insert(ptr->right);
			}

			void	_no_sibling_case(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				ptr->double_black = false;
				if (parent->red == false)
				{
					if (parent != _root)
					{
						parent->double_black = true;
						sibling = parent->is_left_child() ? parent->parent->right : parent->parent->left;
						return _balance(parent, parent->parent, sibling);
					}
					else
					{
						ptr->red = true;
						return;
					}
				}
				parent->red = false;
				return;
			}

			void	_black_sibling_case(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				if (sibling->left->red || sibling->right->red)
				{
					if (sibling->is_left_child())
					{
						if (sibling->left->red)
							_ll_del(parent, sibling);
						else
							_lr_del(parent, sibling);
					}
					else
					{
						if (sibling->right->red)
							_rr_del(parent, sibling);
						else
							_rl_del(parent, sibling);
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
							sibling = parent->is_left_child() ? parent->parent->right : parent->parent->left;
						return _balance(parent, parent->parent, sibling);
					}
					else
						parent->red = false;
				}
				return ;
			}

			void	_red_sibling_case(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				if (parent == _root)
					_root = sibling;
				parent->red = true;
				sibling->red = false;
				if (sibling->is_left_child())
				{
					_right_rotate(parent);
					sibling = parent->left;
				}
				else
				{
					_left_rotate(parent);
					sibling = parent->right;
				}
				return _balance(ptr, parent, sibling);
			}

			void	_balance(node_pointer ptr, node_pointer parent, node_pointer sibling)
			{
				if (ptr != _root)
				{
					if (sibling == _end_node)
						return _no_sibling_case(ptr, parent, sibling);
					else if (sibling->red == false)
						_black_sibling_case(ptr, parent, sibling);
					else
						return _red_sibling_case(ptr, parent, sibling);
				}
				ptr->double_black = false;
				return ;
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
						return _ll_insert(ptr);
					else if (grandparent->left != _end_node && ptr == grandparent->left->right)
						return _lr_insert(ptr);
					else if (grandparent->right != _end_node && ptr == grandparent->right->right)
						return _rr_insert(ptr);
					return _rl_insert(ptr);
				}
				return true;
			}

	/*
				**		insert() helper		**
	*/

			node_pointer	_root_init(pointer value)
			{
				_root = _node_alloc.allocate(1);
				_node_alloc.construct(_root, node_type(value, _end_node, _end_node, _end_node));
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

				_node_alloc.construct(new_node, node_type(value, _end_node->left, _end_node, _end_node));
				parent->left = new_node;
				_end_node->left = new_node;
				return new_node;
			}

			node_pointer	_new_rightmost(pointer value)
			{
				node_pointer	parent(_end_node->right);
				node_pointer	new_node(_node_alloc.allocate(1));

				_node_alloc.construct(new_node, node_type(value, _end_node->right, _end_node, _end_node));
				parent->right = new_node;
				_end_node->right = new_node;
				return new_node;
			}

			node_pointer _node_init(pointer value, node_pointer new_parent, bool is_left = 0)
			{
				node_pointer	new_node(_node_alloc.allocate(1));

				_node_alloc.construct(new_node, node_type(value, new_parent, _end_node, _end_node));
				if (is_left)
					new_parent->left = new_node;
				else
					new_parent->right = new_node;
				return new_node;
			}

	/*
				**		erase() helper		**
	*/

			node_pointer	_inorder_successor(node_pointer ptr)
			{
				if (ptr == _end_node)
					return ptr->left;
				if (ptr->right != _end_node)
				{
					ptr = ptr->right;
					while (ptr->left != _end_node)
						ptr = ptr->left;
				}
				else
				{
					node<T>	*prev(ptr);

					while (ptr != _end_node && prev != ptr->left)
					{
						prev = ptr;
						ptr = ptr->parent;
					}
				}
				return ptr;
			}

			node_pointer	_inorder_predecessor(node_pointer ptr)
			{
				if (ptr == _end_node)
					ptr = ptr->right;
				else if (ptr->left != _end_node)
				{
					ptr = ptr->left;
					while (ptr->right != _end_node)
						ptr = ptr->right;
				}
				else
				{
					node_pointer	prev(ptr);

					while (ptr != _end_node && prev != ptr->right)
					{
						prev = ptr;
						ptr = ptr->parent;
					}
				}
				return ptr;
			}

			void	_root_erase()
			{
				if (_root->left != _end_node || _root->right != _end_node)
				{
					node_pointer	tmp(_root);

					if (_root->right != _end_node)
						_swap_places(_root, _inorder_successor(_root));
					else
						_swap_places(_root, _inorder_predecessor(_root));
					_node_erase(tmp);
				}
				else
					clear();
				return ;
			}

			void	_node_erase(node_pointer ptr)
			{
				node_pointer	parent(ptr->parent);
				node_pointer	balancer(_end_node);
				node_pointer	sibling;

				if (ptr == _root)
					return _root_erase();
				sibling = ptr->is_left_child() ?
					parent->right : parent->left;
				if (ptr->left == _end_node && ptr->right == _end_node)
				{
					ptr->is_left_child() ? parent->left = _end_node : parent->right = _end_node;
					if (parent->red == true)
						parent->red = false;
					else if (ptr->red == false)
						balancer->double_black = true;
				}
				else
				{
					balancer = ptr->left != _end_node ?
						ptr->left : ptr->right;
					ptr->is_left_child() ?
						parent->left = balancer : parent->right = balancer;
					balancer->parent = parent;
					if (ptr->red == false && balancer->red == false)
						balancer->double_black = true;
					else
						balancer->red = false;
				}
				_node_remover(ptr);
				if (balancer->double_black == true)
					_balance(balancer, parent, sibling);
				return ;
			}

			void	_swap_places(node_pointer np1, node_pointer np2)
			{
				node_type	tmp(*np1);

				if (np1 == np2)
					return ;
				if (np1->parent != _end_node)
					np1->is_left_child() ? np1->parent->left = np2 : np1->parent->right = np2;
				if (np2->parent != _end_node)
					np2->is_left_child() ? np2->parent->left = np1 : np2->parent->right = np1;
				if (np1 != _end_node)
					np1->parent = np2->parent;
				np1->left = np2->left != np1 ? np2->left : np2;
				if (np1->left != _end_node)
					np1->left->parent = np1;
				np1->right = np2->right != np1 ? np2->right : np2;
				if (np1->right != _end_node)
					np1->right->parent = np1;
				np1->red = np2->red;
				if (np2 != _end_node)
					np2->parent = tmp.parent;
				np2->left = tmp.left != np2 ? tmp.left : np1;
				if (np2->left != _end_node)
					np2->left->parent = np2;
				np2->right = tmp.right != np2 ? tmp.right : np1;
				if (np2->right != _end_node)
					np2->right->parent = np2;
				np2->red = tmp.red;
				if (_root == np1)
					_root = np2;
				else if (_root == np2)
					_root = np1;
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
