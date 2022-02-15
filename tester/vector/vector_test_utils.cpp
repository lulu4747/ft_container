#include <iostream>
#include <sys/time.h>
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

void	get_crescent_filled_vectors(size_t n, ft::vector<int> *ft, std::vector<int> *stl)
{
	for (size_t i = 0; i < n; i++)
	{
		ft->push_back(i);
		stl->push_back(i);
	}
}

void	begin(ft::vector<int> &vec)
{
	vec.begin();
}

void	begin(std::vector<int> &vec)
{
	vec.begin();
}

void	begin_to_end(ft::vector<int> &vec)
{
	ft::vector<int>::iterator	it = vec.begin();

	while (it != vec.end())
		it++;
}

void	begin_to_end(std::vector<int> &vec)
{
	std::vector<int>::iterator	it = vec.begin();

	while (it != vec.end())
		it++;
}

void	end_to_begin(ft::vector<int> &vec)
{
	ft::vector<int>::iterator	it = vec.end() - 1;

	while (it != vec.begin())
		it--;
}

void	end_to_begin(std::vector<int> &vec)
{
	std::vector<int>::iterator	it = vec.end() - 1;

	while (it != vec.begin())
		it--;
}

void	rbegin(ft::vector<int> &vec)
{
	vec.rbegin();
}

void	rbegin(std::vector<int> &vec)
{
	vec.rbegin();
}

void	rbegin_to_rend(ft::vector<int> &vec)
{
	ft::vector<int>::reverse_iterator	rit = vec.rbegin();

	while (rit != vec.rend())
		rit++;
}

void	rbegin_to_rend(std::vector<int> &vec)
{
	std::vector<int>::reverse_iterator	rit = vec.rbegin();

	while (rit != vec.rend())
		rit++;
}

void	rend_to_rbegin(ft::vector<int> &vec)
{
	ft::vector<int>::reverse_iterator	rit = vec.rend() - 1;

	while (rit != vec.rbegin())
		rit--;
}

void	rend_to_rbegin(std::vector<int> &vec)
{
	std::vector<int>::reverse_iterator	rit = vec.rend() - 1;

	while (rit != vec.rbegin())
		rit--;
}

bool	iterator_time_check(void (*ft_func)(ft::vector<int>&), void (*stl_func)(std::vector<int>&),
			ft::vector<int> &ft, std::vector<int> &stl)
{
	timeval	start, end;
	double	ft_time, stl_time;

	print_time_start(&start);
	for (int i = 0; i <= NB_REPEAT; i++)
		ft_func(ft);
	gettimeofday(&end, nullptr);
	ft_time = timeval_diff_to_ms(start, end);
	gettimeofday(&start, nullptr);
	for (int i = 0; i <= NB_REPEAT; i++)
		stl_func(stl);
	gettimeofday(&end, nullptr);
	stl_time = timeval_diff_to_ms(start, end);
	if (print_test_result(ft_time <= (stl_time * 20)) == false)
		return false;
	return true;
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
