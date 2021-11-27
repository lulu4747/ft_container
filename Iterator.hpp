#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>
# include "ft.hpp"

namespace ft
{

	struct	output_iterator_tag{};
	struct	input_iterator_tag{};
	struct	forward_iterator_tag : public input_iterator_tag {};
	struct	bidirectional_iterator_tag : public forward_iterator_tag {};
	struct	RandomAccessIterator_tag : public bidirectional_iterator_tag {};

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
    	typedef	RandomAccessIterator_tag	iterator_category;
  	};

	template <class T>
	struct	iterator_traits<const T*>
	{
		typedef	std::ptrdiff_t				difference_type;
		typedef	T							value_type;
		typedef	const T*					pointer;
		typedef	const T&					reference;
		typedef	RandomAccessIterator_tag	iterator_category;
  	};

	template <class T>
	struct is_input_iterator_tagged
	{ 
		static const bool value = false;
	};

	template <> struct is_input_iterator_tagged<input_iterator_tag> { static const bool value = true; };
	template <> struct is_input_iterator_tagged<forward_iterator_tag> { static const bool value = true; };
	template <> struct is_input_iterator_tagged<bidirectional_iterator_tag> { static const bool value = true; };
	template <> struct is_input_iterator_tagged<RandomAccessIterator_tag> { static const bool value = true; };

	template< typename T>
	class RandomAccessIterator : public iterator_traits< Iterator< RandomAccessIterator_tag, T > >
	{

	public:

		typedef T							value_type;
    	typedef value_type*					pointer;
    	typedef value_type const *			const_pointer;
    	typedef value_type&					reference;
    	typedef value_type const &			const_reference;
    	typedef std::ptrdiff_t				difference_type;
		typedef RandomAccessIterator_tag	iterator_category;

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
			if (this != other)
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
