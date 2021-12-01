#ifndef BINARY_SEARCH_TREE_ITERATOR
# define BINARY_SEARCH_TREE_ITERATOR

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
	
		explicit Binary_Search_Tree_Iterator(pointer ptr = NULL)
			:_inf(Stack()), _sup(Stack())
		{
			_stack_from_greater(ptr);
			_stack_from_smallest(ptr);
		}

		Binary_Search_Tree_Iterator(Binary_Search_Tree_Iterator const & src)
		{
			*this = src;
		}

		virtual	~Binary_Search_Tree_Iterator()
		{
			_inf.~Stack();
			_sup.~Stack();
		}

		Binary_Search_Tree_Iterator&	operator=(Binary_Search_Tree_Iterator const & rhs)
		{
			if (this != &rhs)
			{
				_empty_stacks();
				_stack_from_greater(rhs._current());
				_stack_from_smallest(rhs._current());
			}
			return *this;
		}

		reference	operator*()
		{
			return *(_current()->value);
		}

		const_reference	operator*() const
		{
			return *(_current()->value);
		}

		pointer	operator->()
		{
			return _current()->value;
		}

		const_pointer	operator->() const
		{
			return _current()->value;
		}

		Binary_Search_Tree_Iterator operator++(int)
		{
			Binary_Search_Tree_Iterator 	tmp(*this);

			operator++();
			return tmp;
		}

		Binary_Search_Tree_Iterator& operator++()
		{
			_inf.push(_sup.top());
			_sup.pop();
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
			_sup.push(_inf.top());	// Verify true behaviour when begin()--
			_inf.pop();
			return *this;
		}

		bool operator==(Binary_Search_Tree_Iterator const &rhs) const
		{
			return (_current() == rhs._current());
		}

		bool operator!=(Binary_Search_Tree_Iterator const &rhs) const
		{
			return !(operator==(rhs));
		}

	protected :

		typedef	T*					node_pointer;
		typedef	Stack<node_pointer>	stack;

		stack			_inf;
		stack			_sup;

		node_pointer	_get_root(node_pointer ptr)
		{
			while (ptr->parent)
				ptr = ptr->parent;
			return ptr;
		}

		node_pointer	_current()
		{
			return (_inf.top())
		}

		void	_empty_stacks()
		{
			while (!_inf.empty())
				_inf.pop();
			while (!_sup.empty())
				_sup.pop();
		}

		void	_stack_from_greater(node_pointer ptr, node_pointer current = NULL, node_pointer root = _get_root(ptr))
		{
			if (!current)
				current = root;
			if (current->right)
				_stack_from_greater(ptr, current->right, root);
			if (_sup.empty())
				_suo.push(NULL);
			if (_sup.top() == ptr || current == ptr)
				return ;
			_sup.push(current);
			if (current->left)
				_stack_from_greater(ptr, current->left, root);
		}

		void	_stack_from_smallest(node_pointer ptr, node_pointer current = NULL, node_pointer root = _get_root(ptr))
		{
			if (!current)
				current = root;
			if (current->left)
				_stack_from_smallest(ptr, current->left, root);
			if (_sup.top() == ptr)
				return ;
			_sup.push(current);
			if (current == ptr)
				return ;
			if (current->right)
				_stack_from_smallest(ptr, current->right, root);
		}
	};
}

#endif
