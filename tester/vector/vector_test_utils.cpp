#include <iostream>
#include <vector>
#include "../tester.hpp"
#include "../../ft_containers/vector.hpp"

std::vector<int>	get_random_vector(size_t n)
{
	std::vector<int>	vector;

	for (size_t i = 0; i < n; i++)
		vector.push_back(rand());
	return vector;
}

void	get_identical_random_filled_vectors(size_t n, ft::vector<int> *ft, std::vector<int> *stl)
{
	std::vector<int>	src(get_random_vector(n));

	for (std::vector<int>::iterator it = src.begin(); it != src.end(); it++)
	{
		ft->push_back(*it);
		stl->push_back(*it);
	}
}

bool	recursive_call(bool (*f)(bool, int), bool time_check, int n)
{
	if (n == EMPTY)
		return f(time_check, SHORT);
	if (n == SHORT)
		return f(time_check, MEDIUM);
	if (n == MEDIUM)
		return f(time_check, LARGE);
	if (n == LARGE)
		return f(time_check, EXTRA_LARGE);
	return true;
}
