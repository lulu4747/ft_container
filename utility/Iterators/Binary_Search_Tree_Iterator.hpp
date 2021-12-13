#ifndef BINARY_SEARCH_TREE_ITERATOR
# define BINARY_SEARCH_TREE_ITERATOR
//
#include <iostream>
//
# include "Iterator.hpp"
# include "../less.hpp"
# include "../BST_tree/node.hpp"

//# include "../BST_tree/rb_tree.hpp"

namespace	ft
{
	template< typename T, typename N >
	struct	tmp
	{
		N	ptr;

		tmp(T const & src):ptr(src._ptr){}

		N	get()
		{	return ptr;}
	};

	template< typename T, class Compare = ft::less< T > , class T_Alloc = typename std::allocator< T >,
					class key = typename T::first_type, typename N = ft::node< T >, class N_Alloc = typename std::allocator< N > >
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

		typedef				Binary_Search_Tree_Iterator< T, Compare, T_Alloc, key, N, N_Alloc>	iterator;
		typedef	typename	N_Alloc::pointer													node_pointer;

		node_pointer	_ptr;

		//friend	void	rb_tree< T, Compare, T_Alloc, key, N, N_Alloc >::erase(Binary_Search_Tree_Iterator< T, Compare, T_Alloc, key, N, N_Alloc >& to_remove);
		friend	struct	tmp<iterator, node_pointer>;
	};
}

#endif
