#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "algorithm.hpp"
# include "ft.hpp"
# include "Map.hpp"
# include "Iterator.hpp"

namespace	ft
{

	template< class T >
	struct node
	{

		typedef	struct		node*						pointer;
		typedef	struct		node&						reference;
		typedef				T							value_type;
		typedef				value_type*					value_pointer;

		typedef	typename	value_type::first&			key_type;

		pointer			parent;
		pointer			left;
		pointer			right;
		value_pointer	value;

		explicit node(reference src_value = value_type(),
			pointer const& src_parent = NULL, pointer const& src_left = NULL, pointer const& src_right = NULL)
		:
			parent(src_parent),
			left(src_left),
			right(src_right),
			value(src_value)
		{}

		node(node const & src)
		{
			*this = src;
		}

		virtual ~node();

		reference	operator=(node const & rhs)
		{
			if (this != &rhs)
			{
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				value = rhs.value;
			}
			return *this;
		}

		key_type	key() const
		{
			return value->first;
		}

		bool	operator==(node const & rhs) const
		{
			return (*value == *(rhs.value));
		}

		bool	operator!=(node const & rhs) const
		{
			return !(*value == *(rhs.value));
		}
	};

	template< class T, class Compare = ft::less< T > , class T_Alloc = typename std::allocator< T >,
					class key = typename T::key_type, class N = ft::node< T >, class N_Alloc = typename std::allocator< N > >
	struct rb_tree
	{
		typedef				T												value_type;
		typedef 			T_Alloc											value_allocator_type;
		typedef				N												node_type;
		typedef 			node_type*										node_pointer;
		typedef 			N_Alloc											node_allocator_type;

		typedef 			Compare											key_compare;
		typedef				key												key_type;
		typedef				size_t											size_type;
	
		typedef				Binary_Search_Tree_Iterator<node_type>			iterator;
		typedef				Binary_Search_Tree_Iterator<const node_type>	const_iterator;

		typedef typename	value_type::second_type							mapped_type;

		node_pointer			root;
		value_allocator_type	value_alloc;
		node_allocator_type		node_alloc;
		key_compare				comp;

/*
			**		Construction		**
*/

		explicit rb_tree(const key_compare& compare = key_compare(), const value_allocator_type& v_alloc = value_allocator_type(),
							const node_allocator_type& n_alloc = node_allocator_type())
			:root(NULL), comp(compare),
			value_alloc(v_alloc),
			node_alloc(n_alloc)
		{}

		rb_tree(rb_tree const& src)
			:rb_tree()
		{
			*this = src;
		}

		rb_tree&	operator=(rb_tree const& rhs)
		{
			if (this != &rhs)
				this->_copy(rhs);
			return *this;
		}

		void	copy(rb_tree const& src)
		{
			clear();
			if (src.empty())
				return ;
			node_alloc.construct(root, *(src.root));
			root->parent = NULL;
			if (src->left)
				root->left = _copy(root->left, src->left, root);
			else
				root->left = NULL;
			if (src->right)
				root->right = _copy(root->right, src->right, root);
			else
				root->right = NULL;
			return ;
		}

/*
			**		destruction		**
*/

		virtual ~rb_tree()
		{
			clear();
		}

		void	clear()
		{
			if (empty())
				return ;
			if (root->left)
				_clear(root->left);
			if (root->right)
				_clear(root->right);
			value_alloc.destroy(root->value);
			node_alloc.destroy(root);
		}

/*
			**		infos		**
*/

		bool	empty()
		{
			return root == NULL;
		}

		size_type	size()
		{
			return _size(root);
		}

		size_type	count(const key_type& k) const
		{
			if (_find(k))
				return 1;
			return 0;
		}

/*
			**		Iterators		**
*/

		iterator	begin()
		{
			iterator	it(_min());

			return it;
		}

		const_iterator	begin() const
		{
			const_iterator	it(_min());

			return it;
		}

		iterator	end()
		{
			iterator	it(NULL);

			return it;
		}

		const_iterator	end() const
		{
			const_iterator	it(NULL);

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
			value_type*		new_val;

			if (ptr)
				return ptr->value.second;
			value_alloc(new_val, value_type(k, mapped_type()));
			insert(*new_val);
			return new_val->second;
		}

/*
			**		Modifiers		**
*/

		bool	insert(const value_type& value)
		{
			node_pointer	new_node(root);
			node_pointer	new_parent(NULL);
			bool			is_left;

			if (_find(value.first))
				return false;
			while (new_node)
			{
				new_parent = new_node;
				is_left = comp(value.first, new_node->value.first);
				new_node = is_left ? new_node->left : new_node->right;
			}
			return _node_init(new_node, value, new_parent, is_left);
		}

		void	erase(iterator& to_remove)
		{
			node_pointer	ptr(&(*to_remove));
			node_pointer	parent(ptr->parent);
			node_pointer	orphan(NULL);

			if (ptr == root)
			{	_root_erase();	return;}
			if (!ptr->left && !ptr->right)
				ptr == parent->left ? parent->left = NULL : parent->right = NULL;
			else
			{
				bool			is_left((!ptr->right || _size(ptr->right) < _size(ptr->left))); // verify after implementing proper balance (size comp might have no impact at all)
				node_pointer	tmp(is_left ? ptr->left : ptr->right);

				ptr == parent->left ?
					parent->left = tmp : parent->right = tmp;
				orphan = is_left ? ptr->right : ptr->left;
			}
			value_alloc.destroy(ptr->value);
			node_alloc.destroy(ptr);
			_relink(orphan);
		}
	
	private:

/*
			**		copy() helper		**
*/

		node_pointer	_copy(node_pointer ptr1, node_pointer ptr2, node_pointer parent)
		{
			node_alloc.construct(ptr1, *ptr2);
			ptr1->parent = parent;
			if (ptr2->left)
				ptr1->left = _copy(ptr1->left, ptr2->left, ptr1);
			else
				ptr1->left = NULL;
			if (ptr2->right)
				ptr1->right = _copy(ptr1->right, ptr2->right, ptr1);
			else
				ptr1->right = NULL;
			return ptr1;
		}

/*
			**		clear() helper		**
*/

		void	_clear(node_pointer ptr)
		{
			if (ptr->left)
				_clear(ptr->left);
			if (ptr->right)
				_clear(ptr->right);
			value_alloc.destroy(ptr->value);
			node_alloc.destroy(ptr);
		}

/*
			**		size() helper		**
*/

		size_type	_size(node_pointer ptr)
		{
			size_type	size(1);

			if (!ptr)
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

			if (ptr)
			{
				for(bool bl(comp(k, ptr.first)); ptr && bl != comp(ptr.first, k); bl = comp(k, ptr.first))
					ptr = bl ? ptr->left : ptr->right;
			}
			return ptr;
		}

/*
			**		insert() helper		**
*/

		bool _node_init(node_pointer new_node, const value_type& value, node_pointer new_parent, bool is_left = 0)
		{
			if (!new_parent)
			{
				node_alloc.construct(root, value);
				root->parent = NULL;
				root->left = NULL;
				root->right = NULL;
			}
			else
			{
				node_alloc.construct(new_node, value);
				new_node->left = NULL;
				new_node->right = NULL;
				new_node->parent = new_parent;
				if (is_left)
					new_parent->left = new_node;
				else
					new_parent->right = new_node;
			}
			return true;
		}

/*
			**		erase() helper		**
*/

		void	_root_erase();

		void	_relink(node_pointer orphan)
		{
			node_pointer	parent(NULL);
			node_pointer	ptr(root);
			bool			is_left = 0;

			if (!orphan || !ptr)
				return ;
			while (ptr)
			{
				parent = ptr->parent;
				is_left = comp(orphan->value.first, ptr->value.first);
				ptr = is_left ? ptr->left : ptr->right;
			}
			orphan->parent = parent;
			is_left ? parent->left = orphan : parent->right = orphan;
		}

/*
			**		Iterators helper		**
*/

		node_pointer	_min()
		{
			node_pointer	ptr(root);

			while(ptr && ptr->left)
				ptr = ptr->left;
			return ptr;
		}

	};

}

#endif