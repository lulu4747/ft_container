#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "Map.hpp"

namespace	ft
{

	template< class T >
	struct node
	{

		typedef	struct		node*						element;
		typedef				T							value_type;
		typedef				value_type*					pointer;
		typedef				value_type&					reference;

		element	parent;
		element	left;
		element	right;
		pointer	value;

		explicit node(reference src_value = value_type(),
			element const& src_parent = NULL, element const& src_left = NULL, element const& src_right = NULL)
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

		node&	operator=(node const & rhs)
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
				, class T_Alloc = typename std::allocator< T >, class N_Alloc = typename std::allocator< N >>
	struct rb_tree
	{
		typedef	T					value_type;
		typedef T_Alloc				value_allocater_type;
		typedef	N					node_type;
		typedef node_type*			node_pointer;
		typedef N_Alloc				node_allocater_type;

		typedef Compare				key_compare;
		typedef	key					key_type;

		node_pointer			root;
		node_pointer			end;
		value_allocater_type	value_alloc;
		node_allocater_type		node_alloc;

		rb_tree()
			:root(NULL), end(NULL),
			value_alloc(value_allocater_type()),
			node_alloc(node_allocater_type())
		{}

		rb_tree(value_type const& val)
			:rb_tree()
		{
			node_alloc.construct(root, val);
			end = root;
		}

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

		void	clear()
		{
			if (empty())
				return ;
			if (root->left)
				clear(root->left);
			if (root->right)
				clear(root->right);
			node_alloc.destroy(root);
		}

		void	clear(node_pointer ptr)
		{
			if (ptr->left)
				clear(ptr->left);
			if (ptr->right)
				clear(ptr->right);
			node_alloc.destroy(ptr);
		}

		void	copy(rb_tree const& src)
		{
			clear();
			if (src.empty())
				return ;
			root = new node_type(src.root);
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

		node_pointer	copy(node_pointer ptr1, node_pointer ptr2)
		{
			ptr1 = new node_type(ptr2);
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

		void	insert(const value_type& value)
		{
			node_pointer	new_node(root);
			node_pointer	new_parent;
			bool			side;

			while (new_node)
			{
				new_parent = new_node;
				if (key_compare(value.first, new_node->value.first))
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
		}

	};

}

#endif