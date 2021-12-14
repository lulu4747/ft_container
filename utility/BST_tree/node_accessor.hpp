#ifndef NODE_ACCESSOR_HPP
# define NODE_ACCESSOR_HPP

# include "../Iterators/Binary_Search_Tree_Iterator.hpp"

namespace	ft
{
	namespace
	{
		template< typename T >
		class	node_accessor : public Binary_Search_Tree_Iterator <T>
		{

		public :

			typedef	T*		node_pointer;

			explicit node_accessor(T* ptr = NULL)
				:Binary_Search_Tree_Iterator<T>(ptr)
			{}

			node_accessor(Binary_Search_Tree_Iterator<T> const & src)
				:Binary_Search_Tree_Iterator<T>(src)
			{}

			node_accessor(node_accessor const & src)
			{
				*this = src;
			}

			virtual	~node_accessor()	{}

			node_accessor&	operator=(node_accessor const & rhs)
			{
				if (this != &rhs)
					Binary_Search_Tree_Iterator<T>::_ptr = rhs._ptr;
				return *this;
			}

			node_pointer	get_node()
			{
				return Binary_Search_Tree_Iterator<T>::_ptr;
			}
		};

	}
}

#endif