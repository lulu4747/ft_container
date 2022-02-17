#include <iostream>
#include <sys/time.h>
#include <vector>
#include "../tester.hpp"
#include "../../ft_containers/vector.hpp"

bool	content_compare(ft::vector<int> &ft, std::vector<int> &stl)
{
	ft::vector<int>::iterator	ftit(ft.begin());
	std::vector<int>::iterator	stlit(stl.begin());

	while (ftit != ft.end() && stlit != stl.end())
	{
		if (*ftit != *stlit)
		{
			std::cout << std::endl << *ftit << " | " << *stlit << "		";
			return false;
		}
		ftit++;
		stlit++;
	}
	if (ftit != ft.end() || stlit != stl.end())
		return false;
	return true;
}

bool	vector_compare(ft::vector<int> &ft, std::vector<int> &stl)
{
	bool	empty, max_size, size, capacity, content;

	std::cout << "empty() comparison :	";
	empty = print_test_result(ft.empty() == stl.empty());
	std::cout << "max_size() comparison :	";
	max_size = print_test_result(ft.max_size() == stl.max_size());
	std::cout << "size() comparison :	";
	size = print_test_result(ft.size() == stl.size());
	if (!size)
		std::cout << ft.size() << "	|	" << stl.size() << "	" << std::endl;
	std::cout << "capacity() comparison :	";
	capacity = print_test_result(ft.capacity() == stl.capacity());
	if (!capacity)
		std::cout << ft.capacity() << "	|	" << stl.capacity() << "	" << std::endl;
	std::cout << "content comparison : 	";
	content = print_test_result(content_compare(ft, stl));
	std::cout << "General comparison : 			";
	if (!empty || !max_size || !size || !capacity || !content)
		return false;
	return true;
}

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
	if (!ft->empty())
		ft->clear();
	if (!stl->empty())
		stl->clear();
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

bool	at_try_catch(ft::vector<int> &ft, std::vector<int> &stl)
{
	bool	ft_catch;
	bool	stl_catch;

	std::cout << std::endl << "#######################################" << std::endl << std::endl
		<< "try/catch with vector.at(" << MEDIUM - 1 << ") :	";

	try
	{
		ft.at(MEDIUM - 1);
		ft_catch = false;
	}
	catch(std::exception &e)
	{
		ft_catch = true;
	}
	try
	{
		stl.at(MEDIUM - 1);
		stl_catch = false;
	}
	catch(std::exception &e)
	{
		stl_catch = true;
	}
	if (!(print_test_result(ft_catch == stl_catch)))
		return false;

	std::cout << "try/catch with vector.at(" << MEDIUM << ") :	";

	try
	{
		ft.at(MEDIUM);
		ft_catch = false;
	}
	catch(std::exception &e)
	{
		ft_catch = true;
	}
	try
	{
		stl.at(MEDIUM);
		stl_catch = false;
	}
	catch(std::exception &e)
	{
		stl_catch = true;
	}
	if (!(print_test_result(ft_catch == stl_catch)))
		return false;

	std::cout << "try/catch with vector.at(" << MEDIUM + 1<< ") :	";

	try
	{
		ft.at(MEDIUM + 1);
		ft_catch = false;
	}
	catch(std::exception &e)
	{
		ft_catch = true;
	}
	try
	{
		stl.at(MEDIUM + 1);
		stl_catch = false;
	}
	catch(std::exception &e)
	{
		stl_catch = true;
	}
	if (!(print_test_result(ft_catch == stl_catch)))
		return false;
	return true;
}

