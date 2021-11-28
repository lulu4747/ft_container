#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "Map.hpp"

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

	template< class T, class Compare = ft::less< T > , class key = typename T::key_type, class N = ft::node< T >
				, class T_Alloc = typename std::allocator< T >, class N_Alloc = typename std::allocator< N > >
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

		typedef typename	value_type::second_type					mapped_type;

		node_pointer			root;
		node_pointer			end;
		value_allocator_type	value_alloc;
		node_allocator_type		node_alloc;
		key_compare				comp;

		explicit rb_tree(const key_compare& compare = key_compare(), const value_allocator_type& v_alloc = value_allocator_type(),
							const node_allocator_type& n_alloc = node_allocator_type())
			:root(NULL), end(NULL), comp(compare),
			value_alloc(v_alloc),
			node_alloc(n_alloc)
		{}

		rb_tree(rb_tree const& src)
			:rb_tree()
		{
			*this = src;
		}

		virtual ~rb_tree()
		{
			clear();
		}

		rb_tree&	operator=(rb_tree const& rhs)
		{
			if (this != &rhs)
				this->copy(rhs);
			return *this;
		}

		bool	empty()
		{
			return root == NULL;
		}

		size_type	size()
		{
			return size(root);
		}

		void	clear()
		{
			if (empty())
				return ;
			if (root->left)
				clear(root->left);
			if (root->right)
				clear(root->right);
			value_alloc.destroy(root->value);
			node_alloc.destroy(root);
		}

		void	copy(rb_tree const& src)
		{
			clear();
			if (src.empty())
				return ;
			node_alloc.construct(root, *(src.root));
			if (src->left)
				root->left = copy(root->left, src->left);
			else
				root->left = NULL;
			if (src->right)
				root->right = copy(root->right, src->right);
			else
				root->right = NULL;
			return ;
		}

		bool	insert(const value_type& value)
		{
			node_pointer	new_node(root);
			node_pointer	new_parent;
			bool			side;

			if (find(value))
				return false;
			while (new_node)
			{
				new_parent = new_node;
				if (comp(value.first, new_node->value.first))
				{	new_node = new_node->left;	side = 0;}
				else
				{	new_node = new_node->right;	side = 1;}
			}
			node_alloc.construct(new_node, value);
			new_node->parent = new_parent;
			if (!side)
				new_parent->left = new_node;
			else
				new_parent->right = new_node;
			return true;
		}

		void	erase(iterator& to_remove)
		{
			node_pointer	ptr(&(*to_remove));
			node_pointer	parent(ptr->parent);
			node_pointer	child(NULL);

			if (ptr == root)
			{	_root_erase();	return;}
			if (ptr == parent->left)
			{
				if (size(ptr->left) <= size(ptr->right))
				{
					parent->left = ptr->right;
					child = ptr->left;
				}
				else if (size(ptr->right) < size(ptr->left))
				{
					parent->left = ptr->left;
					child = ptr->right;
				}
				else
					parent->left = NULL;
				parent = parent->left;
			}
			else
			{
				if (size(ptr->left) <= size(ptr->right))
				{
					parent->right = ptr->right;
					child = ptr->left;
				}
				else if (size(ptr->right) < size(ptr->left))
				{
					parent->right = ptr->left;
					child = ptr->right;
				}
				else
					parent->right = NULL;
				parent = parent->right;
			}
			value_alloc.destroy(ptr->value);
			node_alloc.destroy(ptr);
			if (child)
				_relocate(child, parent);
		}
	
	private:

		size_type	size(node_pointer ptr)
		{
			size_type	size = 0;

			if (ptr->left)
			{
				size++;
				size += size(ptr->left);
			}
			if (ptr->right)
			{
				size++;
				size += size(ptr->right);
			}
			return size;
		}

		void	clear(node_pointer ptr)
		{
			if (ptr->left)
				clear(ptr->left);
			if (ptr->right)
				clear(ptr->right);
			value_alloc.destroy(ptr->value);
			node_alloc.destroy(ptr);
		}

		node_pointer	copy(node_pointer ptr1, node_pointer ptr2)
		{
			node_alloc.construct(ptr1, *ptr2);
			if (ptr2->left)
				ptr1->left = copy(ptr1->left, ptr2->left);
			else
				ptr1->left = NULL;
			if (ptr2->right)
				ptr1->right = copy(ptr1->right, ptr2->right);
			else
				ptr1->right = NULL;
			return ptr1;
		}

		void	_root_erase();

		void	_relocate(node_pointer to_relocate, node_pointer to_compare)
		{
			if (comp(to_relocate->key(), to_compare->key()))
			{
				while (to_compare->left)
					to_compare = to_compare->left;
				to_compare->left = to_relocate;
				to_relocate->parent = to_compare;
			}
			else
			{
				while (to_compare->right)
					to_compare = to_compare->right;
				to_compare->right = to_relocate;
				to_relocate->parent = to_compare;
			}
		}

	};

}

#endif