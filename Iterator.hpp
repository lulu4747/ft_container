#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>
# include "ft.hpp"

namespace ft
{

    struct	input_iterator_tag{};
    struct	output_iterator_tag{};
    struct	forward_iterator_tag : public input_iterator_tag {};
    struct	bidirectional_iterator_tag : public forward_iterator_tag {};
    struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iterator{

		typedef T         value_type;
    	typedef Distance  difference_type;
    	typedef Pointer   pointer;
    	typedef Reference reference;
    	typedef Category  iterator_category;
	};

	template <class Iterator>
	class	iterator_traits
	{
		typedef	typename	Iterator::difference_type	difference_type;
    	typedef typename	Iterator::value_type		value_type;
    	typedef typename	Iterator::pointer			pointer;
    	typedef typename	Iterator::reference			reference;
    	typedef typename	Iterator::iterator_category	iterator_category;
  	};

	template <class T>
	class	iterator_traits<T*>
	{
		typedef	std::ptrdiff_t				difference_type;
    	typedef	T							value_type;
    	typedef	T*							pointer;
    	typedef	T&							reference;
    	typedef	random_access_iterator_tag	iterator_category;
  	};

	template <class T>
	class	iterator_traits<const T*>
	{
		typedef	std::ptrdiff_t				difference_type;
    	typedef	T							value_type;
    	typedef	const T*					pointer;
    	typedef	const T&					reference;
    	typedef	random_access_iterator_tag	iterator_category;
  	};

	//	Random Access Iterator :

	template <class T, class Category = random_access_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class ft_Iterator : public iterator_traits<Iterator<Category, T, Distance, Pointer, Reference> >{
	
	public:

		ft_Iterator<Category, T, Distance, Pointer, Reference> ( void ){}
		ft_Iterator<Category, T, Distance, Pointer, Reference> ( ft_Iterator const & src )
			{	*this = src;	}
		
		ft_Iterator<Category, T, Distance, Pointer, Reference> ( Pointer ptr )
			:	_current(ptr)	{}

		ft_Iterator &	operator=( ft_Iterator const & rhs )
		{
			if (this != &rhs)
				this->_current = rhs.getCurrent();
			return *this;
		}

			// Equivalence :

		bool	operator==(  ft_Iterator const & rhs ) const
			{	return this->_current == rhs.getCurrent();	}
		
		bool	operator!=(  ft_Iterator const & rhs ) const
			{	return this->_current != rhs.getCurrent();	}

			// Relationnal :

		bool	operator<(  ft_Iterator const & rhs ) const
			{	return this->_current < rhs.getCurrent();	}
		
		bool	operator<=(  ft_Iterator const & rhs ) const
			{	return this->_current <= rhs.getCurrent();	}

		bool	operator>(  ft_Iterator const & rhs ) const
			{	return this->_current == rhs.getCurrent();	}
		
		bool	operator>=(  ft_Iterator const & rhs ) const
			{	return this->_current >= rhs.getCurrent();	}

			//	Dereference
		
		Reference	operator*( void )
			{	return &(this->*_current);	}

	private:

		Pointer	_current;

		Pointer	getCurrent( void ) const
		{	return this->_current;	}

		//	test friend operator
		
	};
	
}

#endif
