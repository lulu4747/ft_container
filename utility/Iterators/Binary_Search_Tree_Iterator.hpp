#ifndef BINARY_SEARCH_TREE_ITERATOR
# define BINARY_SEARCH_TREE_ITERATOR

#include <iostream>

# include "../../ft_containers/Stack.hpp"
# include "Iterator.hpp"

namespace	ft
{
	template< typename T >
	class	Binary_Search_Tree_Iterator : public iterator_traits< Iterator< Bidirectional_Iterator_tag, T > >
	{

	public :

		typedef typename	T::value_type				value_type;
    	typedef 			value_type*					pointer;
    	typedef 			value_type const *			const_pointer;
    	typedef 			value_type&					reference;
    	typedef 			value_type const &			const_reference;
    	typedef 			std::ptrdiff_t				difference_type;
		typedef 			Bidirectional_Iterator_tag	iterator_category;
	
		explicit Binary_Search_Tree_Iterator(T* ptr = NULL)
			:_ptr(ptr)
		{}

		Binary_Search_Tree_Iterator(Binary_Search_Tree_Iterator const & src)
		{
			*this = src;
		}

		virtual	~Binary_Search_Tree_Iterator()	{}

		Binary_Search_Tree_Iterator&	operator=(Binary_Search_Tree_Iterator const & rhs)
		{
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		reference	operator*()
		{
			return *(_ptr->value);
		}

		const_reference	operator*() const
		{
			return *(_ptr->value);
		}

		pointer	operator->()
		{
			return _ptr->value;
		}

		const_pointer	operator->() const
		{
			return _ptr->value;
		}

		Binary_Search_Tree_Iterator operator++(int)
		{
			Binary_Search_Tree_Iterator 	tmp(*this);

			operator++();
			return tmp;
		}

		Binary_Search_Tree_Iterator& operator++()
		{
			if (!_ptr->value)
				_ptr = _ptr->left;
			if (_ptr->right->value)
			{
				_ptr = _ptr->right;
				while (_ptr->left->value)
					_ptr = _ptr->left;
			}
			else
			{
				node_pointer	tmp(_ptr);

				while (_ptr->value && tmp != _ptr->left)
				{
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
			}
			return *this;
		}

		Binary_Search_Tree_Iterator operator--(int)
		{
			Binary_Search_Tree_Iterator 	tmp(*this);

			operator--();
			return tmp;
		}

		Binary_Search_Tree_Iterator& operator--()
		{
			if (!_ptr->value)
				_ptr = _ptr->right;
			if (_ptr->left->value)
			{
				_ptr = _ptr->left;
				while (_ptr->right->_value)
					_ptr = _ptr->right;
			}
			else
			{
				node_pointer	tmp(_ptr);

				while (_ptr->value && tmp != _ptr->right)
				{
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
			}
			return *this;
		}

		bool operator==(Binary_Search_Tree_Iterator const &rhs) const
		{
			return (_ptr == rhs._ptr);
		}

		bool operator!=(Binary_Search_Tree_Iterator const &rhs) const
		{
			return !(operator==(rhs));
		}

	protected :

		typedef	T*		node_pointer;

		node_pointer	_ptr;
	};
}

#endif
