#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "Iterator.hpp"

namespace	ft
{
	template< typename T >
	class Random_Access_Iterator : Iterator< Random_Access_Iterator_tag, T >
	{

	public:

		typedef typename Iterator< Random_Access_Iterator_tag, T >::value_type			value_type;
    	typedef typename Iterator< Random_Access_Iterator_tag, T >::difference_type		difference_type;
		typedef typename Iterator< Random_Access_Iterator_tag, T >::iterator_category	iterator_category;
    	typedef value_type*																pointer;
    	typedef value_type&																reference;

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

		operator Random_Access_Iterator<const value_type> () const
		{
			return Random_Access_Iterator<const value_type>(this->_ptr);
		}

		pointer	base() const
		{
			return _ptr;
		}

		reference	operator*()
		{
			return *(_ptr);
		}

		pointer	operator->()
		{
			return &(this->operator*());
		}

		reference	operator[](difference_type index)
		{
			return *(_ptr + index);
		}

		Random_Access_Iterator& operator++()
		{
			++_ptr;
			return *this;
		}

		Random_Access_Iterator operator++(int)
		{
			Random_Access_Iterator 	tmp(*this);

			operator++();
			return tmp;
		}

		Random_Access_Iterator& operator--()
		{
			--_ptr;
			return *this;
		}

		Random_Access_Iterator operator--(int)
		{
			Random_Access_Iterator 	tmp(*this);

			operator--();
			return tmp;
		}

		Random_Access_Iterator& operator+=(difference_type value)
		{
			_ptr += value;
			return *this;
		}

		Random_Access_Iterator operator+(difference_type value) const
		{
			return _ptr + value;
		}
		
		friend Random_Access_Iterator	operator+(const difference_type n, const Random_Access_Iterator& rai)
		{
			return Random_Access_Iterator(rai._ptr + n);
		}

		Random_Access_Iterator& operator-=(difference_type value)
		{
			_ptr -= value;
			return *this;
		}

		Random_Access_Iterator operator-(difference_type value) const
		{
			return _ptr - value;
		}

	protected:

		pointer	_ptr;

	};

	template <typename T>
	typename ft::Random_Access_Iterator<T>::difference_type
	operator==(const ft::Random_Access_Iterator<T> lhs, const ft::Random_Access_Iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::Random_Access_Iterator<T_L>::difference_type
	operator==(const ft::Random_Access_Iterator<T_L> lhs, const ft::Random_Access_Iterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	typename ft::Random_Access_Iterator<T>::difference_type
	operator!=(const ft::Random_Access_Iterator<T> lhs, const ft::Random_Access_Iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::Random_Access_Iterator<T_L>::difference_type
	operator!=(const ft::Random_Access_Iterator<T_L> lhs, const ft::Random_Access_Iterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	typename ft::Random_Access_Iterator<T>::difference_type
	operator<(const ft::Random_Access_Iterator<T> lhs, const ft::Random_Access_Iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::Random_Access_Iterator<T_L>::difference_type
	operator<(const ft::Random_Access_Iterator<T_L> lhs, const ft::Random_Access_Iterator<T_R> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	typename ft::Random_Access_Iterator<T>::difference_type
	operator>(const ft::Random_Access_Iterator<T> lhs, const ft::Random_Access_Iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::Random_Access_Iterator<T_L>::difference_type
	operator>(const ft::Random_Access_Iterator<T_L> lhs, const ft::Random_Access_Iterator<T_R> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	typename ft::Random_Access_Iterator<T>::difference_type
	operator<=(const ft::Random_Access_Iterator<T> lhs, const ft::Random_Access_Iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::Random_Access_Iterator<T_L>::difference_type
	operator<=(const ft::Random_Access_Iterator<T_L> lhs, const ft::Random_Access_Iterator<T_R> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	typename ft::Random_Access_Iterator<T>::difference_type
	operator>=(const ft::Random_Access_Iterator<T> lhs, const ft::Random_Access_Iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::Random_Access_Iterator<T_L>::difference_type
	operator>=(const ft::Random_Access_Iterator<T_L> lhs, const ft::Random_Access_Iterator<T_R> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename T>
	typename ft::Random_Access_Iterator<T>::difference_type
	operator-(const ft::Random_Access_Iterator<T> lhs, const ft::Random_Access_Iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::Random_Access_Iterator<T_L>::difference_type
	operator-(const ft::Random_Access_Iterator<T_L> lhs, const ft::Random_Access_Iterator<T_R> rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif