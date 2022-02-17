#ifndef MAP_TEST_HPP
# define MAP_TEST_HPP

# include "../tester.hpp"
# include "../../ft_containers/map.hpp"

/*
**			Setup Functions								**
*/

void	get_identical_random_filled_maps(size_t n, ft::map< int, char > *ft, std::map< int, char > *stl);
void	get_crescent_key_filled_maps(size_t n, ft::map< int, char > *ft, std::map< int, char > *stl);

/*
**			Execution Time Functions					**
*/

void	begin(ft::map< int, char > &map);
void	begin(std::map< int, char > &map);
void	begin_to_end(ft::map< int, char > &map);
void	begin_to_end(std::map< int, char > &map);
void	end_to_begin(ft::map< int, char > &map);
void	end_to_begin(std::map< int, char > &map);
void	rbegin(ft::map< int, char > &map);
void	rbegin(std::map< int, char > &map);
void	rbegin_to_rend(ft::map< int, char > &map);
void	rbegin_to_rend(std::map< int, char > &map);
void	rend_to_rbegin(ft::map< int, char > &map);
void	rend_to_rbegin(std::map< int, char > &map);

bool	iterator_time_check(void (*ft_func)(ft::map< int, char > &), void (*stl_func)(std::map< int, char > &),
			ft::map< int, char > &ft, std::map< int, char > &stl);

/*
**			Compare Functions				**
*/

bool	content_compare(ft::map< int, char > &ft, std::map< int, char > &stl);
bool	map_compare(ft::map< int, char > &ft, std::map< int, char > &stl);


#endif