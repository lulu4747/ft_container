#include <iostream>
#include <map>
#include <sys/time.h>
#include "map_test.hpp"
#include "../tester.hpp"
#include "../../ft_containers/map.hpp"
#include "../../utility/pair.hpp"

bool	content_compare(ft::map< int, char > &ft, std::map< int, char > &stl)
{
	ft::map< int, char >::iterator	ftit(ft.begin());
	std::map< int, char >::iterator	stlit(stl.begin());

	while (ftit != ft.end() && stlit != stl.end())
	{
		if (ftit->first != stlit->first || ftit->second != stlit->second)
		{
			std::cout << std::endl << ftit->first << " | " << stlit->first << std::endl
				<< ftit->second << " | " << stlit->second << "		";
			return false;
		}
		ftit++;
		stlit++;
	}
	if (ftit != ft.end() || stlit != stl.end())
		return false;
	return true;
}

bool	map_compare(ft::map< int, char > &ft, std::map< int, char > &stl)
{
	bool	empty, max_size, size, content;

	std::cout << "empty() comparison :	";
	empty = print_test_result(ft.empty() == stl.empty());
	std::cout << "max_size() comparison :	";
	max_size = print_test_result(ft.max_size() == stl.max_size());
	std::cout << "size() comparison :	";
	size = print_test_result(ft.size() == stl.size());
	if (!size)
		std::cout << ft.size() << "	|	" << stl.size() << "	" << std::endl;
	std::cout << "content comparison : 	";
	content = print_test_result(content_compare(ft, stl));
	std::cout << "General comparison : 			";
	if (!empty || !max_size || !size || !content)
		return false;
	return true;
}

void	get_identical_random_filled_maps(size_t n, ft::map< int, char > *ft, std::map< int, char > *stl)
{
	int		key;
	char	val;

	for (size_t i = 0; i < n; i++)
	{
		key = std::rand();
		val = (std::rand() % 94) + 32;
		ft->insert(ft::make_pair(key, val));
		stl->insert(std::make_pair(key, val));
	}
	return ;
}

void	get_crescent_key_filled_maps(size_t n, ft::map< int, char > *ft, std::map< int, char > *stl)
{
	char	val;

	for (size_t i = 0; i < n; i++)
	{
		val = (std::rand() % 94) + 32;
		ft->insert(ft::make_pair(i, val));
		stl->insert(std::make_pair(i, val));
	}
	return ;
}

void	begin(ft::map< int, char > &map)
{
	map.begin();
}

void	begin(std::map< int, char > &map)
{
	map.begin();
}

void	begin_to_end(ft::map< int, char > &map)
{
	ft::map< int, char >::iterator	it = map.begin();

	while (it != map.end())
		it++;
}

void	begin_to_end(std::map< int, char > &map)
{
	std::map< int, char >::iterator	it = map.begin();

	while (it != map.end())
		it++;
}

void	end_to_begin(ft::map< int, char > &map)
{
	ft::map< int, char >::iterator	it = map.end();

	it--;
	while (it != map.begin())
		it--;
}

void	end_to_begin(std::map< int, char > &map)
{
	std::map< int, char >::iterator	it = map.end();

	it--;
	while (it != map.begin())
		it--;
}

void	rbegin(ft::map< int, char > &map)
{
	map.rbegin();
}

void	rbegin(std::map< int, char > &map)
{
	map.rbegin();
}

void	rbegin_to_rend(ft::map< int, char > &map)
{
	ft::map< int, char >::reverse_iterator	rit = map.rbegin();

	while (rit != map.rend())
		rit++;
}

void	rbegin_to_rend(std::map< int, char > &map)
{
	std::map< int, char >::reverse_iterator	rit = map.rbegin();

	while (rit != map.rend())
		rit++;
}

void	rend_to_rbegin(ft::map< int, char > &map)
{
	ft::map< int, char >::reverse_iterator	rit = map.rend()--;

	while (rit != map.rbegin())
		rit--;
}

void	rend_to_rbegin(std::map< int, char > &map)
{
	std::map< int, char >::reverse_iterator	rit = map.rend()--;

	while (rit != map.rbegin())
		rit--;
}

bool	iterator_time_check(void (*ft_func)(ft::map< int, char >&), void (*stl_func)(std::map< int, char >&),
			ft::map< int, char > &ft, std::map< int, char > &stl)
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
