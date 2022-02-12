#include <iostream>
#include "tester.hpp"

bool	print_test_result(bool bl)
{
	if(bl == true)
		std::cout << BOLDGREEN << "[OK]";
	else
		std::cout << BOLDRED <<  "[KO]";
	std::cout << RESET;
	return bl;
}