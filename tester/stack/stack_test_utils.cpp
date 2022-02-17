#include <iostream>
#include <stack>
#include "stack_test.hpp"
#include "../tester.hpp"
#include "../../ft_containers/stack.hpp"

bool	content_compare(ft::stack<int> ft, std::stack<int> stl)
{
	Mutant_FT_Stack<int>	mft(ft);
	Mutant_STL_Stack<int>	mstl(stl);
	Mutant_FT_Stack<int>::const_iterator	ftit = mft.begin();
	Mutant_STL_Stack<int>::const_iterator	stlit = mstl.begin();

	while (ftit != mft.end())
	{
		if (*ftit != *stlit)
		{
			std::cout << *ftit << "	|	" << *stlit << std::endl;
			return false;
		}
		ftit++;
		stlit++;
	}
	if (stlit != mstl.end())
		return false;
	return true;
}

bool	stack_compare(ft::stack<int> ft, std::stack<int> stl)
{
	bool	empty, size, content;

	std::cout << "empty() comparison :	";
	empty = print_test_result(ft.empty() == stl.empty());
	std::cout << "size() comparison :	";
	size = print_test_result(ft.size() == stl.size());
	if (!size)
		std::cout << ft.size() << "	|	" << stl.size() << "	" << std::endl;
	std::cout << "content comparison : 	";
	content = print_test_result(content_compare(ft, stl));
	std::cout << "General comparison : 			";
	if (!empty || !size || !content)
		return false;
	return true;
}
