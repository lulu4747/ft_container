#include <iostream>
#include <map>
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
	time_check = false;
	return true;
}

static bool	copy_constructor_test(bool time_check, int size)
{
	time_check = false;
	return true;
}

static bool	fill_constructor_test(bool time_check, int size)
{
	time_check = false;
	return true;
}

static bool	range_constructor_test(bool time_check, int size)
{
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

	if (fill_constructor_test(time_check, EMPTY) == false)
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
		<< "Vector :				";
	print_test_result(true);
	std::cout << std::endl << "*****************************************************" << std::endl;

	time_check = false;
	return	true;
}
