#ifndef SET_TEST_HPP
# define SET_TEST_HPP

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <set>
	#include <vector>
	#include <utility>
	namespace ft = std;
#else
	#include <set.hpp>
	#include <vector.hpp>
	#include <algorithm.hpp>
	#include <functionnal.hpp>
	#include <pair.hpp>
	#include <type_trait.hpp>
#endif

# include <iostream>
# include <stdlib.h>

template<typename Iter>
std::string	printPair(Iter &it)
{
	std::cout << *it;
	return ("");
}

template <typename T_SET>
void	printSize(T_SET const &mp, bool print_content = 0)
{
	std::cout << "size: " << mp.size() << std::endl;
	if (print_content)
	{
		typename T_SET::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <class SET>
void test_bound(SET &mp ,const typename SET::key_type &k)
{
	typedef typename SET::iterator iterator;

	iterator it; 
	it = mp.lower_bound(k);
	std::cout << "lower bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	it = mp.upper_bound(k);
	std::cout << "upper bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	ft::pair<iterator,iterator> ret;

	ret = mp.equal_range(k);
	std::cout << "equal_range = ";
	if (ret.first == mp.end())
		std::cout << "end()";
	else
		printPair(ret.first);
	std::cout << ", ";
	if (ret.second == mp.end())
		std::cout << "end()";
	else
		printPair(ret.second);

	std::cout << std::endl;
	std::cout << "###############################################" << std::endl;
}


template <class SET>
void test_const_bound(SET &mp ,const typename SET::key_type &k)
{
	typedef typename SET::const_iterator iterator;

	iterator it; 
	it = mp.lower_bound(k);
	std::cout << "lower bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	it = mp.upper_bound(k);
	std::cout << "upper bound = ";
	if (it == mp.end())
		std::cout << "end()";
	else
		printPair(it);
	std::cout << std::endl;

	ft::pair<iterator,iterator> ret;

	ret = mp.equal_range(k);
	std::cout << "equal_range = ";
	if (ret.first == mp.end())
		std::cout << "end()";
	else
		printPair(ret.first);
	std::cout << ", ";
	if (ret.second == mp.end())
		std::cout << "end()";
	else
		printPair(ret.second);

	std::cout << std::endl;
	std::cout << "###############################################" << std::endl;
}

template <class SET, class value_type>
void	test_simple_insert(SET &mp, value_type add)
{
	typedef typename SET::const_iterator iterator;
	
	ft::pair<iterator, bool> ret_insert;
	ret_insert = mp.insert(add);
	if (ret_insert.first != mp.end())
		std::cout << "value :" << ret_insert.first;
	else
		std::cout << "end()";
	std::cout << " is add " << ret_insert.second << '\n';
	ret_insert = mp.insert(add);
	
	if (ret_insert.first != mp.end())
		std::cout << "value :" << ret_insert.first;
	else
		std::cout << "end()";
	std::cout << " is add " << ret_insert.second << '\n';
	std::cout << "###############################################" << std::endl;

}

template <class SET, class ite>
void	test_range_insert(SET &mp, ite begin, ite end)
{
	mp.insert(begin, end);
	std::cout << "###############################################" << std::endl;

}

template <class SET>
void	erase_key(SET &mp, size_t len = 10000)
{
	size_t ret = 0;
	for (size_t i = 0; i != len; i++)
		ret += mp.erase(rand() % 10000);
	std::cout << "erased key :" << ret << std::endl;
	std::cout << "###############################################" << std::endl;
}
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

template< class SET >
void	cmp(const SET &lhs, const SET &rhs)
{
	typedef	typename	SET::const_iterator	iterator;

	iterator	left_it = lhs.begin();
	iterator	left_end = lhs.end();
	iterator	right_it = rhs.begin();
	iterator	right_end = rhs.end();

	std::cout << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << "*left_it == *right_it	: " << (*left_it == *right_it)
			<< "*left_it != *right_it	: " << (*left_it != *right_it)
			<< "*left_it <= *right_it	: " << (*left_it <= *right_it)
			<< "*left_it < *right_it	: " << (*left_it < *right_it)
			<< "*left_it >= *right_it	: " << (*left_it >= *right_it)
			<< "*left_it > *right_it	: " << (*left_it > *right_it);
		left_it++;
		right_it++;
	}
	if (left_it != left_end || right_it != right_end)
		std::cout << " left.end() != right.end() " << std::endl;
	else
		std::cout << " left.end() == right.end() " << std::endl;
	return;
}

template< class L_SET, class R_SET >
void	cmp(const L_SET &lhs, const R_SET &rhs)
{
	typedef	typename	L_SET::iterator	l_iterator;
	typedef	typename	R_SET::iterator	r_iterator;

	l_iterator	left_it = lhs.begin();
	l_iterator	left_end = lhs.end();
	r_iterator	right_it = rhs.begin();
	r_iterator	right_end = rhs.end();

	std::cout << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << "*left_it == *right_it	: " << (*left_it == *right_it)
			<< "*left_it != *right_it	: " << (*left_it != *right_it)
			<< "*left_it <= *right_it	: " << (*left_it <= *right_it)
			<< "*left_it < *right_it	: " << (*left_it < *right_it)
			<< "*left_it >= *right_it	: " << (*left_it >= *right_it)
			<< "*left_it > *right_it	: " << (*left_it > *right_it);
		left_it++;
		right_it++;
	}
	if (left_it != left_end || right_it != right_end)
		std::cout << " left.end() != right.end() " << std::endl;
	else
		std::cout << " left.end() == right.end() " << std::endl;
	return;
}

template < class SET >
void	print_content(const SET &mp)
{
	typename	SET::const_iterator	it(mp.begin());
	typename	SET::const_iterator	end(mp.end());

	for (;it != end; it++)
	{
		std::cout << "	|" << *it << "|";
	}
	std::cout << std::endl;
}

template < class SET >
void	print_attributes(const SET &mp)
{
	std::cout << "mp.empty() =	" << mp.empty() << std::endl
		<< "mp.size() =	" << mp.size() << std::endl
		<< "content :" << std::endl;
		print_content(mp);
		std::cout << std::endl;
}

#endif
