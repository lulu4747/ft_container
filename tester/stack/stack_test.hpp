#ifndef STACK_TEST_HPP
# define STACK_TEST_HPP

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <stack>
	#include <utility>
	namespace ft = std;
#else
	#include <stack.hpp>
	#include <algorithm.hpp>
	#include <pair.hpp>
	#include <type_trait.hpp>
#endif

# include <iostream>

template < class STACK >
void	print_content(const STACK &src)
{
	STACK	stk(src);

	while (!stk.empty())
	{
		std::cout << "	|" << stk.top() << "|";
		stk.pop();
	}
	std::cout << std::endl;
}

template < class STACK >
void	print_attributes(const STACK &stk)
{
	std::cout << "stk.empty() =	" << stk.empty() << std::endl
		<< "stk.size() =	" << stk.size() << std::endl
		<< "content :" << std::endl;
		print_content(stk);
		std::cout << std::endl;
}

#endif