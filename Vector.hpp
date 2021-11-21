#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <stdexcept>
# include "ft.hpp"
# include "algorithm.hpp"
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

		typedef typename	allocator_type::pointer			pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;


		typedef	random_access_iterator<value_type>		iterator;
		typedef	const iterator							const_iterator;
		typedef	reverse_iterator<value_type>			reverse_iterator;
		typedef	const reverse_iterator					const_reverse_iterator;

	//	Member Functions :


		//	Canons
		explicit Vector (const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _data(NULL), _end(NULL), _capacity(NULL)
		{}

		explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		:_alloc(alloc), _data(NULL), _end(NULL), _capacity(NULL)
		{
			_allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + i, val);
			_end += n;
		}

		template <class InputIterator>
		Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _data(NULL), _end(NULL), _capacity(NULL)
		{
			assign(first, last);
		}

		Vector (const Vector& x):
			_alloc(x.get_allocator()), _data(NULL), _end(NULL), _capacity(NULL)
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

		iterator	begin( void )
		{
			return	iterator(_data);
		}

		const_iterator begin() const
		{
			return const_iterator(_data);
		}

		iterator	end( void )
		{
			return	iterator(_end);
		}

		const_iterator end() const
		{
			return	const_iterator(_end);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(back());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(back());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_data - 1);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_data - 1);
		}

		// Capacity

		size_type	size( void ) const
		{
			return _end - _data;
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
			return _capacity - _data;
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
				pointer		copy(_data);
				size_type	size(this->size());

				_deallocate();
				_allocate(n);
				_end += size;
				for (size_type i = 0; i < size; i++)
				{
					_alloc.construct(_data + i, copy[i]);
					_alloc.destroy(copy + i);
				}
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
				throw	std::out_of_range("Vector");		//faire mieux
			return _data[n];
		}

		reference	front( void )
		{
			return *_data;
		}

		reference	back( void )
		{
			return	*(_data + size());
		}

		//	Modifier

		void	assign(size_type count, const T& value)
		{
			clear()
			reserve(count);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_data + i, value);
			_end += count;
		}

		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator >::type* = NULL)
		{
			if(!(is_input_iterator_tagged< typename iterator_traits<InputIterator>::iterator_category >::value))
				throw std::invalid_argument("Iterator is'nt at least ft::InputIterator tagged");						//faire mieux

			size_type	count = last - first;

			clear()
			reserve(count);
			for (iterator it = begin(); first != last; first++)
			{
				_alloc.construct(&(*it), *first);
				it++;
			}
			_end += count;
		}

		void	push_back(const value_type& val)
		{
			if (!capacity())
				reserve(1);
			else if(size() == capacity())
				reserve(capacity() * 2);
			_alloc.construct(_end, val);
			_end++;
		}

		void	pop_back()
		{
			if (empty())
				return;
			_alloc.destroy(_end);
			_end--;
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
				push_back(back());

			iterator	it(_end);

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
			if(!(is_input_iterator_tagged< typename iterator_traits<InputIterator>::iterator_category >::value))
				throw std::invalid_argument("Iterator is'nt at least ft::InputIterator tagged");					//Faire mieux

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
				push_back(back());

			iterator	it(_end);
			position = _data + pos;

			while (it != position)
			{
				*it = *(it - size_to_add);
				it--;
			}
			while (first != last)
			{
				*it = *first;
				first++;	it++;
			}
		}

		iterator erase (iterator position)
		{
			size_type	new_pos(position - begin());

			if (position == end())
			{
				pop_back();
				return end();
			}
			for (iterator it = position; it + 1 != end(); it++)
			{
				_alloc.destroy(&(*it));
				_alloc.construct(&(*it), *(it + 1));
			}
			pop_back();
			return (begin() + new_pos);
		}

		iterator erase (iterator first, iterator last)
		{
			size_type	range = 0;

			for (iterator it = first; it != last; it++)
			{
				_alloc.destroy(&(*(it)));				//does'nt segfault when destructing past capacity
				range++;
			}
			while (first != last)
			{
				_alloc.construct(&(*first), *(first + range));
				first++;
			}
			while (range--)
				pop_back();
			return first;
		}
/*
		iterator erase (iterator position)
		{
			if (position == end())
			{
				pop_back();
				return end();
			}
			for (iterator it = position; it + 1 != end(); it++)
				*it = *(it + 1);
			pop_back();
			return position;
		}

		iterator erase (iterator first, iterator last)
		{
			iterator	tmp(first);

			while (first++ != last)			//should be very slow =(
				erase(tmp);
			return first;
		}*/

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
			_end = _data;
		}

		allocator_type get_allocator() const
		{
			return _alloc;
		}

	protected:

		allocator_type	_alloc;

		pointer			_data;
		pointer			_end;
		pointer			_capacity;

		void	_allocate(size_type n)
		{
			_data = _alloc.allocate(n);
			_end = _data;	_capacity = _data + n;
		}

		void	_deallocate()
		{
			_alloc.deallocate(_data, capacity());
			_data = NULL;	_end = NULL;	_capacity = NULL;
		}

	};

	template < class T, class Alloc >
	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return equal(lhs.begin(), iterator(lhs.back()), rhs.begin());
	}

	template < class T, class Alloc >
 	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template < class T, class Alloc >
	bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), iterator(lhs.back()),
				rhs.begin(), iterator(rhs.back())));
	}

	template < class T, class Alloc >
	bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template < class T, class Alloc >
	bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template < class T, class Alloc >
	bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif