#include <iostream>
#include <sys/time.h>
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

double	timeval_diff_to_ms(timeval &start, timeval &end)
{
	double ret = ((((end.tv_sec - start.tv_sec) * 1e6) + (end.tv_usec - start.tv_usec)) * 1e-6);

	if (ret == 0)
		return 1e-06;
	return ret;
}