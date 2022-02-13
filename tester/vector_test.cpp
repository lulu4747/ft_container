#include <iostream>
#include <vector>
#include "tester.hpp"
#include "../ft_containers/vector.hpp"

#include <sys/time.h>

template < class FTV, class STDV >
static bool	content_compare(FTV &ft, STDV &std)
{
	typename FTV::iterator	ftit(ft.begin());
	typename STDV::iterator	stdit(std.begin());

	while (ftit != ft.end() && stdit != std.end())
	{
		if (*ftit != *stdit)
			return false;
		ftit++;
		stdit++;
	}
	if (ftit != ft.end() || stdit != std.end())
		return false;
	return true;
}

template < class FT, class STD >
static bool	vector_compare(FT &ft, STD &std)
{
	bool	empty, max_size, size, capacity, content;

	std::cout << std::endl << "empty() comparison :	";
	empty = print_test_result(ft.empty() == std.empty());
	std::cout << std::endl << "max_size() comparison :	";
	max_size = print_test_result(ft.max_size() == std.max_size());
	std::cout << std::endl << "size() comparison :	";
	size = print_test_result(ft.size() == std.size());
	std::cout << std::endl << "capacity() comparison :	";
	capacity = print_test_result(ft.capacity() == std.capacity());
	std::cout << std::endl << "content comparison : 	";
	content = print_test_result(content_compare(ft, std));
	std::cout << std::endl << "General comparison : 			";
	if (!empty || !max_size || !size || !capacity || !content)
		return false;
	return true;
}

static bool	vector_assignation_constructor_test()
{
	int	n = 10, val = 8;
	std::cout << "__________________________________________" << std::endl
		<< "assignation construction with n = " << n << ", val = " << val << std::endl << std::endl;

	ft::vector<int>		ft(n, val);
	std::vector<int>	std(n, val);

	if (!(print_test_result(vector_compare(ft, std))))
		return false;
	std::cout << std::endl;
	return true;
}

template < class FT, class STD >
static bool	vector_copy_constructor_test(FT &ft, STD &std)
{
	std::cout << "__________________________________________" << std::endl
		<< "copy construction" << std::endl << std::endl;

	ft::vector<int>		ft2(ft);
	std::vector<int>	std2(std);

	if (!(print_test_result(vector_compare(ft2, std2))))
		return false;
	std::cout << std::endl;
	return true;
}

bool	vector_test()
{
	std::cout << "__________________________________________" << std::endl
		<< "	vector" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::vector<int>		ft;
	std::vector<int>	std;

	if (!(print_test_result(vector_compare(ft, std))))
		return false;
	std::cout << std::endl;

	if (vector_assignation_constructor_test() == false)
		return false;

	std::cout << "__________________________________________" << std::endl
		<< "vector.push_back(0) with empty vector :	" << std::endl;
	ft.push_back(0);
	std.push_back(0);
	if (!(print_test_result(vector_compare(ft, std))))
		return false;
	std::cout << std::endl;

	std::cout << "__________________________________________" << std::endl
		<< "vector.pop_back() :	" << std::endl;
	ft.pop_back();
	std.pop_back();
	if (!(print_test_result(vector_compare(ft, std))))
		return false;
	std::cout << std::endl;

//
	struct timeval	start, end;
	double	ft_time; //, std;
	gettimeofday(&start, nullptr);
//

	for (int i = 0; i <= 5000 ; i++)
	{
		std::cout << "__________________________________________" << std::endl
			<< "vector.push_back(" << i << ") :	" << std::endl;
		ft.push_back(i);
		std.push_back(i);
		if (!(print_test_result(vector_compare(ft, std))))
			return false;
		std::cout << std::endl;
	}
//
	gettimeofday(&end, nullptr);
	ft_time = timeval_diff_to_ms(start, end);
	std::cout << std::endl << std::endl << ft_time << std::endl << std::endl;
//

	if (vector_copy_constructor_test(ft, std) == false)
		return false;
/*
	std::cout << "__________________________________________" << std::endl
		<< "clear()" << std::endl << std::endl;
	ft2.clear();
	std2.clear();
	if (!(print_test_result(vector_compare(ft2, std2))))
		return false;
	std::cout << std::endl;
*/
	return true;
}
