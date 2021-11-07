#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "ft.hpp"
# include "Iterator.hpp"

namespace	ft
{

	template< typename T>
	class VectorIterator
	{

	public:

		typedef T					value_type;
    	typedef value_type*			pointer;
    	typedef value_type const *	const_pointer;
    	typedef value_type&			reference;
    	typedef value_type const &	const_reference;
    	typedef std::ptrdiff_t		difference_type;

		VectorIterator():_ptr(NULL)	{}
		VectorIterator(pointer ptr):_ptr(ptr) {}
		VectorIterator(VectorIterator const & src):_ptr(src._ptr)	{}
		virtual	~VectorIterator()	{}

		VectorIterator&	operator=(VectorIterator const & rhs)
		{
			if (this != &rhs)
				this->_ptr = rhs._ptr;
			return *this;
		}

		reference	operator*()
		{
			return *(this->_ptr);
		}

		const_reference	operator*() const
		{
			return *(this->_ptr);
		}

		pointer	operator->()
		{
			return this->_ptr;
		}

		const_pointer	operator->() const
		{
			return this->_ptr;
		}

		reference	operator[](size_t index)
		{
			return *(this->_ptrtr + index);
		}

		const_reference	operator[](size_t index) const
		{
			return *(this->_ptrtr + index);
		}

		VectorIterator operator++(int)
		{
			VectorIterator 	tmp(*this);

			++this->_ptr;
			return tmp;
		}

		VectorIterator& operator++()
		{
			++this->_ptr;
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator 	tmp(*this);

			--this->_ptr;
			return tmp;
		}

		VectorIterator& operator--()
		{
			--this->_ptr;
			return *this;
		}

		VectorIterator& operator+=(int value)
		{
			this->_ptr += value;
			return *this;
		}

		VectorIterator operator+(int value)
		{
			VectorIterator	tmp(*this);

			return tmp + value;
		}

		VectorIterator& operator-=(int value)
		{
			this->_ptr -= value;
			return *this;
		}

		VectorIterator operator-(int value)
		{
			VectorIterator	tmp(*this);

			return tmp - value;
		}

		difference_type operator-(VectorIterator const &rhs) const
		{
			return (this->_ptr - rhs._ptr);
		}

		bool operator==(VectorIterator const &rhs) const
		{
			return (this->_ptr == rhs._ptr);
		}

		bool operator!=(VectorIterator const &rhs) const
		{
			return (this->_ptr != rhs._ptr);
		}

		bool operator<(VectorIterator const &rhs) const
		{
			return (this->_ptr < rhs._ptr);
		}

		bool operator<=(VectorIterator const &rhs) const
		{
			return (this->_ptr <= rhs._ptr);
		}

		bool operator>(VectorIterator const &rhs) const
		{
			return (this->_ptr > rhs._ptr);
		}

		bool operator>=(VectorIterator const &rhs) const
		{
			return (this->_ptr >= rhs._ptr);
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
		:_alloc(alloc)
		{
			this->_allocate(n);
			for (size_type i = 0; i < n; i++)
				this->_data[i] = val;
			this->_back = this->_data + n;
			this->_last = this->_back;
		}

		template <class iterator>
		Vector (iterator first, iterator last, const allocator_type& alloc = allocator_type());

		Vector (const Vector& x);

		virtual	~Vector()
		{
			this->clear();
		}

		// Element Access

		reference	at( size_type n )
		{
			if ( n > this->size() )
				throw	std::out_of_range("vector");
			return this->_data[n];
		}

		reference	operator[]( size_type n )
		{
			return this->_data[n];
		}

		reference	front( void )
		{
			return this->*_data;
		}

		reference	back( void )
		{
			return	this->*_back;
		}

		pointer		data( void )
		{
			return	this->_data;
		}

		//	Iterators

		iterator	begin( void )
		{
			return	iterator(this->_data);
		}

		iterator	end( void )
		{
			return	iterator(this->_back);
		}

		// Capacity

		bool		empty( void )
		{
			return this->_data == NULL;
		}

		size_type	size( void )
		{
			if (!this->_data)
				return 0;
			return this->_back - this->_data;
		}

		size_type	capacity( void )
		{
			if (!this->_data)
				return 0;
			return this->_last - this->_data;
		}

		void	assign(size_type count, const T& value)
		{
			this->clear();
			this->reserve(count);
			for (size_type i = 0; i < count; i++)
				this->_data[i] = value;
		}

		void	assign(iterator first, iterator last)
		{
			this->clear();
			this->reserve(last - first);
			for (iterator it = this->begin(); it++ && first++; first != last)
				it = first;
		}

		void	reserve(size_type n)
		{
			if (!this->_data)
			{
				this->_allocate(n);
				this->_back = this->_data + n;
				this->_last = this->_back;
			}
			else if (this->capacity() > n)
			{
				pointer		tmp = this->_data;
				size_type	size = this->size();

				this->_allocate(n);
				this->_back = this->_data + n;
				this->_last = this->_back;
				for (size_type i = 0; i < size; i++)
				{
					this->_data[i] = tmp[i];
					tmp[i].~value_type();
				}
			}
		}

		void	clear()
		{
			pointer		tmp = this->_data;

			while (tmp != this->_last)
			{
				tmp++;
				this->_data->~value_type();
				this->_data = tmp;
			}
			this->_data->~value_type();
			this->_data = NULL;
			this->_back = NULL;
			this->_last = NULL;
		}

	protected:

		allocator_type	_alloc;

		pointer			_data;
		pointer			_back;
		pointer			_last;

	private:

		void	_allocate(size_type n)
		{
			this->_data = this->_alloc.allocate(sizeof(value_type) * n);
		}

	};
}

#endif