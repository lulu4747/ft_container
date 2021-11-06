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

		VectorIterator():value(nullptr)	{}
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
			_alloc(alloc), _data(nullptr), _back(nullptr), _last(nullptr)
		{}

		explicit Vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		:_alloc(alloc)
		{
			_data = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_data[i] = val;
			_back = _data + n;
			_last = _back;
		}

		template <class iterator>
		Vector (iterator first, iterator last, const allocator_type& alloc = allocator_type());

		Vector (const Vector& x);

		~Vector();

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
			return	VectorIterator<value_type>(this->_data);
		}

		iterator	end( void )
		{
			return	VectorIterator<value_type>(this->_back);
		}

		// Capacity

		bool		empty( void )
		{
			return this->_data == nullptr;
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

		void	assign(iterator first, iterator last)
		{
			this->clear();
			this->reserve(last - first);
		}

		void	reserve(size_type n)
		{
			if (!this->_data)
			{
				this->_data.pointer(n);
				this->_back = this->_data;
				this->_last = this->_data + n;
			}
			else if (this->capacity() > n)
			{
				//voir plus en detail comment fonctionne cette fonction de mort
			}
		}

		void	clear()
		{
			pointer		tmp(this->_data);

			while (tmp != this->_last)
			{
				tmp++;
				this->_data.~pointer();
				this->_data = tmp;
			}
			this->_data.~pointer();
			this->_data(nullptr);
			this->_back(nullptr);
			this->_last(nullptr);
		}

	protected:

		allocator_type	const	_alloc;

		pointer					_data;
		pointer					_back;
		pointer					_last;

	};
}

#endif