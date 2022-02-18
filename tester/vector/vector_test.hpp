#ifndef VECTOR_TEST_HPP
# define VECTOR_TEST_HPP

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <utility>
	namespace ft = std;
#else
	#include <vector.hpp>
	#include <utility>
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

	std::cout << std::boolalpha << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.max_size() == right.max_size()	: " << (lhs.max_size() == rhs.max_size()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl
		<< "left.capacity() == right.capacity()	: " << (lhs.capacity() == rhs.capacity()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << std::boolalpha << "*left_it == *right_it	: " << (*left_it == *right_it) << std::endl
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

	std::cout << std::boolalpha << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.max_size() == right.max_size()	: " << (lhs.max_size() == rhs.max_size()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl
		<< "left.capacity() == right.capacity()	: " << (lhs.capacity() == rhs.capacity()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << std::boolalpha << "*left_it == *right_it	: " << (*left_it == *right_it) << std::endl
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

	for (int i = 0; it != end; it++)
	{
		std::cout << "	|" << *it << "|";
		if (i++ == 5)
			i = 0;
		else
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

template < class VEC >
void	print_attributes(const VEC &vec)
{
	std::cout << std::boolalpha << "vec.empty() =	" << vec.empty() << std::endl
		<< "vec.max_size() =	" << vec.max_size() << std::endl
		<< "vec.size() =	" << vec.size() << std::endl
		<< "vec.capacity() =	" << vec.capacity() << std::endl
		<< "content :" << std::endl;
		print_content(vec);
		std::cout << std::endl;
}
/*

template < typename VEC, typename IT > 
void	op_test(VEC &vec, IT &it, std::string &str_it)
{
	std::string	begin(str_it.find('r') == str_it.npos ? "begin" : "rbegin");


	std::cout << "----------Arithmetic operators----------" << std::endl
		<< "Mostly using \"operator*()\" to print output" << std::endl
		<< std::endl << str_it << " += " << vec.size() / 2 << " :			";

	std::cout << *(it += vec.size() / 2) << std::endl;

	std::cout << str_it << " + " << vec.size() / 5 << " :			";

	std::cout << *(it + vec.size() / 5) << std::endl;

	std::cout << str_it << " - " << vec.size() / 3 << " :			";

	std::cout << *(it - vec.size() / 3) << std::endl;

	std::cout << str_it << " - vector." << begin << "() :		";

	if (str_it.find('r') == str_it.npos)
		std::cout << (it - vec.begin()) << std::endl;
	else
		std::cout << (it - vec.rbegin()) << std::endl;

	std::cout << str_it << " -= " << vec.size() / 4 << " :			";

	std::cout << *(it -= vec.size() / 4) << std::endl;

	std::cout << str_it << " = vector." << begin << "() :	";

	if (str_it.find('r') == str_it.npos)
		std::cout << *(it = vec.begin()) << std::endl;
	else
		std::cout << *(it = vec.rbegin()) << std::endl;

	std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
		<< str_it << " == vector." << begin << "() ? :	";

	if (str_it.find('r') == str_it.npos)
	{
		std::cout << (it == vec.begin())
			<< str_it << " != vector." << begin << "() ? :	"
			<< (it != vec.begin()) << std::endl
			<< str_it << " <= vector." << begin << "() ? :	"
			<< (it <= vec.begin()) << std::endl
			<< str_it << " >= vector." << begin << "() ? :	"
			<< (it >= vec.begin()) << std::endl
			<< str_it << " < vector." << begin << "() ? :		"
			<< (it < vec.begin()) << std::endl
			<< str_it << " > vector." << begin << "() ? :		"
			<< (it > vec.begin()) << std::endl
			<< str_it << "++ == vector." << begin << "() ? :	"
			<< (it++ == vec.begin()) << std::endl
			<< str_it << " != vector." << begin << "() ? :	"
			<< (it != vec.begin()) << std::endl
			<< str_it << " <= vector." << begin << "() ? :	"
			<< (it <= vec.begin()) << std::endl
			<< str_it << " >= vector." << begin << "() ? :	"
			<< (it >= vec.begin()) << std::endl
			<< str_it << " < vector." << begin << "() ? :		"
			<< (it < vec.begin()) << std::endl
			<< str_it << " > vector." << begin << "() ? :		"
			<< (it > vec.begin()) << std::endl
			<< "--" << str_it << " == vector." << begin << "() ? :	"
			<< (--it == vec.begin()) << std::endl;
	}
	else
	{
		std::cout << (it == vec.rbegin())
			<< str_it << " != vector." << begin << "() ? :	"
			<< (it != vec.rbegin()) << std::endl
			<< str_it << " <= vector." << begin << "() ? :	"
			<< (it <= vec.rbegin()) << std::endl
			<< str_it << " >= vector." << begin << "() ? :	"
			<< (it >= vec.rbegin()) << std::endl
			<< str_it << " < vector." << begin << "() ? :		"
			<< (it < vec.rbegin()) << std::endl
			<< str_it << " > vector." << begin << "() ? :		"
			<< (it > vec.rbegin()) << std::endl
			<< str_it << "++ == vector." << begin << "() ? :	"
			<< (it++ == vec.rbegin()) << std::endl
			<< str_it << " != vector." << begin << "() ? :	"
			<< (it != vec.rbegin()) << std::endl
			<< str_it << " <= vector." << begin << "() ? :	"
			<< (it <= vec.rbegin()) << std::endl
			<< str_it << " >= vector." << begin << "() ? :	"
			<< (it >= vec.rbegin()) << std::endl
			<< str_it << " < vector." << begin << "() ? :		"
			<< (it < vec.rbegin()) << std::endl
			<< str_it << " > vector." << begin << "() ? :		"
			<< (it > vec.rbegin()) << std::endl
			<< "--" << str_it << " == vector." << begin << "() ? :	"
			<< (--it == vec.rbegin()) << std::endl;
	}

	std::cout << std::endl << "----------Access operators----------" << std::endl << std::endl
		<< str_it << "[" << vec.size() / 5 << "] :			";

	std::cout << (it[vec.size() / 5]) << std::endl;

	std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
		<< "iterator		tmp(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
	
	IT		tmp(it);

	std::cout << (it++ == tmp) << std::endl;

	std::cout << std::endl << "tmp = " << str_it << ";" << std::endl << str_it << "-- == tmp ? :	";

	tmp = it;

	std::cout << (it-- == tmp) << std::endl;

	std::cout << std::endl << "tmp = " << str_it << ";" << std::endl << "++" << str_it << " == tmp ? :	";

	tmp = it;

	std::cout << (++it == tmp) << std::endl;

	std::cout << std::endl << "tmp = " << str_it << ";" << std::endl << "--" << str_it << " == tmp ? :	";

	tmp = it;

	std::cout << (--it == tmp) << std::endl;
}*/

#endif
