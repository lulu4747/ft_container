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
			delete root;
		}

		void	clear(leaf* l)
		{
			if (l->left)
				clear(l->left);
			if (l->right)
				clear(l->right);
			delete l;
		}

		void	copy(rb_tree const& src)
		{
			clear();
			if (src.empty())
				return ;
			root = new leaf(src.root);
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

		leaf*	copy(leaf* l, leaf* src_l)
		{
			l = new leaf(src_l);
			if (src_l->left)
				l->left = copy(l->left, src_l->left);
			else
				l->left = NULL;
			if (src_l->right)
				l->right = copy(l->right, src_l->right);
			else
				l->right = NULL;
			return l;
		}

		bool	insert(const value_type& value)
		{
			leaf*	new_l(root);
			leaf*	new_p;

			while (new_l != NULL)
			{
				new_p = new_l;
				if (key_compare(value.first, new_l->value.first))
					new_l = new_l->left;
				else
					new_l = new_l->right;
			}
			new_l = new leaf(value, new_p);
		}

	};

}

#endif