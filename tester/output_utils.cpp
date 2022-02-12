#include <iostream>
#include "tester.hpp"

void	bool_comp(bool ft, bool std)
{
	if(ft == std)
		std::cout << BOLDGREEN << "[OK]";
	else
		std::cout << BOLDRED <<  "[KO]";
	std::cout << RESET << std::endl;	
}