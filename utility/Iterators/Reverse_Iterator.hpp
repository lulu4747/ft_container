#ifndef	REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "Iterator.hpp"

namespace	ft
{
	template < class Iter >
	class	Reverse_Iterator : public Iter
	{

	public:

		typedef	Iter	iterator_type;

		typedef typename	iterator_traits<Iter>::difference_type		difference_type;
		typedef typename	iterator_traits<Iter>::value_type			value_type;
		typedef typename	iterator_traits<Iter>::pointer				pointer;
		typedef typename	iterator_traits<Iter>::reference			reference;
		typedef typename	iterator_traits<Iter>::iterator_category	iterator_category;

		Reverse_Iterator()
			:current()
		{}

		Reverse_Iterator( iterator_type x )
			:current(x)
		{}

		template< class U >
		Reverse_Iterator( const Reverse_Iterator<U>& other )
			:current(other.base())
		{}

		template< class U >
		Reverse_Iterator& operator=( const Reverse_Iterator<U>& other )
		{
			if (this != &other)
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

		Reverse_Iterator& operator++()
		{
			return current--;
		}

		Reverse_Iterator& operator--()
		{
			return current++;
		}

		Reverse_Iterator operator++( int )
		{
			Reverse_Iterator	tmp(current);

			--current;
			return tmp;
		}

		Reverse_Iterator operator--( int )
		{
			Reverse_Iterator	tmp(current);

			++current;
			return tmp;
		}

		Reverse_Iterator operator+( difference_type n ) const
		{
			Reverse_Iterator	tmp(current - n);

			return tmp;
		}

		Reverse_Iterator operator-( difference_type n ) const
		{
			Reverse_Iterator	tmp(current + n);

			return tmp;
		}

		Reverse_Iterator& operator+=( difference_type n )
		{
			current -= n;
			return *this;
		}

		Reverse_Iterator& operator-=( difference_type n )
		{
			current += n;
			return *this;
		}

	protected:

		iterator_type	current;

	};
}

#endif
