#include <iostream>
#include <stack>
#include "tester.hpp"
#include "../ft_containers/stack.hpp"

bool	stack_test()
{
	std::cout << "__________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::stack<int>	ft;
	std::stack<int>	std;

	std::cout << "stack.empty() with empty stack :	";
	bool_comp(ft.empty(), std.empty());
	return 0;
}