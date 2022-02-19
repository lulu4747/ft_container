#ifndef MAP_TEST_HPP
# define MAP_TEST_HPP

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <vector>
	#include <utility>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <vector.hpp>
	#include <algorithm.hpp>
	#include <functionnal.hpp>
	#include <pair.hpp>
	#include <type_trait.hpp>
#endif

# include <iostream>
# include <stdlib.h>

#ifndef SEED
	# define SEED 10
#endif

#ifndef LEN
	# define LEN rand() % 1000000
#endif


template<typename Iter>
std::string	printPair(Iter &it)
{
	std::cout << it->first << " => " << it->second;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 0)
{
	std::cout << "size: " << mp.size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <class MAP>
void test_bound(MAP &mp ,const typename MAP::key_type &k)
{
	typedef typename MAP::iterator iterator;

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


template <class MAP>
void test_const_bound(MAP &mp ,const typename MAP::key_type &k)
{
	typedef typename MAP::const_iterator iterator;

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

template <class MAP, class value_type>
void	test_simple_insert(MAP &mp, value_type add)
{
	typedef typename MAP::const_iterator iterator;
	
	ft::pair<iterator, bool> ret_insert;
	ret_insert = mp.insert(add);
	if (ret_insert.first != mp.end())
		std::cout << "value :" << ret_insert.first->first;
	else
		std::cout << "end()";
	std::cout << " is add " << ret_insert.second << '\n';
	ret_insert = mp.insert(add);
	
	if (ret_insert.first != mp.end())
		std::cout << "value :" << ret_insert.first->first;
	else
		std::cout << "end()";
	std::cout << " is add " << ret_insert.second << '\n';
	std::cout << "###############################################" << std::endl;

}

template <class MAP, class ite>
void	test_range_insert(MAP &mp, ite begin, ite end)
{
	mp.insert(begin, end);
	std::cout << "###############################################" << std::endl;

}

template <class MAP>
void	erase_key(MAP &mp, size_t len = 10000)
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
		std::cout << first->first << std::endl;
	}
	std::cout << "###############################################]" << std::endl;
}

/*
**			Compare Functions				**
*/

template< class MAP >
void	cmp(const MAP &lhs, const MAP &rhs)
{
	typedef	typename	MAP::const_iterator	iterator;

	iterator	left_it = lhs.begin();
	iterator	left_end = lhs.end();
	iterator	right_it = rhs.begin();
	iterator	right_end = rhs.end();

	std::cout << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << "left_it->first == right_it->first	: " << (left_it->first == right_it->first)
			<< "left_it->first != right_it->first	: " << (left_it->first != right_it->first)
			<< "left_it->first <= right_it->first	: " << (left_it->first <= right_it->first)
			<< "left_it->first < right_it->first	: " << (left_it->first < right_it->first)
			<< "left_it->first >= right_it->first	: " << (left_it->first >= right_it->first)
			<< "left_it->first > right_it->first	: " << (left_it->first > right_it->first);
		left_it++;
		right_it++;
	}
	if (left_it != left_end || right_it != right_end)
		std::cout << " left.end() != right.end() " << std::endl;
	else
		std::cout << " left.end() == right.end() " << std::endl;
	return;
}

template< class L_MAP, class R_MAP >
void	cmp(const L_MAP &lhs, const R_MAP &rhs)
{
	typedef	typename	L_MAP::iterator	l_iterator;
	typedef	typename	R_MAP::iterator	r_iterator;

	l_iterator	left_it = lhs.begin();
	l_iterator	left_end = lhs.end();
	r_iterator	right_it = rhs.begin();
	r_iterator	right_end = rhs.end();

	std::cout << "left.empty() == right.empty()	: " << (lhs.empty() == rhs.empty()) << std::endl
		<< "left.size() == right.size()	: " << (lhs.size() == rhs.size()) << std::endl;
	
	while (left_it != left_end && right_it != right_end)
	{
		std::cout << "left_it->first == right_it->first	: " << (left_it->first == right_it->first)
			<< "left_it->first != right_it->first	: " << (left_it->first != right_it->first)
			<< "left_it->first <= right_it->first	: " << (left_it->first <= right_it->first)
			<< "left_it->first < right_it->first	: " << (left_it->first < right_it->first)
			<< "left_it->first >= right_it->first	: " << (left_it->first >= right_it->first)
			<< "left_it->first > right_it->first	: " << (left_it->first > right_it->first);
		left_it++;
		right_it++;
	}
	if (left_it != left_end || right_it != right_end)
		std::cout << " left.end() != right.end() " << std::endl;
	else
		std::cout << " left.end() == right.end() " << std::endl;
	return;
}

template < class MAP >
void	print_content(const MAP &mp)
{
	typename	MAP::const_iterator	it(mp.begin());
	typename	MAP::const_iterator	end(mp.end());

	for (;it != end; it++)
	{
		std::cout << "	|" << it->first << "|";
	}
	std::cout << std::endl;
}

template < class MAP >
void	print_attributes(const MAP &mp)
{
	std::cout << "mp.empty() =	" << mp.empty() << std::endl
		<< "mp.size() =	" << mp.size() << std::endl
		<< "content :" << std::endl;
		print_content(mp);
		std::cout << std::endl;
}

#endif
