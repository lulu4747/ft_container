#include <iostream>
#include <sys/time.h>
#include <vector>
#include "../tester.hpp"
#include "../../ft_containers/vector.hpp"

void	at_try_catch(ft::vector<int> &ft, std::vector<int> &stl)
{
	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "try/catch with vector.at(" << MEDIUM - 1 << ") :	";

	try
	{
		ft.at(MEDIUM - 1);
		std::cout << "no exception" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "catched" << std::endl;
	}

	std::cout << "try/catch with vector.at(" << MEDIUM << ") :	";

	try
	{
		ft.at(MEDIUM);
		std::cout << "no exception" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "catched" << std::endl;
	}

	std::cout << "try/catch with vector.at(" << MEDIUM + 1<< ") :	";

	try
	{
		ft.at(MEDIUM + 1);
		std::cout << "no exception" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "catched" << std::endl;
	}
}

