#ifndef	REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "Iterator.hpp"

namespace	ft
{
	template < class Iterator >
	class	Reverse_Iterator
	{

	public:

		typedef	Iterator	iterator_type;

		typedef typename	iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename	iterator_traits<iterator_type>::value_type			value_type;
		typedef typename	iterator_traits<iterator_type>::pointer				pointer;
		typedef typename	iterator_traits<iterator_type>::reference			reference;
		typedef typename	iterator_traits<iterator_type>::iterator_category	iterator_category;

		Reverse_Iterator()
			:it()
		{}

		Reverse_Iterator( iterator_type x )
			:it(x)
		{}

		template< class U >
		Reverse_Iterator( const Reverse_Iterator<U>& other )
			:it(other.base())
		{}

		template< class U >
		Reverse_Iterator& operator=( const Reverse_Iterator<U>& other )
		{
			if (this->base() != other.base())
				it = other.base();
			return *this;
		}

		iterator_type base() const
		{
			return it;
		}

		reference operator*() const
		{
			return *(--iterator_type(it));
		}

		pointer operator->() const
		{
			return &operator*();
		}

		reference	operator[]( difference_type n ) const
		{
			return base()[-n-1];
		}

		Reverse_Iterator& operator++()
		{
			it--;
			return *this;
		}

		Reverse_Iterator& operator--()
		{
			it++;
			return *this;
		}

		Reverse_Iterator operator++( int )
		{
			return Reverse_Iterator(it--);
		}

		Reverse_Iterator operator--( int )
		{
			return Reverse_Iterator(it++);
		}

		Reverse_Iterator operator+( difference_type n ) const
		{
			return Reverse_Iterator(it - n);
		}

		friend	Reverse_Iterator operator+(const difference_type n, const Reverse_Iterator &rit)
		{
			return Reverse_Iterator(rit.it - n);
		}

		Reverse_Iterator operator-( difference_type n ) const
		{
			return Reverse_Iterator(it + n);
		}

		Reverse_Iterator& operator+=( difference_type n )
		{
			it -= n;
			return *this;
		}

		Reverse_Iterator& operator-=( difference_type n )
		{
			it += n;
			return *this;
		}

	protected:

		iterator_type	it;

	};

	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::difference_type
	operator==(const ft::Reverse_Iterator<Iterator> &lhs, const ft::Reverse_Iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<class Iterator_L, class Iterator_R>
	typename ft::Reverse_Iterator<Iterator_L>::difference_type
	operator==(const ft::Reverse_Iterator<Iterator_L> &lhs, const ft::Reverse_Iterator<Iterator_R> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::difference_type
	operator!=(const ft::Reverse_Iterator<Iterator> &lhs, const ft::Reverse_Iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<class Iterator_L, class Iterator_R>
	typename ft::Reverse_Iterator<Iterator_L>::difference_type
	operator!=(const ft::Reverse_Iterator<Iterator_L> &lhs, const ft::Reverse_Iterator<Iterator_R> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::difference_type
	operator<(const ft::Reverse_Iterator<Iterator> &lhs, const ft::Reverse_Iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<class Iterator_L, class Iterator_R>
	typename ft::Reverse_Iterator<Iterator_L>::difference_type
	operator<(const ft::Reverse_Iterator<Iterator_L> &lhs, const ft::Reverse_Iterator<Iterator_R> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::difference_type
	operator>(const ft::Reverse_Iterator<Iterator> &lhs, const ft::Reverse_Iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<class Iterator_L, class Iterator_R>
	typename ft::Reverse_Iterator<Iterator_L>::difference_type
	operator>(const ft::Reverse_Iterator<Iterator_L> lhs, const ft::Reverse_Iterator<Iterator_R> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::difference_type
	operator<=(const ft::Reverse_Iterator<Iterator> &lhs, const ft::Reverse_Iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<class Iterator_L, class Iterator_R>
	typename ft::Reverse_Iterator<Iterator_L>::difference_type
	operator<=(const ft::Reverse_Iterator<Iterator_L> &lhs, const ft::Reverse_Iterator<Iterator_R> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::difference_type
	operator>=(const ft::Reverse_Iterator<Iterator> lhs, const ft::Reverse_Iterator<Iterator> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<class Iterator_L, class Iterator_R>
	typename ft::Reverse_Iterator<Iterator_L>::difference_type
	operator>=(const ft::Reverse_Iterator<Iterator_L> &lhs, const ft::Reverse_Iterator<Iterator_R> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	typename ft::Reverse_Iterator<Iterator>::difference_type
	operator-(const ft::Reverse_Iterator<Iterator> &lhs, const ft::Reverse_Iterator<Iterator> &rhs)
	{
		return (-1 * (lhs.base() - rhs.base()));
	}

	template<class Iterator_L, class Iterator_R>
	typename ft::Reverse_Iterator<Iterator_L>::difference_type
	operator-(const ft::Reverse_Iterator<Iterator_L> &lhs, const ft::Reverse_Iterator<Iterator_R> &rhs)
	{
		return (-1 * (lhs.base() - rhs.base()));
	}
}

#endif
