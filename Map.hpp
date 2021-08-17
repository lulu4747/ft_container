#ifndef MAP_HPP
# define MAP_HPP

# include "ft.hpp"

template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >
class ft::Map{

public:
	Map(void);
	~Map();


private:
	/* data */

};

#endif