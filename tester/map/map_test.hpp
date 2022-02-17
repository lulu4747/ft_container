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
**			Compare Functions				**
*/

bool	content_compare(ft::map< int, char > &ft, std::map< int, char > &stl);
bool	map_compare(ft::map< int, char > &ft, std::map< int, char > &stl);


#endif