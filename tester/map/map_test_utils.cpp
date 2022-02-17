#include <iostream>
#include <map>
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
