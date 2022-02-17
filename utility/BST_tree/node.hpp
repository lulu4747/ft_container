#ifndef NODE_HPP
# define NODE_HPP

# include <clocale>

namespace	ft
{
	namespace
	{
		template< class T >
		struct node
		{

			typedef	struct		node*						pointer;
			typedef	const		pointer						const_pointer;
			typedef	struct		node&						reference;
			typedef				T							value_type;
			typedef				value_type*					value_pointer;

			typedef	typename	value_type::first_type		key_type;

			pointer			parent;
			pointer			left;
			pointer			right;
			value_pointer	value;
			bool			nill;
			bool			red;
			bool			double_black;

			explicit node(value_pointer src_value = NULL,
				pointer const& src_parent = NULL, pointer const& src_left = NULL, pointer const& src_right = NULL)
			:
				parent(src_parent),
				left(src_left),
				right(src_right),
				value(src_value),
				nill(false),
				red(true),
				double_black(false)
			{}

			node(node const & src)
			{
				*this = src;
			}

			reference	operator=(node const & rhs)
			{
				if (this != &rhs)
				{
					parent = rhs.parent;
					left = rhs.left;
					right = rhs.right;
					value = rhs.value;
					nill = rhs.nill;
					red = rhs.red;
					double_black = rhs.double_black;
				}
				return *this;
			}

			key_type&	key() const
			{
				return value->first;
			}

			pointer	root()
			{
				pointer	ptr(this);

				while (ptr->parent->value)
					ptr = ptr->parent;
				return ptr;
			}

			const_pointer	root() const
			{
				const_pointer	ptr(this);

				while (ptr->parent->value)
					ptr = ptr->parent;
				return ptr;
			}

			pointer	leftmost()
			{
				pointer	ptr(root());

				while (ptr->left->value)
					ptr = ptr->left;
				return ptr;
			}

			const_pointer	leftmost() const
			{
				const_pointer	ptr(root());

				while (ptr->left->value)
					ptr = ptr->left;
				return ptr;
			}

			pointer	rightmost()
			{
				pointer	ptr(root());

				while (ptr->right->value)
					ptr = ptr->right;
				return ptr;
			}

			const_pointer	rightmost() const
			{
				const_pointer	ptr(root());

				while (ptr->right->value)
					ptr = ptr->right;
				return ptr;
			}

			pointer	grandparent()
			{
				return parent->parent;
			}

			const_pointer	grandparent() const
			{
				return parent->parent;
			}

			pointer	uncle()
			{
				pointer	gp(grandparent());

				if (parent == gp->left)
					return gp->right;
				return gp->left;
			}

			const_pointer	uncle() const
			{
				pointer	gp(grandparent());

				if (parent == gp->left)
					return gp->right;
				return gp->left;
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
	}
}

#endif