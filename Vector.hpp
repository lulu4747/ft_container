#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <stdexcept>
# include "ft.hpp"
# include "Iterator.hpp"

namespace	ft
{

	template< typename T>
	class VectorIterator //: public iterator_traits< T >
	{

	public:

		typedef T							value_type;
    	typedef value_type*					pointer;
    	typedef value_type const *			const_pointer;
    	typedef value_type&					reference;
    	typedef value_type const &			const_reference;
    	typedef std::ptrdiff_t				difference_type;
		typedef random_access_iterator_tag	iterator_category;

		VectorIterator():_ptr(NULL)	{}
		VectorIterator(pointer ptr):_ptr(ptr) {}
		VectorIterator(VectorIterator const & src):_ptr(src._ptr)	{}
		virtual	~VectorIterator()	{}

		VectorIterator&	operator=(VectorIterator const & rhs)
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

		VectorIterator operator++(int)
		{
			VectorIterator 	tmp(*this);

			++_ptr;
			return tmp;
		}

		VectorIterator& operator++()
		{
			++_ptr;
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator 	tmp(*this);

			--_ptr;
			return tmp;
		}

		VectorIterator& operator--()
		{
			--_ptr;
			return *this;
		}

		VectorIterator& operator+=(int value)
		{
			_ptr += value;
			return *this;
		}

		VectorIterator operator+(int value)
		{
			VectorIterator tmp(this->_ptr + value);

			return tmp;
		}

		VectorIterator& operator-=(int value)
		{
			_ptr -= value;
			return *this;
		}

		VectorIterator operator-(int value)
		{
			VectorIterator	tmp(this->_ptr - value);

			return tmp;
		}

		difference_type operator-(VectorIterator const &rhs) const
		{
			return (_ptr - rhs._ptr);
		}

		bool operator==(VectorIterator const &rhs) const
		{
			return (_ptr == rhs._ptr);
		}

		bool operator!=(VectorIterator const &rhs) const
		{
			return (_ptr != rhs._ptr);
		}

		bool operator<(VectorIterator const &rhs) const
		{
			return (_ptr < rhs._ptr);
		}

		bool operator<=(VectorIterator const &rhs) const
		{
			return (_ptr <= rhs._ptr);
		}

		bool operator>(VectorIterator const &rhs) const
		{
			return (_ptr > rhs._ptr);
		}

		bool operator>=(VectorIterator const &rhs) const
		{
			return (_ptr >= rhs._ptr);
		}

	protected:

		pointer	_ptr;

	};

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

		typedef typename	allocator_type::pointer			pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;


		typedef	VectorIterator<value_type>				iterator;
		typedef	VectorIterator<value_type>				const_iterator;
		/*typedef	ft_ReverseIterator<iterator>		reverse_iterator;
		typedef	ft_ReverseIterator<iterator>		const_reverse_iterator;*/

	//	Member Functions :


		//	Canons
		explicit Vector (const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _data(NULL), _back(NULL), _last(NULL)
		{}

		explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		:_alloc(alloc), _data(NULL), _back(NULL), _last(NULL)
		{
			_allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + i, val);
			_back += n;
		}

		template <class InputIterator>
		Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _data(NULL), _back(NULL), _last(NULL)
		{
			assign(first, last);
		}

		Vector (const Vector& x):
			_alloc(x.get_allocator()), _data(NULL), _back(NULL), _last(NULL)
		{
			*this = x;
		}

		Vector &	operator=(const Vector& rhs)
		{
			if (this != &rhs)
			{
				if (capacity())
					this->~Vector();
				assign(rhs.begin(), rhs.end());
			}
			return *this;
		}

		virtual	~Vector()
		{
			for (size_type i = 0; i < size(); i++)
				_alloc.destroy(_data + i);
			_deallocate();
		}

		//	Iterators

		iterator	begin( void ) const
		{
			return	iterator(_data);
		}

		iterator	end( void ) const
		{
			return	iterator(_back);
		}

		// Capacity

		size_type	size( void ) const
		{
			return _back - _data;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		void resize (size_type n, value_type val = value_type())
		{
			while (!empty() && size() > n)
				pop_back();
			while (size() < n)
				push_back(val);
		}

		size_type	capacity( void ) const
		{
			return _last - _data;
		}

		bool		empty( void ) const
		{
			return !size();
		}

		void	reserve(size_type n)
		{
			if (empty())
				_allocate(n);
			else if (capacity() < n)
			{
				Vector*		old_vector(this);

				_allocate(n);
				_back += old_vector->size();
				for (size_type i = 0; i < old_vector->size(); i++)
					_alloc.construct(_data + i, old_vector->_data[i]);
				old_vector->~Vector();
			}
		}

		// Element Access

		reference	operator[]( size_type n )
		{
			return _data[n];
		}

		reference	at( size_type n )
		{
			if ( n > size() )
				throw	std::out_of_range("vector");		//faire mieux
			return _data[n];
		}

		reference	front( void )
		{
			return *_data;
		}

		reference	back( void )
		{
			return	*_back;
		}

		//	Modifier

		void	assign(size_type count, const T& value)
		{
			reserve(count);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_data + i, value);
			_back += count;
		}

		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator >::type* = NULL)
		{
			size_type	count = last - first;

			reserve(count);
			for (iterator it = begin(); first != last; first++)
			{
				_alloc.construct(&(*it), *first);
				it++;
			}
			_back += count;
		}

		void	push_back(const value_type& val)
		{
			if (!capacity())
				reserve(1);
			else if(size() == capacity())
				reserve(capacity() * 2);
			_alloc.construct(_back, val);
			_back++;
		}

		void	pop_back()
		{
			if (empty())
				return;
			_alloc.destroy(_back);
			_back--;
		}

		iterator insert (iterator position, const value_type& val)
		{
			size_type i = position - begin();

			insert(position, 1, val);
			return begin() + i;
		}

		void insert (iterator position, size_type n, const value_type& val) // Verifier avec n = 0 meme si c est con
		{
			if (position == end())
			{
				while (n--)
					push_back(val);
				return ;
			}

			for (size_type i = n; i > 0; i--)
				push_back(*_back);

			iterator	it(_back);

			while (it != position)
			{
				*it = *(it - n);
				it--;
			}
			while (n--)
			{
				*it = val;
				it++;
			}
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator >::type* = NULL)
		{
			size_type	size_to_add(last - first);
			size_type	pos(position - begin());

			if (position == end())
			{
				while (first != last)
				{
					push_back(*first);
					first++;
				}
				return ;
			}

			for (size_type i = size_to_add; i > 0; i--)
				push_back(*_back);

			iterator	it(_back);
			position = _data + pos;

			while (it != position)
			{
				*it = *(it - size_to_add);
				it--;
			}
			while (first != last)
			{
				*it = *first;
				first++;
				it++;
			}
		}

		iterator erase (iterator position)
		{
			if (position == end())
			{
				pop_back();
				return end();
			}
			for (iterator it = position; it != end(); it++)
				*it = *(it + 1);
			pop_back();
			return ++position;
		}

		iterator erase (iterator first, iterator last)
		{
			while (first != last)
				first = erase(first);
			return first;
		}

		void swap(Vector& x)
		{
			Vector	tmp(*this);

			*this = x;
			x = tmp;
			tmp.~Vector();
		}

		void	clear()
		{
			for (size_type i = 0; i < size(); i++)
				_alloc.destroy(_data + i);
			_back = _data;
		}

		allocator_type get_allocator() const
		{
			return _alloc;
		}

	protected:

		allocator_type	_alloc;

		pointer			_data;
		pointer			_back;
		pointer			_last;

		void	_allocate(size_type n)
		{
			_data = _alloc.allocate(n);
			_back = _data;
			_last = _data + n;
		}

		void	_deallocate()
		{
			_alloc.deallocate(_data, capacity());
			_data = NULL;
			_back = NULL;
			_last = NULL;
		}

	};
}

#endif