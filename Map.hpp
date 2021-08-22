#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "ft.hpp"
# include "Iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
			class Alloc = std::allocator< ft::pair<const Key,T> > >
	class Map{

	public:
		Map(void);
		~Map();


	private:
		/* data */

	};
}


#endif