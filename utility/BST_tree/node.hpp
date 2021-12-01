#ifndef NODE_HPP
# define NODE_HPP

# include <clocale>

namespace	ft
{

	template< class T >
	struct node
	{

		typedef	struct		node*						pointer;
		typedef	struct		node&						reference;
		typedef				T							value_type;
		typedef				value_type*					value_pointer;

		typedef	typename	value_type::first_type		key_type;

		pointer			parent;
		pointer			left;
		pointer			right;
		value_pointer	value;

		explicit node(value_pointer src_value = NULL,
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

		key_type&	key() const
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
}

#endif