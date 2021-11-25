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
		pointer	data;

		explicit node(reference src_data = value_type(),
			element const& src_parent = NULL, element const& src_left = NULL, element const& src_right = NULL)
		:
			parent(src_parent),
			left(src_left),
			right(src_right),
			data(src_data)
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
				data = rhs.data;
			}
			return *this;
		}

		bool	operator==(node const & rhs) const
		{
			return (*data == *(rhs.data));
		}

		bool	operator!=(node const & rhs) const
		{
			return !(*data == *(rhs.data));
		}
	};

	template< class T, class Compare, class key = typename T::key_type >
	struct rb_tree
	{
		typedef	T					value_type;
		typedef Compare				key_compare;
		typedef	key					key_type;
		typedef node<value_type>	leaf;

		leaf*	root;
		leaf*	end;

		rb_tree()
			:root(NULL), end(NULL)
		{}

		rb_tree(value_type const& val)
			:root(new leaf(val)), end(root)
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

		void	clear()
		{
			if (root == NULL)
				return ;
			if (root->left)
				clear(root->left);
			if (root->right)
				clear(root->right);
			delete root;
		}

		void	clear(leaf *l)
		{
			if (l == NULL)
				return ;
			if (l->left)
				clear(l->left);
			if (l->right)
				clear(l->right);
			delete l;
		}

		void	copy(rb_tree const& rhs)
		{
			clear();
			// go
		}

	};

}

#endif