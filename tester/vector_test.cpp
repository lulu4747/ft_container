#include <iostream>
#include <vector>
#include "tester.hpp"
#include "../ft_containers/vector.hpp"

template < class FTV, class STDV >
static bool	content_compare(FTV ft, STDV std)
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
	bool	empty;
	bool	size;
	bool	capacity;
	bool	content;

	std::cout << std::endl << "empty() comparison :	";
	empty = print_test_result(ft.empty() == std.empty());
	std::cout << std::endl << "size() comparison :	";
	size = print_test_result(ft.size() == std.size());
	std::cout << std::endl << "capacity() comparison :	";
	capacity = print_test_result(ft.capacity() == std.capacity());
	std::cout << std::endl << "content comparison : 	";
	content = print_test_result(content_compare(ft, std));
	std::cout << std::endl << "General comparison : 			";
	if (!empty || !size || !capacity || !content)
		return false;
	return true;
}

bool	vector_test()
{
	std::cout << "__________________________________________" << std::endl
		<< "	vector" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::vector<int>		ft;
	std::vector<int>	std;

	std::cout << "__________________________________________" << std::endl
		<< "vector.push_back(0) with empty vector :	" << std::endl;
	ft.push_back(0);
	std.push_back(0);
	print_test_result(vector_compare(ft, std));
	std::cout << std::endl;

	std::cout << "__________________________________________" << std::endl
		<< "vector.pop_back() :	" << std::endl;
	ft.pop_back();
	std.pop_back();
	print_test_result(vector_compare(ft, std));
	std::cout << std::endl;

	for (int i = 0; i <= 50 ; i++)
	{
		std::cout << "__________________________________________" << std::endl
			<< "vector.push_back(" << i << ") :	" << std::endl;
		ft.push_back(i);
		std.push_back(i);
		print_test_result(vector_compare(ft, std));
		std::cout << std::endl;
	}

	while(!ft.empty())
	{
		std::cout << "__________________________________________" << std::endl
			<< "vector.pop_back()	" << std::endl;
		ft.pop_back();
		std.pop_back();
		print_test_result(vector_compare(ft, std));
		std::cout << std::endl;
	}

	return true;
}