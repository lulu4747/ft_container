#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>
# include "Stack.hpp"
# include "ft.hpp"

namespace ft
{

	struct	Output_Iterator_tag{};
	struct	Input_Iterator_tag{};
	struct	Forward_Iterator_tag : public Input_Iterator_tag {};
	struct	Bidirectional_Iterator_tag : public Forward_Iterator_tag {};
	struct	Random_Access_Iterator_tag : public Bidirectional_Iterator_tag {};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;

	};

	template <class Iterator>
	struct	iterator_traits
	{
		typedef	typename	Iterator::difference_type	difference_type;
		typedef typename	Iterator::value_type		value_type;
		typedef typename	Iterator::pointer			pointer;
		typedef typename	Iterator::reference			reference;
		typedef typename	Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct	iterator_traits<T*>
	{
		typedef	std::ptrdiff_t				difference_type;
    	typedef	T							value_type;
    	typedef	T*							pointer;
    	typedef	T&							reference;
    	typedef	Random_Access_Iterator_tag	iterator_category;
  	};

	template <class T>
	struct	iterator_traits<const T*>
	{
		typedef	std::ptrdiff_t				difference_type;
		typedef	T							value_type;
		typedef	const T*					pointer;
		typedef	const T&					reference;
		typedef	Random_Access_Iterator_tag	iterator_category;
  	};

	template <class T>
	struct is_input_iterator_tagged
	{ 
		static const bool value = false;
	};

	template <> struct is_input_iterator_tagged<Input_Iterator_tag> { static const bool value = true; };
	template <> struct is_input_iterator_tagged<Forward_Iterator_tag> { static const bool value = true; };
	template <> struct is_input_iterator_tagged<Bidirectional_Iterator_tag> { static const bool value = true; };
	template <> struct is_input_iterator_tagged<Random_Access_Iterator_tag> { static const bool value = true; };

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
			:_inf(stack()), _sup(stack())
		{
			_stack_from_greater(ptr);
			_stack_from_smallest(ptr);
		}

		Binary_Search_Tree_Iterator(Binary_Search_Tree_Iterator const & src)
		{
			*this = src;
		}

		virtual	~Binary_Search_Tree_Iterator()	{}

		Binary_Search_Tree_Iterator&	operator=(Binary_Search_Tree_Iterator const & rhs)
		{
			if (this != &rhs)
			{
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

	template< typename T >
	class RandomAccessIterator : public iterator_traits< Iterator< Random_Access_Iterator_tag, T > >
	{

	public:

		typedef T							value_type;
    	typedef value_type*					pointer;
    	typedef value_type const *			const_pointer;
    	typedef value_type&					reference;
    	typedef value_type const &			const_reference;
    	typedef std::ptrdiff_t				difference_type;
		typedef Random_Access_Iterator_tag	iterator_category;

		RandomAccessIterator():_ptr(NULL)	{}
		RandomAccessIterator(pointer ptr):_ptr(ptr) {}
		RandomAccessIterator(RandomAccessIterator const & src):_ptr(src._ptr)	{}
		virtual	~RandomAccessIterator()	{}

		RandomAccessIterator&	operator=(RandomAccessIterator const & rhs)
		{
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		reference	operator*()
		{
			return *(_ptr);
		}

		const_reference	operator*() const
		{
			return *(_ptr);
		}

		pointer	operator->()
		{
			return _ptr;
		}

		const_pointer	operator->() const
		{
			return _ptr;
		}

		reference	operator[](size_t index)
		{
			return *(_ptr + index);
		}

		const_reference	operator[](size_t index) const
		{
			return *(_ptr + index);
		}

		RandomAccessIterator operator++(int)
		{
			RandomAccessIterator 	tmp(*this);

			++_ptr;
			return tmp;
		}

		RandomAccessIterator& operator++()
		{
			++_ptr;
			return *this;
		}

		RandomAccessIterator operator--(int)
		{
			RandomAccessIterator 	tmp(*this);

			--_ptr;
			return tmp;
		}

		RandomAccessIterator& operator--()
		{
			--_ptr;
			return *this;
		}

		RandomAccessIterator& operator+=(int value)
		{
			_ptr += value;
			return *this;
		}

		RandomAccessIterator operator+(int value)
		{
			RandomAccessIterator tmp(this->_ptr + value);

			return tmp;
		}

		RandomAccessIterator& operator-=(int value)
		{
			_ptr -= value;
			return *this;
		}

		RandomAccessIterator operator-(int value)
		{
			RandomAccessIterator	tmp(this->_ptr - value);

			return tmp;
		}

		difference_type operator-(RandomAccessIterator const &rhs) const
		{
			return (_ptr - rhs._ptr);
		}

		bool operator==(RandomAccessIterator const &rhs) const
		{
			return (_ptr == rhs._ptr);
		}

		bool operator!=(RandomAccessIterator const &rhs) const
		{
			return (_ptr != rhs._ptr);
		}

		bool operator<(RandomAccessIterator const &rhs) const
		{
			return (_ptr < rhs._ptr);
		}

		bool operator<=(RandomAccessIterator const &rhs) const
		{
			return (_ptr <= rhs._ptr);
		}

		bool operator>(RandomAccessIterator const &rhs) const
		{
			return (_ptr > rhs._ptr);
		}

		bool operator>=(RandomAccessIterator const &rhs) const
		{
			return (_ptr >= rhs._ptr);
		}

	protected:

		pointer	_ptr;

	};

	template < class Iter >
	class	ReverseIterator : public Iter
	{

	public:

		typedef	Iter	iterator_type;

		typedef typename	iterator_traits<Iter>::difference_type		difference_type;
		typedef typename	iterator_traits<Iter>::value_type			value_type;
		typedef typename	iterator_traits<Iter>::pointer				pointer;
		typedef typename	iterator_traits<Iter>::reference			reference;
		typedef typename	iterator_traits<Iter>::iterator_category	iterator_category;

		ReverseIterator()
			:current()
		{}

		ReverseIterator( iterator_type x )
			:current(x)
		{}

		template< class U >
		ReverseIterator( const ReverseIterator<U>& other )
			:current(other.base())
		{}

		template< class U >
		ReverseIterator& operator=( const ReverseIterator<U>& other )
		{
			if (this != &other)
				current = other.base();
			return *this;
		}

		iterator_type base() const
		{
			return current;
		}

		reference operator*() const
		{
			iterator_type	tmp(current);

			return *--tmp;
		}

		pointer operator->() const
		{
			iterator_type	tmp(current);

			return (--tmp).operator->();
		}

		reference	operator[]( difference_type n ) const
		{
			return base()[-n-1];
		}

		ReverseIterator& operator++()
		{
			return current--;
		}

		ReverseIterator& operator--()
		{
			return current++;
		}

		ReverseIterator operator++( int )
		{
			ReverseIterator	tmp(current);

			--current;
			return tmp;
		}

		ReverseIterator operator--( int )
		{
			ReverseIterator	tmp(current);

			++current;
			return tmp;
		}

		ReverseIterator operator+( difference_type n ) const
		{
			ReverseIterator	tmp(current - n);

			return tmp;
		}

		ReverseIterator operator-( difference_type n ) const
		{
			ReverseIterator	tmp(current + n);

			return tmp;
		}

		ReverseIterator& operator+=( difference_type n )
		{
			current -= n;
			return *this;
		}

		ReverseIterator& operator-=( difference_type n )
		{
			current += n;
			return *this;
		}

	protected:

		iterator_type	current;

	};



}

#endif
