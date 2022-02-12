#include <iostream>
#include <stack>
#include "tester.hpp"
#include "../ft_containers/stack.hpp"

template < class FT, class STD >
static bool	content_compare(FT ft, STD std)
{
	while (!ft.empty())
	{
		if (ft.top() != std.top())
			return false;
		ft.pop();
		std.pop();
	}
	return true;
}

template < class FT, class STD >
static bool	stack_compare(FT &ft, STD &std)
{
	if (ft.size() != std.size())
		return false;
	return content_compare(ft, std);
}

bool	stack_test()
{
	std::cout << "__________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::stack<int>	ft;
	std::stack<int>	std;

	std::cout << "stack.empty() with empty stack :	";
	print_test_result(ft.empty() == std.empty());
	std::cout << std::endl;

	std::cout << "stack.push(0) with empty stack :	";
	ft.push(0);
	std.push(0);
	print_test_result(stack_compare(ft, std));
	std::cout << std::endl;
	return true;
}