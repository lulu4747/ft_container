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
	if (n == EMPTY)
	{
		std::cout << "_______________________________________________" << std::endl
			<< "range construction" << std::endl << "empty range :" << std::endl;
	}
	else
	{
		std::cout << std::endl << "#######################################" << std::endl
			<< n << " range :" << std::endl;
	}

	ft::map< int, char >	ft_src;
	std::map< int, char >	stl_src;

	get_identical_random_filled_maps(n, &ft_src, &stl_src);

	ft::map< int, char>		ft(ft_src.begin(), ft_src.end());
	std::map< int, char>	stl(stl_src.begin(), stl_src.end());

	if (!(print_test_result(map_compare(ft, stl))))
		return false;

	if (time_check && n != EXTRA_LARGE)
	{
		timeval	start, end;
		double	ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			range_construction< ft::map< int, char> >(ft_src.begin(), ft_src.end());
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			range_construction< std::map< int, char> >(stl_src.begin(), stl_src.end());
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}
	return recursive_call(&range_constructor_test, time_check, n);
}

static bool	begin_test(bool time_check)
{
	std::cout << "begin() on empty map" << std::endl << std::endl << "compared with end() :	";

	ft::map< int, char >			ft;
	std::map< int, char >			stl;
	ft::map< int, char >::iterator	ft_it = ft.begin();
	std::map< int, char >::iterator	stl_it = stl.begin();

	if (!(print_test_result((ft_it == ft.end()) == (stl_it == stl.end()))))
		return false;

	if (time_check && iterator_time_check(&begin, &begin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const begin() on empty map" << std::endl << std::endl << "compared with end() :	";
	ft::map< int, char >::const_iterator		ft_cit = ft.begin();
	std::map< int, char >::const_iterator	stl_cit = stl.begin();

	if (!(print_test_result((ft_cit == ft.end()) == (stl_cit == stl.end()))))
		return false;

	std::cout << std::endl << "begin() on large (" << LARGE << ") map" << std::endl << std::endl << "while(it != end())"
		<< std::endl << "it++; (*it == *stl_it)? :			";

	get_identical_random_filled_maps(LARGE, &ft, &stl);
	ft_it = ft.begin();
	stl_it = stl.begin();

	while (ft_it != ft.end())
	{
		if (ft_it->first != stl_it->first && ft_it->second != stl_it->second)
			return false;
		ft_it++;
		stl_it++;
	}
	if (stl_it != stl.end())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&begin_to_end, &begin_to_end, ft, stl) == false)
		return false;

	std::cout << std::endl << "const begin() on same map" << std::endl << std::endl << "while(cit != end())"
		<< std::endl << "cit++; (*cit == *stl_cit)? :			";

	ft_cit = ft.begin();
	stl_cit = stl.begin();

	while (ft_cit != ft.end())
	{
		if (ft_cit->first != stl_cit->first && ft_cit->second != stl_cit->second)
			return false;
		ft_cit++;
		stl_cit++;
	}
	if (stl_cit != stl.end())
		return false;
	print_test_result(true);

	std::cout << "General :					";
	return true;
}

static bool	end_test(bool time_check)
{

	ft::map< int, char >				ft;
	std::map< int, char >			stl;

	std::cout << std::endl << "#######################################" << std::endl
		<< "--end() on large (" << LARGE << ") map" << std::endl << std::endl << "while(it != begin())"
		<< std::endl << "it--; (*it == *stl_it)? :			";

	get_identical_random_filled_maps(LARGE, &ft, &stl);
	ft::map< int, char >::iterator	ft_it = --ft.end();
	std::map< int, char >::iterator	stl_it = --stl.end();

	while (ft_it != ft.begin())
	{
		if (ft_it->first != stl_it->first && ft_it->second != stl_it->second)
			return false;
		ft_it--;
		stl_it--;
	}
	if (stl_it != stl.begin())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&end_to_begin, &end_to_begin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const end()-- on same map" << std::endl << std::endl << "while(cit != begin())"
		<< std::endl << "cit--; (*cit == *stl_cit)? :			";

	ft::map< int, char >::const_iterator		ft_cit = --ft.end();
	std::map< int, char >::const_iterator	stl_cit = --stl.end();

	while (ft_cit != ft.begin())
	{
		if (ft_cit->first != stl_cit->first && ft_cit->second != stl_cit->second)
			return false;
		ft_cit--;
		stl_cit--;
	}
	if (stl_cit != stl.begin())
		return false;
	print_test_result(true);

	std::cout << "General :					";
	return true;
}

static bool	rbegin_test(bool time_check)
{
	std::cout << std::endl << "#######################################" << std::endl
		<< "rbegin() on empty map" << std::endl << std::endl << "compared with rend() :	";

	ft::map< int, char >						ft;
	std::map< int, char >					stl;
	ft::map< int, char >::reverse_iterator	ft_rit = ft.rbegin();
	std::map< int, char >::reverse_iterator	stl_rit = stl.rbegin();

	if (!(print_test_result((ft_rit == ft.rend()) == (stl_rit == stl.rend()))))
		return false;

	if (time_check && iterator_time_check(&rbegin, &rbegin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const rbegin() on empty map" << std::endl << std::endl << "compared with rend() :	";
	ft::map< int, char >::const_reverse_iterator		ft_crit = ft.rbegin();
	std::map< int, char >::const_reverse_iterator	stl_crit = stl.rbegin();

	if (!(print_test_result((ft_crit == ft.rend()) == (stl_crit == stl.rend()))))
		return false;

	std::cout << std::endl << "rbegin() on large (" << LARGE << ") map" << std::endl << std::endl << "while(rit != rend())"
		<< std::endl << "rit++; (*rit == *stl_rit)? :			";

	get_identical_random_filled_maps(LARGE, &ft, &stl);
	ft_rit = ft.rbegin();
	stl_rit = stl.rbegin();

	int i = 0;
	while (ft_rit != ft.rend())
	{
		std::cout << i << std::endl;
		if (ft_rit->first != stl_rit->first && ft_rit->second != stl_rit->second)
			return false;
		ft_rit++;
		stl_rit++;
		i++;
	}
	if (stl_rit != stl.rend())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&rbegin_to_rend, &rbegin_to_rend, ft, stl) == false)
		return false;

	std::cout << std::endl << "const rbegin() on same map" << std::endl << std::endl << "while(crit != rend())"
		<< std::endl << "crit++; (*crit == *stl_crit)? :			";

	ft_crit = ft.rbegin();
	stl_crit = stl.rbegin();

	while (ft_crit != ft.rend())
	{
		if (ft_crit->first != stl_crit->first && ft_crit->second != stl_crit->second)
			return false;
		ft_crit++;
		stl_crit++;
	}
	if (stl_crit != stl.rend())
		return false;
	print_test_result(true);

	std::cout << "General :					";
	return true;
}

static bool	rend_test(bool time_check)
{
	std::cout << std::endl << "#######################################" << std::endl
		<< "rend()-- on large (" << LARGE << ") map" << std::endl << std::endl << "while(rit != rbegin())"
		<< std::endl << "rit--; (*rit == *stl_rit)? :			";

	ft::map< int, char >				ft;
	std::map< int, char >				stl;

	get_identical_random_filled_maps(LARGE, &ft, &stl);
	ft::map< int, char >::reverse_iterator	ft_rit = --ft.rend();
	std::map< int, char >::reverse_iterator	stl_rit = --stl.rend();

	while (ft_rit != ft.rbegin())
	{
		if (ft_rit->first != stl_rit->first && ft_rit->second != stl_rit->second)
			return false;
		ft_rit--;
		stl_rit--;
	}
	if (stl_rit != stl.rbegin())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&rend_to_rbegin, &rend_to_rbegin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const rend() - 1 on same map" << std::endl << std::endl << "while(crit != rbegin())"
		<< std::endl << "--crit; (*crit == *stl_crit)? :			";

	ft::map< int, char >::const_reverse_iterator		ft_crit = --ft.rend();
	std::map< int, char >::const_reverse_iterator	stl_crit = --stl.rend();

	while (ft_crit != ft.rbegin())
	{
		if (ft_crit->first != stl_crit->first && ft_crit->second != stl_crit->second)
			return false;
		ft_crit--;
		stl_crit--;
	}
	if (stl_crit != stl.rbegin())
		return false;
	print_test_result(true);

	std::cout << "General :					";
	return true;
}

template <typename FT_iterator, typename STL_iterator, 
			typename FT_begin, typename STL_begin>
static bool	op_test(std::string it, FT_iterator &ft_it, STL_iterator &stl_it,
			FT_begin ft_begin, STL_begin stl_begin)
{
	std::string	begin(it.find('r') == it.npos ? "begin" : "rbegin");

	std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
		<< "iterator		tmp(" << it << ");" << std::endl << std::endl << it << "++ == tmp ? :	";

	FT_iterator		ft_tmp(ft_it);
	STL_iterator	stl_tmp(stl_it);

	if (!print_test_result((ft_it++ == ft_tmp) == (stl_it++ == stl_tmp)))
		return false;

	std::cout << std::endl << "tmp = " << it << ";" << std::endl << it << "-- == tmp ? :	";

	ft_tmp = ft_it;
	stl_tmp = stl_it;

	if (!print_test_result((ft_it-- == ft_tmp) == (stl_it-- == stl_tmp)))
		return false;

	std::cout << std::endl << "tmp = " << it << ";" << std::endl << "++" << it << " == tmp ? :	";

	ft_tmp = ft_it;
	stl_tmp = stl_it;

	if (!print_test_result((++ft_it == ft_tmp) == (++stl_it == stl_tmp)))
		return false;

	std::cout << std::endl << "tmp = " << it << ";" << std::endl << "--" << it << " == tmp ? :	";

	ft_tmp = ft_it;
	stl_tmp = stl_it;

	if (!print_test_result((--ft_it == ft_tmp) == (--stl_it == stl_tmp)))
		return false;

	std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
		<< it << " == vector." << begin << "() ? :	";

	if (!print_test_result((ft_it == ft_begin) == (stl_it == stl_begin)))
		return false;

	std::cout << it << " != vector." << begin << "() ? :	";

	if (!print_test_result((ft_it != ft_begin) == (stl_it != stl_begin)))
		return false;

	std::cout << it << "++ == vector." << begin << "() ? :	";

	if (!print_test_result((ft_it++ == ft_begin) == (stl_it++ == stl_begin)))
		return false;

	std::cout << it << " != vector." << begin << "() ? :	";

	if (!print_test_result((ft_it != ft_begin) == (stl_it != stl_begin)))
		return false;

	std::cout << "--" << it << " == vector." << begin << "() ? :	";

	if (!print_test_result((--ft_it == ft_begin) == (--stl_it == stl_begin)))
		return false;

	return true;
}

static bool	operators_test()
{
	std::cout << std::endl << "#######################################" << std::endl
		<< "iterators operators test" << std::endl
		<< "Crescent values filled map from 0 to " << MEDIUM << std::endl << std::endl
		<< "	Comparison operator	" << std::endl << std::endl
		<< "normal iterator :" << std::endl
		<< "it(map.begin());" << std::endl << std::endl;

	ft::map< int, char >						ft;
	std::map< int, char >						stl;
	get_crescent_key_filled_maps(MEDIUM, &ft, &stl);

	ft::map< int, char >::iterator				ft_it(ft.begin());
	std::map< int, char >::iterator				stl_it(stl.begin());

	if (op_test("it", ft_it, stl_it, ft.begin(), stl.begin()) == false)
		return false;
	
	std::cout << std::endl << "constant iterator :" << std::endl
		<< "cit(map.begin());" << std::endl << std::endl;

	ft::map< int, char >::const_iterator			ft_cit(ft.begin());
	std::map< int, char >::const_iterator		stl_cit(stl.begin());

	if (op_test("cit", ft_cit, stl_cit, ft.begin(), stl.begin()) == false)
		return false;
	
	std::cout << std::endl << "reverse iterator :" << std::endl
		<< "rit(map.rbegin());" << std::endl << std::endl;

	ft::map< int, char >::reverse_iterator		ft_rit(ft.rbegin());
	std::map< int, char >::reverse_iterator		stl_rit(stl.rbegin());

	if (op_test("rit", ft_rit, stl_rit, ft.rbegin(), stl.rbegin()) == false)
		return false;
	
	std::cout << std::endl << "const reverse iterator :" << std::endl
		<< "crit(map.rbegin());" << std::endl << std::endl;

	ft::map< int, char >::const_reverse_iterator			ft_crit(ft.rbegin());
	std::map< int, char >::const_reverse_iterator		stl_crit(stl.rbegin());

	if (op_test("crit", ft_crit, stl_crit, ft.rbegin(), stl.rbegin()) == false)
		return false;

	std::cout << "General :			";

	return true;
}

static bool	iterators_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "iterators test" << std::endl;

	if (!print_test_result(begin_test(time_check)))
		return false;
	if (!print_test_result(end_test(time_check)))
		return false;
	if (!print_test_result(rbegin_test(time_check)))
		return false;
	if (!print_test_result(rend_test(time_check)))
		return false;
	if (!print_test_result(operators_test()))
		return false;
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
