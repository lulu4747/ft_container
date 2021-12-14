#ifndef RB_TREE_HPP
# define RB_TREE_HPP

//
# include <iostream>
//

# include <memory>
# include "node_accessor.hpp"
# include "node.hpp"
# include "../less.hpp"
# include "../Iterators/Binary_Search_Tree_Iterator.hpp"

namespace	ft
{

	template< class T, class Compare = ft::less< T > , class T_Alloc = typename std::allocator< T >,
					class key = typename T::first_type, typename N = ft::node< T >, class N_Alloc = typename std::allocator< N > >
	class rb_tree
	{

	public :

		typedef				T																					value_type;
		typedef				value_type*																			pointer;
		typedef 			T_Alloc																				value_allocator_type;
		typedef				N																					node_type;
		typedef 			node_type*																			node_pointer;
		typedef 			N_Alloc																				node_allocator_type;

		typedef 			Compare																				key_compare;
		typedef				key																					key_type;
		typedef				size_t																				size_type;
	
		typedef				Binary_Search_Tree_Iterator<node_type>/*, Compare, T_Alloc, key, N, N_Alloc>*/		iterator;
		typedef				Binary_Search_Tree_Iterator<const node_type>/*,  Compare, T_Alloc, key, N, N_Alloc>*/	const_iterator;

		typedef typename	value_type::second_type																mapped_type;

		node_pointer			end_node;
		node_pointer			root;
		key_compare				comp;
		value_allocator_type	value_alloc;
		node_allocator_type		node_alloc;

/*
			**		Construction		**
*/

		explicit rb_tree(const key_compare& compare = key_compare(), const value_allocator_type& v_alloc = value_allocator_type(),
							const node_allocator_type& n_alloc = node_allocator_type())
			:comp(compare),
			value_alloc(v_alloc),
			node_alloc(n_alloc)
		{
			end_node = node_alloc.allocate(1);
			node_alloc.construct(end_node, node_type());
			root = end_node;
			end_node->right = end_node;
			end_node->left = end_node;
		}

		rb_tree(rb_tree const& src)
			:rb_tree()
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

			clear();
			if (src.empty())
				return ;
			new_val = value_alloc.allocate(1);
			value_alloc.construct(new_val, make_pair(src.root->value->first, src.root->value->second));
			_root_init(new_val);
			if (src.root->left != src.end_node)
				_copy(src.root->left);
			if (src.root->right != src.end_node)
				_copy(src.root->right);
			return ;
		}

/*
			**		destruction		**
*/

		virtual ~rb_tree()
		{
			clear();
			node_alloc.destroy(end_node);
			node_alloc.deallocate(end_node, 1);
		}

		void	clear()
		{
			if (empty())
				return ;
			if (root->left != end_node)
				_clear(root->left);
			if (root->right != end_node)
				_clear(root->right);
			_node_remover(root);
			root = end_node;
			end_node->right = end_node;
			end_node->left = end_node;
		}

/*
			**		infos		**
*/

		bool	empty() const
		{
			return root == end_node;
		}

		size_type	size() const
		{
			return _size(root);
		}

		size_type	count(const key_type& k) const
		{
			if (_find(k) != end_node)
				return 1;
			return 0;
		}

/*
			**		Iterators		**
*/

		iterator	begin()
		{
			iterator	it(end_node->left);

			return it;
		}

		const_iterator	begin() const
		{
			const_iterator	it(end_node->left);

			return it;
		}

		iterator	end()
		{
			iterator	it(end_node);

			return it;
		}

		const_iterator	end() const
		{
			const_iterator	it(end_node);

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

		iterator	lower_bound(const key_type& k)
		{
			iterator		it(begin());
			iterator		ite(end());

			while (it != ite && comp(k, (*it).first))
				it++;
			return it;
		}

		iterator	upper_bound(const key_type& k)
		{
			iterator		it(begin());
			iterator		ite(end());

			while (it != ite && !comp((*it).first), k)
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

			if (ptr != end_node)
				return ptr->value->second;
			new_val = value_alloc.allocate(sizeof(value_type));
			value_alloc.construct(new_val, make_pair(k, mapped_type()));
			insert(new_val);
			return new_val->second;
		}

/*
			**		Modifiers		**
*/

		bool	insert(pointer value)
		{
			if (empty())
				return _root_init(value);
			if (_find(value->first) != end_node)
				return false;
			return _insert(value);
		}

		void	erase(iterator& to_remove)
		{
			node_pointer	ptr(node_accessor<node_type>(to_remove).get_node());

			if (ptr == root)
				return _root_erase();
			if (ptr == end_node->left)
				return _leftmost_erase();
			if (ptr == end_node->right)
				return _rightmost_erase();
			return _node_erase(ptr);
		}
	
	private:

/*
			**		clear() helper		**
*/

		void	_clear(node_pointer ptr)
		{
			if (ptr->left != end_node)
				_clear(ptr->left);
			if (ptr->right != end_node)
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

		node_pointer	_find(const key_type& k)
		{
			node_pointer	ptr(root);
			bool			is_left;

			while (ptr != end_node)
			{
				if ((is_left = comp(k, ptr->value->first)) == comp(ptr->value->first, k))
					return ptr;
				if (is_left)
					ptr = ptr->left;
				else
					ptr = ptr->right;
			}
			return ptr;
		}

/*
			**		insert() / copy() helper		**
*/

		void	_copy(node_pointer ptr)
		{
			pointer	new_val(value_alloc.allocate(1));

			value_alloc.construct(new_val, make_pair(ptr->value->first, ptr->value->second));
			_insert(new_val);
			if (ptr->left && ptr->left->value)
				_copy(ptr->left);
			if (ptr->right && ptr->right->value)
				_copy(ptr->right);
		}

		bool	_root_init(pointer value)
		{
			std::cout << "root_init" << std::endl;
			root = node_alloc.allocate(1);
			node_alloc.construct(root, node_type(value));
			root->parent = end_node;
			root->right = end_node;
			root->left = end_node;
			end_node->left = root;
			end_node->right = root;
			return true;
		}

		bool	_insert(pointer value)
		{
			node_pointer	new_parent;
			node_pointer	ptr(root);
			bool			is_left;
	
			if (comp(value->first, end_node->left->value->first))
				return _new_leftmost(value);
			if (comp(end_node->right->value->first, value->first))
				return _new_rightmost(value);
			while (ptr)
			{
				new_parent = ptr;
				is_left = comp(value->first, ptr->value->first);
				ptr = is_left ? ptr->left : ptr->right;
			}
			return _node_init(value, new_parent, is_left);
		}

		bool	_new_leftmost(pointer value)
		{
			node_pointer	parent(end_node->left);
			node_pointer	new_node;

			new_node = node_alloc.allocate(1);
			node_alloc.construct(new_node, node_type(value));
			new_node->parent = parent;
			parent->left = new_node;
			new_node->right = end_node;
			new_node->left = end_node;
			end_node->left = new_node;
			return true;
		}

		bool	_new_rightmost(pointer value)
		{
			node_pointer	parent(end_node->right);
			node_pointer	new_node;

			new_node = node_alloc.allocate(1);
			node_alloc.construct(new_node, node_type(value));
			new_node->parent = parent;
			parent->right = new_node;
			new_node->right = end_node;
			new_node->left = end_node;
			end_node->right = new_node;
			return true;
		}

		bool _node_init(pointer value, node_pointer new_parent, bool is_left = 0)
		{
			node_pointer	new_node;

			new_node = node_alloc.allocate(1);
			node_alloc.construct(new_node, node_type(value));
			new_node->left = end_node;
			new_node->right = end_node;
			new_node->parent = new_parent;
			if (is_left)
				new_parent->left = new_node;
			else
				new_parent->right = new_node;
			return true;
		}

/*
			**		erase() helper		**
*/

		void	_root_erase()
		{
			node_pointer	new_root;
			node_pointer	orphan;

			if (root->right == end_node && root->left == end_node)
				return clear();
			if (root->right == end_node || _size(root->right) < _size(root->left))
			{
				new_root = root->left;
				orphan = root->right;
			}
			else
			{
				new_root = root->right;
				orphan = root->left;
			}
			_node_remover(root);
			root = new_root;
			new_root->parent = end_node;
			if (!new_root->left)
				new_root->left = orphan;
			else if (!new_root->right)
				new_root->right = orphan;
			else
				_relink(orphan);
		}

		void	_leftmost_erase()
		{
			node_pointer	ptr(end_node->left);

			if (ptr->right)
			{
				ptr->parent->left = ptr->right;
				ptr->right->parent = ptr->parent;
			}
			_node_remover(ptr);
			ptr = root->leftmost();
			end_node->left = ptr;
			ptr->left = end_node;
		}

		void	_rightmost_erase()
		{
			node_pointer	ptr(end_node->right);

			if (ptr->left)
			{
				ptr->parent->right = ptr->left;
				ptr->left->parent = ptr->parent;
			}
			_node_remover(ptr);
			ptr = root->rightmost();
			end_node->right = ptr;
			ptr->right = end_node;
		}

		void	_node_erase(node_pointer ptr)
		{
			node_pointer	parent(ptr->parent);
			node_pointer	orphan(end_node);

			if (!ptr->left && !ptr->right)
				ptr == parent->left ? parent->left = end_node : parent->right = end_node;
			else
			{
				bool			is_left((ptr->right == end_node || _size(ptr->right) < _size(ptr->left))); // verify after implementing proper balance (size comp might have no impact at all)
				node_pointer	tmp(is_left ? ptr->left : ptr->right);

				ptr == parent->left ?
					parent->left = tmp : parent->right = tmp;
				orphan = is_left ? ptr->right : ptr->left;
			}
			_node_remover(ptr);
			_relink(orphan);
		}

		void	_node_remover(node_pointer ptr)
		{
			value_alloc.destroy(ptr->value);
			value_alloc.deallocate(ptr->value, 1);
			node_alloc.destroy(ptr);
			node_alloc.deallocate(ptr, 1);
		}

		void	_relink(node_pointer orphan)
		{
			node_pointer	parent;
			node_pointer	ptr(root);
			bool			is_left = 0;

			if (empty() || !orphan || orphan == end_node)
				return ;
			while (ptr)
			{
				parent = ptr->parent;
				is_left = comp(orphan->value->first, ptr->value->first);
				ptr = is_left ? ptr->left : ptr->right;
			}
			orphan->parent = parent;
			is_left ? parent->left = orphan : parent->right = orphan;
		}

	};
}

#endif
