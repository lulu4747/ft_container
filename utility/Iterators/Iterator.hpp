#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>

namespace ft
{

	struct	Output_Iterator_tag{};
	struct	Input_Iterator_tag{};
	struct	Forward_Iterator_tag : public Input_Iterator_tag {};
	struct	Bidirectional_Iterator_tag : public Forward_Iterator_tag {};
	struct	Random_Access_Iterator_tag : public Bidirectional_Iterator_tag {};

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
    	typedef	Random_Access_Iterator_tag	iterator_category;
  	};

	template <class T>
	struct	iterator_traits<const T*>
	{
		typedef	std::ptrdiff_t				difference_type;
		typedef	T							value_type;
		typedef	const T*					pointer;
		typedef	const T&					reference;
		typedef	Random_Access_Iterator_tag	iterator_category;
  	};
}

#endif