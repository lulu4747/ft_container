#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
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
		typedef	ptrdiff_t			difference_type;
		typedef	value_type&			reference;
 		typedef const value_type&	const_reference;

		typedef typename	Alloc::pointer			pointer;
		typedef typename	Alloc::const_pointer	const_pointer;
/*	need to check iterators
iterator 	LegacyRandomAccessIterator to value_type
const_iterator 	LegacyRandomAccessIterator to const value_type
reverse_iterator 	std::reverse_iterator<iterator>
const_reverse_iterator 	std::reverse_iterator<const_iterator>*/

	//	Member Functions :


		//	Canons
		explicit Vector (const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _size(0), _capacity(0)
		{}

		explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _size(n), _capacity(n)
		{
			_value = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_value[i] = val;
		}

		template <class InputIterator>
		Vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());

		Vector (const Vector& x);

		~Vector();

		//	Iterators

	private:

		allocator_type		_alloc;
		value_type*			_value;

		size_type			_size;
		size_type			_capacity;

		reference			_front;
		reference			_back;
	};
}

#endif