#include <iostream>
#include <string>
#include <sys/time.h>
#include <vector>
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

	if (!(print_test_result(vector_compare(ft, stl))))
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

	if (!(print_test_result(vector_compare(ft, stl))))
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

	if (!(print_test_result(vector_compare(ft, stl))))
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
		std::cout << std::endl << "#######################################" << std::endl
			<< n << " range :" << std::endl;
	}

	std::vector<int>	range(get_random_vector(n));

	std::vector<int>::iterator	stl_it(range.begin());			// <-- Could not use same iterator constructor because it is private in STL
	ft::vector<int>::iterator	ft_it = &(*(range.begin()));

	if (&(*stl_it) != &(*ft_it))
		return false;

	ft::vector<int>		ft(ft_it, ft_it + n);
	std::vector<int>	stl(stl_it, stl_it + n);

	if (!(print_test_result(vector_compare(ft, stl))))
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
	std::cout << "begin() on empty vector" << std::endl << std::endl << "compared with end() :	";

	ft::vector<int>		ft;
	std::vector<int>	stl;
	ft::vector<int>::iterator	ft_it = ft.begin();
	std::vector<int>::iterator	stl_it = stl.begin();

	if (!(print_test_result((ft_it == ft.end()) == (stl_it == stl.end()))))
		return false;

	if (time_check && iterator_time_check(&begin, &begin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const begin() on empty vector" << std::endl << std::endl << "compared with end() :	";
	ft::vector<int>::const_iterator		ft_cit = ft.begin();
	std::vector<int>::const_iterator	stl_cit = stl.begin();

	if (!(print_test_result((ft_cit == ft.end()) == (stl_cit == stl.end()))))
		return false;

	std::cout << std::endl << "begin() on large (" << LARGE << ") vector" << std::endl << std::endl << "while(it != end())"
		<< std::endl << "it++; (*it == *stl_it)? :			";

	get_identical_random_filled_vectors(LARGE, &ft, &stl);
	ft_it = ft.begin();
	stl_it = stl.begin();

	while (ft_it != ft.end())
	{
		if (*ft_it != *stl_it)
			return false;
		ft_it++;
		stl_it++;
	}
	if (stl_it != stl.end())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&begin_to_end, &begin_to_end, ft, stl) == false)
		return false;

	std::cout << std::endl << "const begin() on same vector" << std::endl << std::endl << "while(cit != end())"
		<< std::endl << "cit++; (*cit == *stl_cit)? :			";

	ft_cit = ft.begin();
	stl_cit = stl.begin();

	while (ft_cit != ft.end())
	{
		if (*ft_cit != *stl_cit)
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

	ft::vector<int>				ft;
	std::vector<int>			stl;

	std::cout << std::endl << "#######################################" << std::endl
		<< "end() - 1 on large (" << LARGE << ") vector" << std::endl << std::endl << "while(it != begin())"
		<< std::endl << "it--; (*it == *stl_it)? :			";

	get_identical_random_filled_vectors(LARGE, &ft, &stl);
	ft::vector<int>::iterator	ft_it = ft.end() - 1;
	std::vector<int>::iterator	stl_it = stl.end() - 1;

	while (ft_it != ft.begin())
	{
		if (*ft_it != *stl_it)
			return false;
		ft_it--;
		stl_it--;
	}
	if (stl_it != stl.begin())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&end_to_begin, &end_to_begin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const end() - 1 on same vector" << std::endl << std::endl << "while(cit != begin())"
		<< std::endl << "cit--; (*cit == *stl_cit)? :			";

	ft::vector<int>::const_iterator		ft_cit = ft.end() - 1;
	std::vector<int>::const_iterator	stl_cit = stl.end() - 1;

	while (ft_cit != ft.begin())
	{
		if (*ft_cit != *stl_cit)
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
		<< "rbegin() on empty vector" << std::endl << std::endl << "compared with rend() :	";

	ft::vector<int>						ft;
	std::vector<int>					stl;
	ft::vector<int>::reverse_iterator	ft_rit = ft.rbegin();
	std::vector<int>::reverse_iterator	stl_rit = stl.rbegin();

	if (!(print_test_result((ft_rit == ft.rend()) == (stl_rit == stl.rend()))))
		return false;

	if (time_check && iterator_time_check(&rbegin, &rbegin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const rbegin() on empty vector" << std::endl << std::endl << "compared with rend() :	";
	ft::vector<int>::const_reverse_iterator		ft_crit = ft.rbegin();
	std::vector<int>::const_reverse_iterator	stl_crit = stl.rbegin();

	if (!(print_test_result((ft_crit == ft.rend()) == (stl_crit == stl.rend()))))
		return false;

	std::cout << std::endl << "rbegin() on large (" << LARGE << ") vector" << std::endl << std::endl << "while(rit != rend())"
		<< std::endl << "rit++; (*rit == *stl_rit)? :			";

	get_identical_random_filled_vectors(LARGE, &ft, &stl);
	ft_rit = ft.rbegin();
	stl_rit = stl.rbegin();

	while (ft_rit != ft.rend())
	{
		if (*ft_rit != *stl_rit)
			return false;
		ft_rit++;
		stl_rit++;
	}
	if (stl_rit != stl.rend())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&rbegin_to_rend, &rbegin_to_rend, ft, stl) == false)
		return false;

	std::cout << std::endl << "const rbegin() on same vector" << std::endl << std::endl << "while(crit != rend())"
		<< std::endl << "crit++; (*crit == *stl_crit)? :			";

	ft_crit = ft.rbegin();
	stl_crit = stl.rbegin();

	while (ft_crit != ft.rend())
	{
		if (*ft_crit != *stl_crit)
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
		<< "rend() - 1 on large (" << LARGE << ") vector" << std::endl << std::endl << "while(rit != rbegin())"
		<< std::endl << "rit--; (*rit == *stl_rit)? :			";

	ft::vector<int>				ft;
	std::vector<int>			stl;

	get_identical_random_filled_vectors(LARGE, &ft, &stl);
	ft::vector<int>::reverse_iterator	ft_rit = ft.rend() - 1;
	std::vector<int>::reverse_iterator	stl_rit = stl.rend() - 1;

	while (ft_rit != ft.rbegin())
	{
		if (*ft_rit != *stl_rit)
			return false;
		ft_rit--;
		stl_rit--;
	}
	if (stl_rit != stl.rbegin())
		return false;
	print_test_result(true);

	if (time_check && iterator_time_check(&rend_to_rbegin, &rend_to_rbegin, ft, stl) == false)
		return false;

	std::cout << std::endl << "const rend() - 1 on same vector" << std::endl << std::endl << "while(crit != rbegin())"
		<< std::endl << "crit--; (*crit == *stl_crit)? :			";

	ft::vector<int>::const_reverse_iterator		ft_crit = ft.rend() - 1;
	std::vector<int>::const_reverse_iterator	stl_crit = stl.rend() - 1;

	while (ft_crit != ft.rbegin())
	{
		if (*ft_crit != *stl_crit)
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


	std::cout << "----------Arithmetic operators----------" << std::endl
		<< "Mostly using \"operator*()\" to compare ft::vector with std::vector" << std::endl
		<< std::endl << it << " += " << MEDIUM / 2 << " :			";

	if (!print_test_result(*(ft_it += MEDIUM / 2) == *(stl_it += MEDIUM / 2)))
		return false;

	std::cout << it << " + " << MEDIUM / 5 << " :			";

	if (!print_test_result(*(ft_it + MEDIUM / 5) == *(stl_it + MEDIUM / 5)))
		return false;

	std::cout << it << " - " << MEDIUM / 3 << " :			";

	if (!print_test_result(*(ft_it - MEDIUM / 3) == *(stl_it - MEDIUM / 3)))
		return false;

	std::cout << it << " - vector." << begin << "() :		";

	if (!print_test_result((ft_it - ft_begin) == (stl_it - stl_begin)))
		return false;

	std::cout << it << " -= " << MEDIUM / 4 << " :			";

	if (!print_test_result(*(ft_it -= MEDIUM / 4) == *(stl_it -= MEDIUM / 4)))
		return false;

	std::cout << it << " = vector." << begin << "() :	";

	if (!print_test_result(*(ft_it = ft_begin) == *(stl_it = stl_begin)))
		return false;

	std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
		<< it << " == vector." << begin << "() ? :	";

	if (!print_test_result((ft_it == ft_begin) == (stl_it == stl_begin)))
		return false;

	std::cout << it << " != vector." << begin << "() ? :	";

	if (!print_test_result((ft_it != ft_begin) == (stl_it != stl_begin)))
		return false;

	std::cout << it << " <= vector." << begin << "() ? :	";

	if (!print_test_result((ft_it <= ft_begin) == (stl_it <= stl_begin)))
		return false;

	std::cout << it << " >= vector." << begin << "() ? :	";

	if (!print_test_result((ft_it >= ft_begin) == (stl_it >= stl_begin)))
		return false;

	std::cout << it << " < vector." << begin << "() ? :		";

	if (!print_test_result((ft_it < ft_begin) == (stl_it < stl_begin)))
		return false;

	std::cout << it << " > vector." << begin << "() ? :		";

	if (!print_test_result((ft_it > ft_begin) == (stl_it > stl_begin)))
		return false;

	std::cout << it << "++ == vector." << begin << "() ? :	";

	if (!print_test_result((ft_it++ == ft_begin) == (stl_it++ == stl_begin)))
		return false;

	std::cout << it << " != vector." << begin << "() ? :	";

	if (!print_test_result((ft_it != ft_begin) == (stl_it != stl_begin)))
		return false;

	std::cout << it << " <= vector." << begin << "() ? :	";

	if (!print_test_result((ft_it <= ft_begin) == (stl_it <= stl_begin)))
		return false;

	std::cout << it << " >= vector." << begin << "() ? :	";

	if (!print_test_result((ft_it >= ft_begin) == (stl_it >= stl_begin)))
		return false;

	std::cout << it << " < vector." << begin << "() ? :		";

	if (!print_test_result((ft_it < ft_begin) == (stl_it < stl_begin)))
		return false;

	std::cout << it << " > vector." << begin << "() ? :		";

	if (!print_test_result((ft_it > ft_begin) == (stl_it > stl_begin)))
		return false;

	std::cout << "--" << it << " == vector." << begin << "() ? :	";

	if (!print_test_result((--ft_it == ft_begin) == (--stl_it == stl_begin)))
		return false;

	std::cout << std::endl << "----------Access operators----------" << std::endl << std::endl
		<< it << "[" << MEDIUM / 5 << "] :			";

	if (!print_test_result((ft_it[MEDIUM / 5]) == (stl_it[MEDIUM / 5])))
		return false;

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

	return true;
}

static bool	operators_test()
{
	std::cout << std::endl << "#######################################" << std::endl
		<< "iterators operators test" << std::endl
		<< "Crescent values filled vector from 0 to " << MEDIUM << std::endl << std::endl
		<< "	Comparison operator	" << std::endl << std::endl
		<< "normal iterator :" << std::endl
		<< "it(vector.begin());" << std::endl << std::endl;

	ft::vector<int>							ft;
	std::vector<int>						stl;
	get_crescent_filled_vectors(MEDIUM, &ft, &stl);

	ft::vector<int>::iterator				ft_it(ft.begin());
	std::vector<int>::iterator				stl_it(stl.begin());

	if (op_test("it", ft_it, stl_it, ft.begin(), stl.begin()) == false)
		return false;
	
	std::cout << std::endl << "constant iterator :" << std::endl
		<< "cit(vector.begin());" << std::endl << std::endl;

	ft::vector<int>::const_iterator			ft_cit(ft.begin());
	std::vector<int>::const_iterator		stl_cit(stl.begin());

	if (op_test("cit", ft_cit, stl_cit, ft.begin(), stl.begin()) == false)
		return false;
	
	std::cout << std::endl << "reverse iterator :" << std::endl
		<< "rit(vector.rbegin());" << std::endl << std::endl;

	ft::vector<int>::reverse_iterator		ft_rit(ft.rbegin());
	std::vector<int>::reverse_iterator		stl_rit(stl.rbegin());

	if (op_test("rit", ft_rit, stl_rit, ft.rbegin(), stl.rbegin()) == false)
		return false;
	
	std::cout << std::endl << "const reverse iterator :" << std::endl
		<< "crit(vector.rbegin());" << std::endl << std::endl;

	ft::vector<int>::const_reverse_iterator			ft_crit(ft.rbegin());
	std::vector<int>::const_reverse_iterator		stl_crit(stl.rbegin());

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

static bool	resize_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "Resize test" << std::endl
		<< std::endl << "#######################################" << std::endl << std::endl
		<< "Resize equal (" << MEDIUM << " to " << MEDIUM << ")" << std::endl << std::endl;

	ft::vector<int>		ft;
	std::vector<int>	stl;

	get_crescent_filled_vectors(MEDIUM, &ft, &stl);

	ft.resize(MEDIUM);
	stl.resize(MEDIUM);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		ft::vector<int>		ft_tmp;
		std::vector<int>	stl_tmp;
		timeval				start, end;
		double				ft_time, stl_time;

		get_crescent_filled_vectors(MEDIUM, &ft_tmp, &stl_tmp);
		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			ft_tmp.resize(MEDIUM);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			stl_tmp.resize(MEDIUM);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "Resize expansion (" << MEDIUM << " to " << LARGE << ") with no val" << std::endl << std::endl;

	ft.resize(LARGE);
	stl.resize(LARGE);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		ft::vector<int>		ft_tmp;
		std::vector<int>	stl_tmp;
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			get_crescent_filled_vectors(MEDIUM, &ft_tmp, &stl_tmp);
			ft_tmp.resize(LARGE);
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			get_crescent_filled_vectors(MEDIUM, &ft_tmp, &stl_tmp);
			stl_tmp.resize(LARGE);
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "Resize reduction (" << LARGE << " to " << SHORT << ")" << std::endl << std::endl;

	ft.resize(SHORT);
	stl.resize(SHORT);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		ft::vector<int>		ft_tmp;
		std::vector<int>	stl_tmp;
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			get_crescent_filled_vectors(LARGE, &ft_tmp, &stl_tmp);
			ft_tmp.resize(SHORT);
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			get_crescent_filled_vectors(LARGE, &ft_tmp, &stl_tmp);
			stl_tmp.resize(SHORT);
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	int	val(std::rand());

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "Resize expansion (" << SHORT << " to " << MEDIUM << ") with val = " << val << std::endl << std::endl;

	ft.resize(LARGE, val);
	stl.resize(LARGE, val);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		ft::vector<int>		ft_tmp;
		std::vector<int>	stl_tmp;
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			get_crescent_filled_vectors(MEDIUM, &ft_tmp, &stl_tmp);
			ft_tmp.resize(LARGE, val);
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			get_crescent_filled_vectors(MEDIUM, &ft_tmp, &stl_tmp);
			stl_tmp.resize(LARGE, val);
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	return true;
}

static bool	reserve_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "Reserve test" << std::endl
		<< std::endl << "#######################################" << std::endl << std::endl
		<< "reserve(" << MEDIUM << ") on empty vector" << std::endl << std::endl;

	ft::vector<int>		ft;
	std::vector<int>	stl;

	ft.reserve(MEDIUM);
	stl.reserve(MEDIUM);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft::vector<int>		*ft_tmp = new ft::vector<int>;

			ft_tmp->reserve(MEDIUM);
			delete	ft_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			std::vector<int>	*stl_tmp = new std::vector<int>;

			stl_tmp->reserve(MEDIUM);
			delete	stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	int	val(std::rand());

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "push_back(" << val << ") on same vector" << std::endl << std::endl;

	ft.push_back(val);
	stl.push_back(val);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "Reserve (" << MEDIUM + SHORT << ") on same vector" << std::endl << std::endl;

	ft.resize(MEDIUM + SHORT);
	stl.resize(MEDIUM + SHORT);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft::vector<int>		*ft_tmp = new ft::vector<int>(MEDIUM);
			std::vector<int>	*stl_tmp = new std::vector<int>(MEDIUM);

			ft_tmp->push_back(val);
			stl_tmp->push_back(val);

			ft_tmp->reserve(MEDIUM + SHORT);
			delete	ft_tmp;
			delete	stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft::vector<int>		*ft_tmp = new ft::vector<int>(MEDIUM);
			std::vector<int>	*stl_tmp = new std::vector<int>(MEDIUM);

			ft_tmp->push_back(val);
			stl_tmp->push_back(val);

			stl_tmp->reserve(MEDIUM + SHORT);
			delete	ft_tmp;
			delete	stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	return true;
}

static bool elements_access_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "Elements Access test" << std::endl
		<< "Using a randomly filled vector of size " << MEDIUM << std::endl
		<< std::endl << "#######################################" << std::endl << std::endl
		<< "operator[]" << std::endl << std::endl
		<< "accessing vector[" << MEDIUM / 4 << "] :		";

	ft::vector<int>		ft;
	std::vector<int>	stl;

	get_identical_random_filled_vectors(MEDIUM, &ft, &stl);

	if (!(print_test_result(ft[MEDIUM / 4] == stl[MEDIUM / 4])))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			ft[MEDIUM / 4];
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			stl[MEDIUM / 4];
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << "vector[" << MEDIUM / 4 << "] = 1 on same vector :	";

	ft[MEDIUM / 4] = 1;
	stl[MEDIUM / 4] = 1;

	if (!(print_test_result(ft[MEDIUM / 4] == stl[MEDIUM / 4])))
		return false;

	std::cout << "const vector[" << MEDIUM / 4 << "] :		";

	const int	ft_const = ft[MEDIUM / 4];
	const int	stl_const = stl[MEDIUM / 4];

	if (!(print_test_result(ft_const == stl_const)))
		return false;

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "function at()" << std::endl << std::endl
		<< "accessing vector.at(" << MEDIUM / 4 << ") :	";

	if (!(print_test_result(ft.at(MEDIUM / 4) == stl.at(MEDIUM / 4))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			ft.at(MEDIUM / 4);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			stl.at(MEDIUM / 4);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << "vector.at(" << MEDIUM / 4 << ") = 2 :		";

	ft.at(MEDIUM / 4) = 2;
	stl.at(MEDIUM / 4) = 2;

	if (!(print_test_result(ft.at(MEDIUM / 4) == stl.at(MEDIUM / 4))))
		return false;

	std::cout << "const vector.at(" << MEDIUM / 4 << ") :		";

	const int	ft_const2 = ft.at(MEDIUM / 4);
	const int	stl_const2 = stl.at(MEDIUM / 4);

	if (!(print_test_result(ft_const2 == stl_const2)))
		return false;

	if (!at_try_catch(ft, stl))
		return false;

	std::cout << std::endl<< "#######################################" << std::endl << std::endl
		<< "function front()" << std::endl << std::endl
		<< "accessing vector.front() :	";

	if (!(print_test_result(ft.front() == stl.front())))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			ft.front();
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			stl.front();
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << "vector.front() = 2 :		";

	ft.front() = 2;
	stl.front() = 2;

	if (!(print_test_result(ft.front() == stl.front())))
		return false;

	std::cout << "const vector.front() :		";

	const int	ft_const3 = ft.front();
	const int	stl_const3 = stl.front();

	if (!(print_test_result(ft_const3 == stl_const3)))
		return false;

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "function back()" << std::endl << std::endl
		<< "accessing vector.back() :	";

	if (!(print_test_result(ft.back() == stl.back())))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			ft.back();
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			stl.back();
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << "vector.back() = 6 :		";

	ft.back() = 6;
	stl.back() = 6;

	if (!(print_test_result(ft.back() == stl.back())))
		return false;

	std::cout << "const vector.back() :		";

	const int	ft_const4 = ft.back();
	const int	stl_const4 = stl.back();

	if (!(print_test_result(ft_const4 == stl_const4)))
		return false;

	return true;
}

static bool	assign_test(bool time_check)
{
	int	val(std::rand());

	std::cout << "_______________________________________________" << std::endl
		<< "Assign" << std::endl << std::endl
		<< std::endl << "#######################################" << std::endl << std::endl
		<< "fill assign" << std::endl << std::endl
		<< "vector.assign(" << MEDIUM << ", " << val << ") on empty vector" << std::endl;
	
	ft::vector<int>		*ft = new ft::vector<int>;
	std::vector<int>	*stl = new std::vector<int>;

	ft->assign(MEDIUM, val);
	stl->assign(MEDIUM, val);

	if (!(print_test_result(vector_compare(*ft, *stl))))
		return false;

	if (time_check)
	{
		ft::vector<int>		*ft_tmp;
		std::vector<int>	*stl_tmp;
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			ft_tmp->assign(MEDIUM, val);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			stl_tmp->assign(MEDIUM, val);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	val = std::rand();

	std::cout << std::endl << std::endl
		<< "vector.assign(" << LARGE << ", " << val
		<< ") on previously assigned vector" << std::endl;

	ft->assign(LARGE, val);
	stl->assign(LARGE, val);

	if (!(print_test_result(vector_compare(*ft, *stl))))
		return false;

	delete	ft;
	delete	stl;

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "range assign" << std::endl << std::endl
		<< "Using a randomly filled source of size " << MEDIUM << " on empty vector" << std::endl;

	ft::vector<int>		ft_src;
	std::vector<int>	stl_src;
	
	ft = new ft::vector<int>;
	stl = new std::vector<int>;

	get_identical_random_filled_vectors(MEDIUM, &ft_src, &stl_src);
	ft->assign(ft_src.begin(), ft_src.end());
	stl->assign(stl_src.begin(), stl_src.end());

	if (!(print_test_result(vector_compare(*ft, *stl))))
		return false;

	if (time_check)
	{
		ft::vector<int>		*ft_tmp;
		std::vector<int>	*stl_tmp;
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			ft_tmp->assign(ft_src.begin(), ft_src.end());

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			stl_tmp->assign(stl_src.begin(), stl_src.end());

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << std::endl
		<< "Using a new randomly filled source of size " << LARGE
		<< " on previously assigned vector" << std::endl;

	ft_src.clear();
	stl_src.clear();
	get_identical_random_filled_vectors(LARGE, &ft_src, &stl_src);
	ft->assign(ft_src.begin(), ft_src.end());
	stl->assign(stl_src.begin(), stl_src.end());

	if (!(print_test_result(vector_compare(*ft, *stl))))
		return false;

	delete	ft;
	delete	stl;

	return true;
}

static bool	push_back_test(bool time_check)
{
	int val(std::rand());

	std::cout << "_______________________________________________" << std::endl
		<< "push_back test" << std::endl << std::endl
		<< "vector.push_back(" << val << ") on empty vector" << std::endl << std::endl;

	ft::vector<int>		ft;
	std::vector<int>	stl;

	ft.push_back(val);
	stl.push_back(val);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft::vector<int>		*ft_tmp = new ft::vector<int>;

			ft_tmp->push_back(val);
			delete	ft_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			std::vector<int>	*stl_tmp = new std::vector<int>;

			stl_tmp->push_back(val);
			delete	stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	val = std::rand();

	std::cout << "#######################################" << std::endl << std::endl
		<< "vector.push_back(" << val << ") on same vector" << std::endl << std::endl;

	ft.push_back(val);
	stl.push_back(val);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft::vector<int>		*ft_tmp = new ft::vector<int>(ft);
			std::vector<int>	*stl_tmp = new std::vector<int>(stl);

			ft_tmp->push_back(val);
			delete	ft_tmp;
			delete	stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft::vector<int>		*ft_tmp = new ft::vector<int>(ft);
			std::vector<int>	*stl_tmp = new std::vector<int>(stl);

			stl_tmp->push_back(val);
			delete	ft_tmp;
			delete	stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	return true;
}

static bool	pop_back_test()
{
	/*
	std::vector<int>	vec;													//Uncomment shows segfault on stl vector
	vec.pop_back();																//when using pop_back() on empty then iterating
	for (std::vector<int>::iterator	it = vec.begin(); it != vec.end(); it++)	//so i removed empty protection from my pop_back()
		std::cout << *it << std::endl;											//method and my vector crashs too now, yay
	*/


	std::cout << "_______________________________________________" << std::endl
		<< "pop_back test" << std::endl << std::endl
		<< "vector.pop_back() on vector with size = " << SHORT << std::endl << std::endl;

	ft::vector<int>		ft(SHORT);
	std::vector<int>	stl(SHORT);

	ft.pop_back();
	stl.pop_back();

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	return true;
}

static bool	insert_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "insert test" << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "vector.insert() on empty vector at vector.begin()" << std::endl << std::endl
		<< "single value (5)" << std::endl << std::endl;

	ft::vector<int>		ft;
	std::vector<int>	stl;
	ft::vector<int>		*ft_tmp;
	std::vector<int>	*stl_tmp;

	ft::vector<int>::const_iterator		ftit;
	std::vector<int>::const_iterator	stlit;

	ftit = ft.insert(ft.begin(), 5);
	stlit = stl.insert(stl.begin(), 5);

	std::cout << "Return :		";

	if (!(print_test_result(*ftit == *stlit)))
		return false;

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	ft.clear();
	stl.clear();

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			ft_tmp->insert(ft_tmp->begin(), 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			stl_tmp->insert(stl_tmp->begin(), 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << SHORT << " value (5)" << std::endl << std::endl;

	ft.insert(ft.begin(), SHORT, 5);
	stl.insert(stl.begin(), SHORT, 5);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	ft.clear();
	stl.clear();

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			ft_tmp->insert(ft_tmp->begin(), SHORT, 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			stl_tmp->insert(stl_tmp->begin(), SHORT, 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << "Random range with size = " << SHORT << std::endl << std::endl;

	ft::vector<int>		ft_src;
	std::vector<int>	stl_src;

	get_identical_random_filled_vectors(SHORT, &ft_src, &stl_src);

	ft.insert(ft.begin(), ft_src.begin(), ft_src.end());
	stl.insert(stl.begin(), stl_src.begin(), stl_src.end());

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			ft_tmp->insert(ft_tmp->begin(), ft_src.begin(), ft_src.end());

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>;
			stl_tmp = new std::vector<int>;

			stl_tmp->insert(stl_tmp->begin(), stl_src.begin(), stl_src.end());

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "vector.insert() on same vector" << std::endl << std::endl
		<< "single value (5) at vector.begin() + (vector.size() / 2)" << std::endl << std::endl;

	ftit = ft.insert(ft.begin() + (ft.size() / 2), 5);
	stlit = stl.insert(stl.begin() + (stl.size() / 2), 5);

	std::cout << "Return :		";

	if (!(print_test_result(*ftit == *stlit)))
		return false;

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			ft_tmp->insert(ft_tmp->begin(), 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			stl_tmp->insert(stl_tmp->begin(), 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << SHORT
		<< " value (5) at vector.begin() + (vector.size() / 2)" << std::endl << std::endl;

	ft.insert(ft.begin() + (ft.size() / 2), SHORT, 5);
	stl.insert(stl.begin() + (stl.size() / 2), SHORT, 5);

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			ft_tmp->insert(ft_tmp->begin(), SHORT, 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			stl_tmp->insert(stl_tmp->begin(), SHORT, 5);

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl <<
		"Random range previously used at vector.begin() + (vector.size() / 2)" << std::endl << std::endl;

	ft.insert(ft.begin() + (ft.size() / 2), ft_src.begin(), ft_src.end());
	stl.insert(stl.begin() + (stl.size() / 2), stl_src.begin(), stl_src.end());

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			ft_tmp->insert(ft_tmp->begin() + (ft_tmp->size() / 2), ft_src.begin(), ft_src.end());

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			stl_tmp->insert(stl_tmp->begin() + (stl_tmp->size() / 2), stl_src.begin(), stl_src.end());

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	return true;
}

static bool	erase_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "erase test" << std::endl << std::endl
		<< "using randomly generated vector with size = " << MEDIUM << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "erase single value (begin() + size() / 4)" << std::endl << std::endl;

	ft::vector<int>						ft;
	std::vector<int>					stl;
	ft::vector<int>						*ft_tmp;
	std::vector<int>					*stl_tmp;
	ft::vector<int>::const_iterator		ftit;
	std::vector<int>::const_iterator	stlit;

	get_identical_random_filled_vectors(MEDIUM, &ft, &stl);

	ftit = ft.erase(ft.begin() + (ft.size() / 4));
	stlit = stl.erase(stl.begin() + (stl.size() / 4));

	std::cout << "Return :		";

	if (!(print_test_result(*ftit == *stlit)))
		return false;

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if(time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			ft_tmp->erase(ft_tmp->begin() + (ft_tmp->size() / 4));

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			stl_tmp->erase(stl_tmp->begin() + (stl_tmp->size() / 4));

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "erase range from (begin() + size() / 8) to (begin() + size() / 2)" << std::endl << std::endl;

	ftit = ft.erase(ft.begin() + (ft.size() / 8), ft.begin() + (ft.size() / 2));
	stlit = stl.erase(stl.begin() + (stl.size() / 8), stl.begin() + (stl.size() / 2));

	std::cout << "Return :		";

	if (!(print_test_result(*ftit == *stlit)))
		return false;

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if(time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			ft_tmp->erase(ft_tmp->begin() + (ft_tmp->size() / 8), ft_tmp->begin() + (ft_tmp->size() / 2));

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			stl_tmp->erase(stl_tmp->begin() + (stl_tmp->size() / 8), stl_tmp->begin() + (stl_tmp->size() / 2));

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "erase range from begin() to end()" << std::endl << std::endl;

	ftit = ft.erase(ft.begin(), ft.end());
	stlit = stl.erase(stl.begin(), stl.end());

	std::cout << "Return :		";

	if (!(print_test_result(*ftit == *stlit)))
		return false;

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	return true;
}

static bool	swap_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "swap test" << std::endl << std::endl
		<< "using randomly generated vector with size = " << SHORT << std::endl;

	ft::vector<int>		ft1;
	std::vector<int>	stl1;
	ft::vector<int>		ft2;
	std::vector<int>	stl2;

	get_identical_random_filled_vectors(SHORT, &ft1, &stl1);
	get_identical_random_filled_vectors(SHORT, &ft2, &stl2);

	ft1.swap(ft2);
	stl1.swap(stl2);

	std::cout << std::endl << "first vector :	" << std::endl << std::endl;
	if (!(print_test_result(vector_compare(ft1, stl1))))
		return false;

	std::cout << std::endl << "second vector :	" << std::endl << std::endl;
	if (!(print_test_result(vector_compare(ft2, stl2))))
		return false;

	if (time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			ft1.swap(ft2);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			stl1.swap(stl2);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	std::cout << std::endl << std::endl
		<< "first vector size = " << SHORT <<" and second size = " << MEDIUM << std::endl;

	ft2.clear();
	stl2.clear();

	get_identical_random_filled_vectors(MEDIUM, &ft2, &stl2);

	ft1.swap(ft2);
	stl1.swap(stl2);

	std::cout << std::endl << "first vector :	" << std::endl << std::endl;
	if (!(print_test_result(vector_compare(ft1, stl1))))
		return false;

	std::cout << std::endl << "second vector :	" << std::endl << std::endl;
	if (!(print_test_result(vector_compare(ft2, stl2))))
		return false;

	if(time_check)
	{
		timeval				start, end;
		double				ft_time, stl_time;

		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
			ft1.swap(ft2);
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
			stl1.swap(stl2);
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	return true;
}

static bool	clear_test(bool time_check)
{
	std::cout << "_______________________________________________" << std::endl
		<< "clear test" << std::endl << std::endl
		<< "Empty :			" << std::endl;

	ft::vector<int>		ft;
	std::vector<int>	stl;

	ft.clear();
	stl.clear();

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "random vector with size = " << SHORT << std::endl << std::endl;

	get_identical_random_filled_vectors(SHORT, &ft, &stl);

	ft.clear();
	stl.clear();

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "random vector with size = " << MEDIUM << std::endl << std::endl;

	get_identical_random_filled_vectors(MEDIUM, &ft, &stl);

	ft.clear();
	stl.clear();

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "random vector with size = " << LARGE << std::endl << std::endl;

	get_identical_random_filled_vectors(LARGE, &ft, &stl);

	ft.clear();
	stl.clear();

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "random vector with size = " << EXTRA_LARGE << std::endl << std::endl;

	get_identical_random_filled_vectors(EXTRA_LARGE, &ft, &stl);

	ft.clear();
	stl.clear();

	if (!(print_test_result(vector_compare(ft, stl))))
		return false;

	if (time_check)
	{
		ft::vector<int>		*ft_tmp;
		std::vector<int>	*stl_tmp;
		timeval				start, end;
		double				ft_time, stl_time;

		get_identical_random_filled_vectors(EXTRA_LARGE, &ft, &stl);
		print_time_start(&start);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			ft_tmp->clear();

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		ft_time = timeval_diff_to_ms(start, end);
		gettimeofday(&start, nullptr);
		for (int i = 0; i <= NB_REPEAT; i++)
		{
			ft_tmp = new ft::vector<int>(ft);
			stl_tmp = new std::vector<int>(stl);

			stl_tmp->clear();

			delete ft_tmp;
			delete stl_tmp;
		}
		gettimeofday(&end, nullptr);
		stl_time = timeval_diff_to_ms(start, end);
		if (print_test_result(ft_time <= (stl_time * 20)) == false)
			return false;
	}

	return true;
}

static bool	relationnal_operators_test()
{
	std::cout << "_______________________________________________" << std::endl
		<< "Relational operator test" << std::endl << std::endl
		<< "vec1 = randomly filled vector of size " << MEDIUM << ";" << std::endl
		<< "vec2 = vec1 copy;" << std::endl
		<< "vec3 = other random vec of size " << MEDIUM << ";" << std::endl
		<< "vec4 = other random vec of size " << LARGE << ";" << std::endl
		<< "vec5 = other random vec of size " << SHORT << ";" << std::endl << std::endl;

	ft::vector<int>		ft1;
	ft::vector<int>		ft2;
	ft::vector<int>		ft3;
	ft::vector<int>		ft4;
	ft::vector<int>		ft5;
	std::vector<int>	stl1;
	std::vector<int>	stl2;
	std::vector<int>	stl3;
	std::vector<int>	stl4;
	std::vector<int>	stl5;

	get_identical_random_filled_vectors(MEDIUM, &ft1, &stl1);

	ft2.assign(ft1.begin(), ft1.end());
	stl2.assign(stl1.begin(), stl1.end());

	get_identical_random_filled_vectors(MEDIUM, &ft3, &stl3);
	get_identical_random_filled_vectors(LARGE, &ft4, &stl4);
	get_identical_random_filled_vectors(SHORT, &ft4, &stl4);

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"==\" " << std::endl << std::endl
		<< "vec1 == vec2 ? :		";

	if (!print_test_result((ft1 == ft2) == (stl1 == stl2)))
		return false;

	std::cout << "vec1 == vec3 ? :		";

	if (!print_test_result((ft1 == ft3) == (stl1 == stl3)))
		return false;

	std::cout << "vec1 == vec4 ? :		";

	if (!print_test_result((ft1 == ft4) == (stl1 == stl4)))
		return false;

	std::cout << "vec1 == vec5 ? :		";

	if (!print_test_result((ft1 == ft5) == (stl1 == stl5)))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"!=\" " << std::endl << std::endl
		<< "vec1 != vec2 ? :		";

	if (!print_test_result((ft1 != ft2) == (stl1 != stl2)))
		return false;

	std::cout << "vec1 != vec3 ? :		";

	if (!print_test_result((ft1 != ft3) == (stl1 != stl3)))
		return false;

	std::cout << "vec1 != vec4 ? :		";

	if (!print_test_result((ft1 != ft4) == (stl1 != stl4)))
		return false;

	std::cout << "vec1 != vec5 ? :		";

	if (!print_test_result((ft1 != ft5) == (stl1 != stl5)))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<\" " << std::endl << std::endl
		<< "vec1 < vec2 ? :			";

	if (!print_test_result((ft1 < ft2) == (stl1 < stl2)))
		return false;

	std::cout << "vec1 < vec3 ? :			";

	if (!print_test_result((ft1 < ft3) == (stl1 < stl3)))
		return false;

	std::cout << "vec1 < vec4 ? :			";

	if (!print_test_result((ft1 < ft4) == (stl1 < stl4)))
		return false;

	std::cout << "vec1 < vec5 ? :			";

	if (!print_test_result((ft1 < ft5) == (stl1 < stl5)))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<=\" " << std::endl << std::endl
		<< "vec1 <= vec2 ? :		";

	if (!print_test_result((ft1 <= ft2) == (stl1 <= stl2)))
		return false;

	std::cout << "vec1 <= vec3 ? :		";

	if (!print_test_result((ft1 <= ft3) == (stl1 <= stl3)))
		return false;

	std::cout << "vec1 <= vec4 ? :		";

	if (!print_test_result((ft1 <= ft4) == (stl1 <= stl4)))
		return false;

	std::cout << "vec1 <= vec5 ? :		";

	if (!print_test_result((ft1 <= ft5) == (stl1 <= stl5)))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">\" " << std::endl << std::endl
		<< "vec1 > vec2 ? :			";

	if (!print_test_result((ft1 > ft2) == (stl1 > stl2)))
		return false;

	std::cout << "vec1 > vec3 ? :			";

	if (!print_test_result((ft1 > ft3) == (stl1 > stl3)))
		return false;

	std::cout << "vec1 > vec4 ? :			";

	if (!print_test_result((ft1 > ft4) == (stl1 > stl4)))
		return false;

	std::cout << "vec1 > vec5 ? :			";

	if (!print_test_result((ft1 > ft5) == (stl1 > stl5)))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">=\" " << std::endl << std::endl
		<< "vec1 >= vec2 ? :		";

	if (!print_test_result((ft1 >= ft2) == (stl1 >= stl2)))
		return false;

	std::cout << "vec1 >= vec3 ? :		";

	if (!print_test_result((ft1 >= ft3) == (stl1 >= stl3)))
		return false;

	std::cout << "vec1 >= vec4 ? :		";

	if (!print_test_result((ft1 >= ft4) == (stl1 >= stl4)))
		return false;

	std::cout << "vec1 >= vec5 ? :		";

	if (!print_test_result((ft1 >= ft5) == (stl1 >= stl5)))
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

	if (iterators_test(time_check) == false)
		return false;

	if (resize_test(time_check) == false)
		return false;

	if (reserve_test(time_check) == false)
		return false;

	if (elements_access_test(time_check) == false)
		return false;

	if (assign_test(time_check) == false)
		return false;

	if (push_back_test(time_check) == false)
		return false;

	if (pop_back_test() == false)
		return false;

	if (insert_test(time_check) == false)
		return false;

	if (erase_test(time_check) == false)
		return false;

	if (swap_test(time_check) == false)
		return false;

	if (clear_test(time_check) == false)
		return false;

	if (relationnal_operators_test() == false)
		return false;

	std::cout << std::endl << "*****************************************************" << std::endl << std::endl
		<< "Vector :				";
	print_test_result(true);
	std::cout << std::endl << "*****************************************************" << std::endl;

	return true;
}
