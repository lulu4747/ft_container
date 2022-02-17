#include <iostream>
#include <string>
#include <map>
#include <sys/time.h>
#include "map_test.hpp"
#include "../tester.hpp"
#include "../../ft_containers/map.hpp"

/*
	ft::map< int, char >	ft;
	std::map< int, char >	stl;

	get_identical_random_filled_maps(EXTRA_LARGE, &ft, &stl);
*/

static bool	default_constructor_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "	map" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::map<int, char>		ft;
	std::map<int, char>	stl;

	if (!(print_test_result(map_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval	start, end;
		double	ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			default_construction< ft::map<int, char> >();
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			default_construction< std::map<int, char> >();
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

	ft::map< int, char >	ft_src;
	std::map< int, char >	stl_src;

	get_identical_random_filled_maps(n, &ft_src, &stl_src);

	ft::map< int, char >	ft(ft_src);
	std::map< int, char >	stl(stl_src);

	if (!(print_test_result(map_compare(ft, stl))))
		return false;

	if (time_check && n != EXTRA_LARGE)
	{
		timeval	start, end;
		double	ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			copy_construction< ft::map< int, char > >(ft_src);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			copy_construction< std::map< int, char > >(stl_src);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}
	return recursive_call(&copy_constructor_test, time_check, n);
}

static bool	range_constructor_test(bool time_check, int n)
{
	n++;
	time_check = false;
	return true;
}

static bool	iterators_test(bool time_check)
{
	time_check = false;
	return true;
}

static bool	elements_access_test(bool time_check)
{
	time_check = false;
	return true;
}

static bool	insert_test(bool time_check)
{
	time_check = false;
	return true;
}

static bool	erase_test(bool time_check)
{
	time_check = false;
	return true;
}

static bool	swap_test(bool time_check)
{
	time_check = false;
	return true;
}

static bool	clear_test(bool time_check)
{
	time_check = false;
	return true;
}

static bool	operations_test(bool time_check)
{
/*
find(time_check)

count(time_check)

lower_bound(time_check)

upper_bound(time_check)

equal_range(time_check)*/
	time_check = false;
	return true;
}

static bool	relationnal_operators_test()
{
	return true;
}

bool	map_test(bool time_check)
{
	if (default_constructor_test(time_check) == false)
		return false;

	if (copy_constructor_test(time_check, EMPTY) == false)
		return false;

	if (range_constructor_test(time_check, EMPTY) == false)
		return false;

	if (iterators_test(time_check) == false)
		return false;

	if (elements_access_test(time_check) == false)
		return false;

	if (insert_test(time_check) == false)
		return false;

	if (erase_test(time_check) == false)
		return false;

	if (swap_test(time_check) == false)
		return false;

	if (clear_test(time_check) == false)
		return false;

	if (operations_test(time_check) == false)
		return false;

	if (relationnal_operators_test() == false)
		return false;

	std::cout << std::endl << "*****************************************************" << std::endl << std::endl
		<< "Map :				";
	print_test_result(true);
	std::cout << std::endl << "*****************************************************" << std::endl;

	time_check = false;
	return	true;
}
