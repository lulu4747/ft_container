#ifndef VECTOR_TEST_HPP
# define VECTOR_TEST_HPP

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <utility>
	namespace ft = std;
#else
	#include <vector.hpp>
	#include <algorithm.hpp>
	#include <pair.hpp>
	#include <functionnal.hpp>
	#include <type_trait.hpp>
#endif

#include <iostream>
#include <string>


#ifndef SEED
	# define SEED 10
#endif

#ifndef LEN
	# define LEN rand() % 1000000
#endif

template <class V>
size_t rand_size(const V& v)
{
	if (v.size() == 0)
		return 0;
	size_t ret = rand() % (v.size());

	if ( ret > v.size() )
		return 0;
	return ret;
}

template<class T_VEC>
void	erase_rand_el(T_VEC & v, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		v.erase(v.begin() + rand() % v.size());
	}
}

template<class T_VEC, class T>
void	insert_rand_el(T_VEC & v, size_t n, const T & x)
{
	for (size_t i = 0; i < n; i++)
	{
		std::cout << i << std::endl;
		v.insert(v.begin() + rand() % v.size(), x);
	}
}


template<class IT>
void	print_it(IT first, IT last)
{
	for (; first != last; first++)
	{
		std::cout << *first << std::endl;
	}
	std::cout << "###############################################]" << std::endl;
}

/*
**			Compare Functions				**
*/

template< class VEC >
void	cmp(const VEC &lhs, const VEC &rhs)
{
	typedef	typename	VEC::const_iterator	iterator;

	iterator	left_it = lhs.begin();
	iterator	left_end = lhs.end();
	iterator	right_it = rhs.begin();
	iterator	right_end = rhs.end();

	std::cout << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.max_size() == right.max_size()	: " << (lhs.max_size() == rhs.max_size()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl
		<< "left.capacity() == right.capacity()	: " << (lhs.capacity() == rhs.capacity()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << "*left_it == *right_it	: " << (*left_it == *right_it) << std::endl
			<< "*left_it != *right_it	: " << (*left_it != *right_it) << std::endl
			<< "*left_it <= *right_it	: " << (*left_it <= *right_it) << std::endl
			<< "*left_it < *right_it	: " << (*left_it < *right_it) << std::endl
			<< "*left_it >= *right_it	: " << (*left_it >= *right_it) << std::endl
			<< "*left_it > *right_it	: " << (*left_it > *right_it) << std::endl << std::endl;
		left_it++;
		right_it++;
	}
	if (left_it != left_end || right_it != right_end)
		std::cout << " left.end() != right.end() " << std::endl;
	else
		std::cout << " left.end() == right.end() " << std::endl;
	return;
}

template< class L_VEC, class R_VEC >
void	cmp(const L_VEC &lhs, const R_VEC &rhs)
{
	typedef	typename	L_VEC::iterator	l_iterator;
	typedef	typename	R_VEC::iterator	r_iterator;

	l_iterator	left_it = lhs.begin();
	l_iterator	left_end = lhs.end();
	r_iterator	right_it = rhs.begin();
	r_iterator	right_end = rhs.end();

	std::cout << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.max_size() == right.max_size()	: " << (lhs.max_size() == rhs.max_size()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl
		<< "left.capacity() == right.capacity()	: " << (lhs.capacity() == rhs.capacity()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << "*left_it == *right_it	: " << (*left_it == *right_it) << std::endl
			<< "*left_it != *right_it	: " << (*left_it != *right_it) << std::endl
			<< "*left_it <= *right_it	: " << (*left_it <= *right_it) << std::endl
			<< "*left_it < *right_it	: " << (*left_it < *right_it) << std::endl
			<< "*left_it >= *right_it	: " << (*left_it >= *right_it) << std::endl
			<< "*left_it > *right_it	: " << (*left_it > *right_it) << std::endl << std::endl;
		left_it++;
		right_it++;
	}
	if (left_it != left_end || right_it != right_end)
		std::cout << " left.end() != right.end() " << std::endl;
	else
		std::cout << " left.end() == right.end() " << std::endl;
	return;
}

template < class VEC >
void	print_content(const VEC &vec)
{
	typename	VEC::const_iterator	it(vec.begin());
	typename	VEC::const_iterator	end(vec.end());

	for (;it != end; it++)
	{
		std::cout << "	|" << *it << "|";
	}
	std::cout << std::endl;
}

template < class VEC >
void	print_attributes(const VEC &vec)
{
	std::cout << "vec.empty() =	" << vec.empty() << std::endl
		<< "vec.max_size() =	" << vec.max_size() << std::endl
		<< "vec.size() =	" << vec.size() << std::endl
		<< "vec.capacity() =	" << vec.capacity() << std::endl
		<< "content :" << std::endl;
		print_content(vec);
		std::cout << std::endl;
}

#endif
