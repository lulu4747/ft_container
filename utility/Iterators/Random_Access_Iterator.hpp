#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "Iterator.hpp"

namespace	ft
{
	template< typename T >
	class Random_Access_Iterator : public iterator_traits< Iterator< Random_Access_Iterator_tag, T > >
	{

	public:

		typedef T							value_type;
    	typedef value_type*					pointer;
    	typedef value_type const *			const_pointer;
    	typedef value_type&					reference;
    	typedef value_type const &			const_reference;
    	typedef std::ptrdiff_t				difference_type;
		typedef Random_Access_Iterator_tag	iterator_category;

		Random_Access_Iterator():_ptr(NULL)	{}
		Random_Access_Iterator(pointer ptr):_ptr(ptr) {}
		Random_Access_Iterator(Random_Access_Iterator const & src):_ptr(src._ptr)	{}
		virtual	~Random_Access_Iterator()	{}

		Random_Access_Iterator&	operator=(Random_Access_Iterator const & rhs)
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

		Random_Access_Iterator operator++(int)
		{
			Random_Access_Iterator 	tmp(*this);

			++_ptr;
			return tmp;
		}

		Random_Access_Iterator& operator++()
		{
			++_ptr;
			return *this;
		}

		Random_Access_Iterator operator--(int)
		{
			Random_Access_Iterator 	tmp(*this);

			--_ptr;
			return tmp;
		}

		Random_Access_Iterator& operator--()
		{
			--_ptr;
			return *this;
		}

		Random_Access_Iterator& operator+=(int value)
		{
			_ptr += value;
			return *this;
		}

		Random_Access_Iterator operator+(int value)
		{
			Random_Access_Iterator tmp(this->_ptr + value);

			return tmp;
		}

		Random_Access_Iterator& operator-=(int value)
		{
			_ptr -= value;
			return *this;
		}

		Random_Access_Iterator operator-(int value)
		{
			Random_Access_Iterator	tmp(this->_ptr - value);

			return tmp;
		}

		difference_type operator-(Random_Access_Iterator const &rhs) const
		{
			return (_ptr - rhs._ptr);
		}

		bool operator==(Random_Access_Iterator const &rhs) const
		{
			return (_ptr == rhs._ptr);
		}

		bool operator!=(Random_Access_Iterator const &rhs) const
		{
			return (_ptr != rhs._ptr);
		}

		bool operator<(Random_Access_Iterator const &rhs) const
		{
			return (_ptr < rhs._ptr);
		}

		bool operator<=(Random_Access_Iterator const &rhs) const
		{
			return (_ptr <= rhs._ptr);
		}

		bool operator>(Random_Access_Iterator const &rhs) const
		{
			return (_ptr > rhs._ptr);
		}

		bool operator>=(Random_Access_Iterator const &rhs) const
		{
			return (_ptr >= rhs._ptr);
		}

	protected:

		pointer	_ptr;

	};
}

#endif