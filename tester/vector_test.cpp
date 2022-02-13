#include <iostream>
#include <sys/time.h>
#include <vector>
#include "tester.hpp"
#include "../ft_containers/vector.hpp"


template < class FTV, class STLV >
static bool	content_compare(FTV &ft, STLV &stl)
{
	typename FTV::iterator	ftit(ft.begin());
	typename STLV::iterator	stlit(stl.begin());

	while (ftit != ft.end() && stlit != stl.end())
	{
		if (*ftit != *stlit)
			return false;
		ftit++;
		stlit++;
	}
	if (ftit != ft.end() || stlit != stl.end())
		return false;
	return true;
}

template < class FT, class STL >
static bool	vector_compare(FT &ft, STL &stl)
{
	bool	empty, max_size, size, capacity, content;

	std::cout << std::endl << "empty() comparison :	";
	empty = print_test_result(ft.empty() == stl.empty());
	std::cout << std::endl << "max_size() comparison :	";
	max_size = print_test_result(ft.max_size() == stl.max_size());
	std::cout << std::endl << "size() comparison :	";
	size = print_test_result(ft.size() == stl.size());
	std::cout << std::endl << "capacity() comparison :	";
	capacity = print_test_result(ft.capacity() == stl.capacity());
	std::cout << std::endl << "content comparison : 	";
	content = print_test_result(content_compare(ft, stl));
	std::cout << std::endl << "General comparison : 			";
	if (!empty || !max_size || !size || !capacity || !content)
		return false;
	return true;
}

static bool	vector_fill_constructor_test()
{
	int	n = 10, val = 8;
	std::cout << "_______________________________________________" << std::endl
		<< "assignation construction with n = " << n << ", val = " << val << std::endl << std::endl;

//
	struct timeval	start, end;
	double	ft_time, stl_time;
	gettimeofday(&start, nullptr);
//

	ft::vector<int>		ft(n, val);

//
	gettimeofday(&end, nullptr);
	ft_time = timeval_diff_to_ms(start, end);
	gettimeofday(&start, nullptr);
//
	std::vector<int>	stl(n, val);

//
	gettimeofday(&end, nullptr);
	stl_time = timeval_diff_to_ms(start, end);
//

	if (!(print_test_result(ft_time <= stl_time * 20)))
		return false;
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;
	return true;
}

static bool	vector_range_constructor_test()
{
	std::cout << "_______________________________________________" << std::endl
		<< "range construction" << std::endl << std::endl;
	std::vector<int> range(10, 10);

	ft::vector<int>::iterator	ft_iterator(range.data());
	std::vector<int>::iterator	stl_iterator(range.begin());

	ft::vector<int>		ft(ft_iterator, ft_iterator + 6);
	std::vector<int>	stl(stl_iterator, stl_iterator + 6);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;
	return true;
}

template < class FT, class STl >
static bool	vector_copy_constructor_test(FT &ft, STl &stl)
{
	std::cout << "_______________________________________________" << std::endl
		<< "copy construction" << std::endl << std::endl;

	ft::vector<int>		ft2(ft);
	std::vector<int>	stl2(stl);

	if (!(print_test_result(vector_compare(ft2, stl2))))
		return false;
	std::cout << std::endl;
	return true;
}

bool	vector_test()
{
	std::cout << "_______________________________________________" << std::endl
		<< "	vector" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::vector<int>		ft;
	std::vector<int>	stl;

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	if (vector_fill_constructor_test() == false)
		return false;

	if (vector_range_constructor_test() == false)
		return false;

	std::cout << "_______________________________________________" << std::endl
		<< "vector.push_back(0) with empty vector :	" << std::endl;
	ft.push_back(0);
	stl.push_back(0);
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	std::cout << "_______________________________________________" << std::endl
		<< "vector.pop_back() :	" << std::endl;
	ft.pop_back();
	stl.pop_back();
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	for (int i = 0; i <= 500 ; i++)
	{
		std::cout << "_______________________________________________" << std::endl
			<< "vector.push_back(" << i << ") :	" << std::endl;
		ft.push_back(i);
		stl.push_back(i);
		if (!(print_test_result(vector_compare(ft, stl))))
			return false;
		std::cout << std::endl;
	}

	if (vector_copy_constructor_test(ft, stl) == false)
		return false;

	std::cout << "_______________________________________________" << std::endl
		<< "clear()" << std::endl << std::endl;
	ft.clear();
	stl.clear();
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	size_t	n = 80;
	int		val = 9;

	std::cout << "_______________________________________________" << std::endl
		<< "assign(" << n << ", " << val << ")" << std::endl << std::endl;
	ft.assign(80, 9);
	stl.assign(80, 9);
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	std::cout << "_______________________________________________" << std::endl
		<< "resize(size - (size / 3))" << std::endl << std::endl;
	ft.resize(ft.size() - (ft.size() / 3));
	stl.resize(stl.size() - (stl.size() / 3));
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	std::cout << "_______________________________________________" << std::endl
		<< "Element access :" << std::endl << "	vector[size()/2] = 2" << std::endl << std::endl;

	ft[ft.size() / 2] = 2;
	stl[stl.size() / 2] = 2;
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	std::cout << std::endl << "#######################################" << std::endl
		<< std::endl << "	vector.at(size()/4) = 4" << std::endl << std::endl;

	ft.at(ft.size() / 4) = 4;
	stl.at(stl.size() / 4) = 4;
	if (!(print_test_result(vector_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	return true;
}
