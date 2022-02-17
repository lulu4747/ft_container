#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "../utility/Iterators/Random_Access_Iterator.hpp"
# include "../utility/Iterators/Reverse_Iterator.hpp"
# include "../utility/algorithm.hpp"
# include "../utility/type_trait.hpp"

namespace	ft
{

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

	public:

	//	Member Types :

		typedef 			T											value_type;
		typedef				Alloc										allocator_type;
		typedef				size_t										size_type;
		typedef				std::ptrdiff_t								difference_type;

		typedef	typename	allocator_type::reference					reference;
		typedef	typename	allocator_type::const_reference				const_reference;

		typedef typename	allocator_type::pointer						pointer;
		typedef typename	allocator_type::const_pointer				const_pointer;


		typedef				Random_Access_Iterator<value_type>			iterator;
		typedef				Random_Access_Iterator<const value_type>	const_iterator;
		typedef				Reverse_Iterator<iterator>					reverse_iterator;
		typedef				Reverse_Iterator<const_iterator>			const_reverse_iterator;

	//	Member Functions :


		//	Canons
		explicit vector (const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc), _data(NULL), _end(NULL), _capacity(NULL)
		{}

		explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		:_alloc(alloc), _data(NULL), _end(NULL), _capacity(NULL)
		{
			if (n != 0)
			{
				if (n > max_size())
					throw (std::length_error("vector::vector(size_type n, const value_type& val, const allocator_type& alloc"));
				_allocate(n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_data + i, val);
				_end += n;
			}
		}

		template <class InputIt>
		vector (InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
			typename enable_if<!is_integral<InputIt>::value, InputIt >::type* = NULL)
		:
			_alloc(alloc), _data(NULL), _end(NULL), _capacity(NULL)
		{
			if(!(is_input_iterator_tagged< typename iterator_traits<InputIt>::iterator_category >::value))
				throw std::invalid_argument("In ft::vector(InputIt first, InputIt last), InputIt class is'nt at least ft::InputIterator tagged");					//Faire mieux

			assign(first, last);
		}

		vector (const vector& x):
			_alloc(x.get_allocator()), _data(NULL), _end(NULL), _capacity(NULL)
		{
			insert(begin(), x.begin(), x.end());
		}

		vector &	operator=(const vector& rhs)
		{
			if (this != &rhs)
			{
				clear();
				insert(begin(), rhs.begin(), rhs.end());
			}
			return *this;
		}

		virtual	~vector()
		{
			clear();
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
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->begin());
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
			if (n > this->max_size())
				throw (std::length_error("vector::resize"));
			else if (size() > n)
			{
				while (!empty() && size() > n)
					pop_back();
			}
			else
				insert(end(), n - size(), val);
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
			if (capacity() == 0)
				_allocate(n);
			else if (capacity() < n)
			{
				pointer		prev_data(_data);
				pointer		prev_capacity(_capacity);
				size_type	size(this->size());

				_allocate(n);
				_end += size;
				for (size_type i = 0; i < capacity(); i++)
				{
					if (i < this->size())
					{
						_alloc.construct(_data + i, prev_data[i]);
						_alloc.destroy(prev_data + i);
					}
				}
				_alloc.deallocate(prev_data, (prev_capacity - prev_data));
			}
		}

		// Element Access

		reference	operator[]( size_type n )
		{
			return _data[n];
		}

		const_reference	operator[]( size_type n ) const
		{
			return const_reference(_data[n]);
		}

		reference	at( size_type n )
		{
			if ( n >= size() )
				throw	std::out_of_range("vector");
			return _data[n];
		}

		const_reference	at( size_type n ) const
		{
			if ( n >= size() )
				throw	std::out_of_range("vector");
			return _data[n];
		}

		reference	front( void )
		{
			return *_data;
		}

		const_reference	front( void ) const
		{
			return const_reference(*_data);
		}

		reference	back( void )
		{
			return	*(_end - 1);
		}

		const_reference	back( void ) const
		{
			return	const_reference(*(_end - 1));
		}

		//	Modifier

		void	assign(size_type count, const T& value)
		{
			reserve(count);
			clear();
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_data + i, value);
			_end += count;
		}

		template <class InputIt>
		void	assign(InputIt first, InputIt last,
		typename enable_if<!is_integral<InputIt>::value, InputIt >::type* = NULL)
		{
			if(!(is_input_iterator_tagged< typename iterator_traits<InputIt>::iterator_category >::value))
				throw std::invalid_argument("In ft::vector::assign(InputIt first, InputIt last), InputIt class is'nt at least ft::InputIterator tagged");					//Faire mieux

			size_type	count = last - first;

			reserve(count);
			clear();
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
			_alloc.destroy(_end);
			_end--;
		}

		iterator insert (iterator position, const value_type& val)
		{
			size_type i = position - begin();

			insert(position, 1, val);
			return begin() + i;
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type	new_size(size() + n);

			if (n == 0)
				return;
			if (new_size > max_size())
				throw (std::length_error("vector::insert(iterator position, size_type n, const value_type& val)"));

			
			if (new_size > capacity())
			{
				difference_type	new_pos(position - begin());

				if (new_size <= capacity() * 2)
					reserve(capacity() * 2);
				else
					reserve(new_size);
				position = begin() + new_pos;
			}

			difference_type	range(new_size - size());

			_end = _data + new_size;
			for (iterator it(end() - difference_type(1)); (it - range) != position - difference_type(1); it--)
			{
				_alloc.destroy(&(*it));
				_alloc.construct(&(*it), *(it - range));
			}
			while (n--)
			{
				_alloc.destroy(&(*(position)));
				_alloc.construct(&(*position), val);
				position++;
			}
			return;
		}

		template <class InputIt>
    	void insert (iterator position, InputIt first, InputIt last,
			typename enable_if<!is_integral<InputIt>::value, InputIt >::type* = NULL)
		{
			if(!(is_input_iterator_tagged< typename iterator_traits<InputIt>::iterator_category >::value))
				throw std::invalid_argument("In ft::vector::insert(iterator position, InputIt first, InputIt last), InputIt class is'nt at least ft::InputIterator tagged");					//Faire mieux

			size_type	new_size(size() + (last - first));

			if (size() == new_size)
				return ;
			if (new_size > this->max_size())
				throw (std::length_error("vector::insert(iterator position, InputIt first, InputIt last)"));

			if (new_size > capacity())
			{
				difference_type	new_pos(position - begin());

				if (new_size <= capacity() * 2)
					reserve(capacity() * 2);
				else
					reserve(new_size);
				position = begin() + new_pos;
			}

			difference_type	range(new_size - size());

			_end = _data + new_size;
			for (iterator it(end() - difference_type(1)); (it - range) != position - difference_type(1); it--)
			{
				_alloc.destroy(&(*it));
				_alloc.construct(&(*it), *(it - range));
			}
			while (first != last)
			{
				_alloc.destroy(&(*(position)));
				_alloc.construct(&(*position), *(first++));
				position++;
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
			difference_type	diff(last - first);
			pointer			ptr(&(*first));

			for (int i = 0; i < diff ; i++, first++)
				_alloc.destroy(&(*first));
			for (int i = 0; ptr + i < _end - diff; i++)
			{
				_alloc.construct(ptr + i, *(ptr + diff + i));
				_alloc.destroy(ptr + diff + i);
			}
			_end -= diff;
			return iterator(ptr);
		}

		void swap(vector& x)
		{
			if (*this != x)
			{
				allocator_type	tmp_alloc = x._alloc;
				pointer			tmp_data = x._data;
				pointer			tmp_end = x._end;
				pointer			tmp_capacity = x._capacity;

				x._alloc = _alloc;
				x._data = _data;
				x._end = _end;
				x._capacity = _capacity;

				_alloc = tmp_alloc;
				_data = tmp_data;
				_end = tmp_end;
				_capacity = tmp_capacity;
			}
			return ;
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
			_end = _data;
			_capacity = _data + n;
		}

		void	_deallocate()
		{
			_alloc.deallocate(_data, capacity());
			_data = NULL;	_end = NULL;	_capacity = NULL;
		}

	};

	template < class T, class Alloc >
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		typename ft::vector<T>::const_iterator	first1 = lhs.begin();
		typename ft::vector<T>::const_iterator	first2 = rhs.begin();

		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	template < class T, class Alloc >
 	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template < class T, class Alloc >
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template < class T, class Alloc >
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template < class T, class Alloc >
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template < class T, class Alloc >
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
