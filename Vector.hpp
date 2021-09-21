#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "ft.hpp"
# include "Iterator.hpp"

namespace	ft
{

	template < class T, class Alloc = std::allocator<T> >
	class Vector{

	public:

	//	Member Types :

		typedef T					value_type;
		typedef	Alloc				allocator_type;
		typedef	size_t				size_type;
		typedef	std::ptrdiff_t		difference_type;
		typedef	value_type&			reference;
 		typedef const value_type&	const_reference;

		typedef typename	Alloc::pointer			pointer;
		typedef typename	Alloc::const_pointer	const_pointer;


		typedef	ft_Iterator<value_type>				iterator;
		typedef	ft_Iterator<value_type>				const_iterator;
		/*typedef	ft_ReverseIterator<iterator>		reverse_iterator;
		typedef	ft_ReverseIterator<iterator>		const_reverse_iterator;*/

	//	Member Functions :


		//	Canons
		explicit Vector (const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _front(NULL), _back(NULL), _last(NULL)
		{}

		explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc)
		{
			_front = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_front[i] = val;
			_back = _front + n;
			_last = _back;
		}

		template <class InputIterator>
		Vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());

		Vector (const Vector& x);

		~Vector();

		// Element Access

		reference	at( size_type n )
		{
			if ( n > this->size() )
				throw	std::out_of_range("vector");
			return this->_front[n];
		}

		reference	operator[]( size_type n )
		{
			return this->_front[n];
		}

		reference	front( void )
		{
			return this->*_front;
		}

		reference	back( void )
		{
			return	this->*_back;
		}

		pointer		data( void )
		{
			return	this->_front;
		}

		//	Iterators

		iterator	begin( void )
		{
			return	ft_Iterator<value_type>(this->_front);
		}

		iterator	end( void )
		{
			return	ft_Iterator<value_type>(this->_back + sizeof(value_type));
		}

		// Capacity

		bool		empty( void )
		{
			return this->_front == NULL;
		}

		size_type	size( void )
		{
			return this->_back - this->_front;
		}

		size_type	capacity( void )
		{
			return this->_last - this->_front;
		}

	protected:

		allocator_type	const	_alloc;

		pointer					_front;
		pointer					_back;
		pointer					_last;

	};
}

#endif