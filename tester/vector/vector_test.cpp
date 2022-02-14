#include <iostream>
#include <sys/time.h>
#include <vector>
#include <cstdlib>
#include "vector_test.hpp"
#include "../tester.hpp"
#include "../../ft_containers/vector.hpp"

static bool	default_constructor_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "	vector" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::vector<int>		ft;
	std::vector<int>	stl;

	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval	start, end;
		double	ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			default_construction< ft::vector<int> >();
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			default_construction< std::vector<int> >();
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}
	return true;
}

static bool	copy_constructor_test(bool time_check, int n)
{
	if (n == EMPTY)
	{
		std::cout << "_______________________________________________" << std::endl
			<< "copy construction" << std::endl << "empty source :" << std::endl;
	}
	else
		std::cout << std::endl << "#######################################" << std::endl 
			<< n << " random values source :" << std::endl;

	ft::vector<int>		ft_src;
	std::vector<int>	stl_src;

	get_identical_random_filled_vectors(n, &ft_src, &stl_src);

	ft::vector<int>		ft(ft_src);
	std::vector<int>	stl(stl_src);

	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval	start, end;
		double	ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			copy_construction< ft::vector<int> >(ft_src);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			copy_construction< std::vector<int> >(stl_src);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}
	return recursive_call(&copy_constructor_test, time_check, n);
}

static bool	fill_constructor_test(bool time_check, int n)
{
	int val = rand();

	if (n == EMPTY)
		std::cout << "_______________________________________________" << std::endl;
	else
		std::cout << std::endl << "#######################################" << std::endl;
	std::cout << "fill construction with n = " << n << ", val = " << val << std::endl << std::endl;

	ft::vector<int>		ft(n, val);
	std::vector<int>	stl(n, val);

	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval	start, end;
		double	ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			fill_construction< ft::vector<int> >(n, val);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			fill_construction< std::vector<int> >(n, val);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}
	return recursive_call(&fill_constructor_test, time_check, n);
}

static bool	range_constructor_test(bool time_check, int n)
{
	if (n == EMPTY)
	{
		std::cout << "_______________________________________________" << std::endl
			<< "range construction" << std::endl << "empty range :" << std::endl;
	}
	else
	{
		std::cout <<  std::endl << "#######################################" << std::endl 
			<< n << " range :" << std::endl;
	}

	std::vector<int>	range(get_random_vector(n));

	std::vector<int>::iterator	stl_it = range.begin();			// <-- Could not use same iterator constructor because it is private in STL
	ft::vector<int>::iterator	ft_it = &(*(range.begin()));

	if (&(*stl_it) != &(*ft_it))
		return false;

	ft::vector<int>		ft(ft_it, ft_it + n);
	std::vector<int>	stl(stl_it, stl_it + n);

	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval	start, end;
		double	ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			range_construction< ft::vector<int> >(ft_it, ft_it + n);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			range_construction< std::vector<int> >(stl_it, stl_it + n);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}
	return recursive_call(&range_constructor_test, time_check, n);
}

static bool	begin_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "begin() on empty vector" << std::endl << std::endl << "compared with end() :	";

	ft::vector<int>		ft;
	std::vector<int>	stl;
	ft::vector<int>::iterator	ft_it = ft.begin();
	std::vector<int>::iterator	stl_it = stl.begin();

	if (!(print_test_result((ft_it == ft.end()) == (stl_it == stl.end()))))
		return false;

	if (time_check && iterator_time_check(&begin, &begin, ft, stl) == false)
		return false;

	std::cout << "const begin() on empty vector" << std::endl << std::endl << "compared with end() :	";
	ft::vector<int>::const_iterator		ft_cit = ft.begin();
	std::vector<int>::const_iterator	stl_cit = stl.begin();

	if (!(print_test_result((ft_cit == ft.end()) == (stl_cit == stl.end()))))
		return false;

	return true;
}

bool	vector_test(bool time_check)
{
	if (default_constructor_test(time_check) == false)
		return false;

	if (copy_constructor_test(time_check, EMPTY) == false)
		return false;

	if (fill_constructor_test(time_check, EMPTY) == false)
		return false;

	if (range_constructor_test(time_check, EMPTY) == false)
		return false;
	
	if (begin_test(time_check) == false)
		return false;
/*
	std::cout << "_______________________________________________" << std::endl
		<< "vector.push_back(0) with empty vector :	" << std::endl;
	ft.push_back(0);
	stl.push_back(0);
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	std::cout << "_______________________________________________" << std::endl
		<< "vector.pop_back() :	" << std::endl;
	ft.pop_back();
	stl.pop_back();
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	int i = 500;

	std::cout << "_______________________________________________" << std::endl
		<< "vector.push_back() " << i << " times :	" << std::endl;
	while (i >= 0)
	{
		ft.push_back(i);
		stl.push_back(i);
		i--;
	}
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	std::cout << "_______________________________________________" << std::endl
		<< "clear()" << std::endl << std::endl;
	ft.clear();
	stl.clear();
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	size_t	n = 80;
	int		val = 9;

	std::cout << "_______________________________________________" << std::endl
		<< "assign(" << n << ", " << val << ")" << std::endl << std::endl;
	ft.assign(80, 9);
	stl.assign(80, 9);
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	std::cout << "_______________________________________________" << std::endl
		<< "resize reduction :" << std::endl << "resize(size - (size / 3))" << std::endl << std::endl;
	ft.resize(ft.size() - (ft.size() / 3));
	stl.resize(stl.size() - (stl.size() / 3));
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "resize extension :" << std::endl << "resize(size + 10)" << std::endl << std::endl;
	ft.resize(ft.size() + 10);
	stl.resize(stl.size() + 10);
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;
	std::cout << std::endl;

	std::cout << "_______________________________________________" << std::endl
		<< "Element access :" << std::endl << "	operator[] (size / 2) = 2" << std::endl << std::endl;

	ft[ft.size() / 2] = 2;
	stl[stl.size() / 2] = 2;
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;

	std::cout << std::endl << "#######################################" << std::endl
		<< std::endl << "	vector.at(size()/4) = 4" << std::endl << std::endl;

	ft.at(ft.size() / 4) = 4;
	stl.at(stl.size() / 4) = 4;
	if (!(print_test_result(attributes_compare(ft, stl))))
		return false;
*/
	return true;
}
