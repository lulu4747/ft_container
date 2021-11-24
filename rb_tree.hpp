#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "Map.hpp"

namespace	ft
{

	template< class Container >
	struct node
	{

		typedef	typename	Container::key_type			key_type;
		typedef	typename	Container::value_type		value_type;
		typedef	typename	Container::allocator_type	allocator_type;

		typedef	struct		node*						pointer;
		typedef	const		Container*					container;

		pointer			parent;
		pointer			left;
		pointer			right;
		pointer			root;
		container		C;
		value_type*		content;

		node( const Container& c, value_type& val)
			:parent(this),
			left(NULL),
			right(NULL),
			root(this),
			C(&c)
		{
			allocator().construct(content, val);
		}

		node( pointer root);

		const allocator_type&	allocator() const
		{
			return C->get_allocator();
		}
	};

}

#endif