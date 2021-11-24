#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "ft.hpp"
//# include "rb_tree.hpp"
# include "Iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
			class Alloc = std::allocator< ft::pair<const Key,T> > >
	class Map
	{

	public:

		typedef				Key												key_type;
		typedef				T												mapped_type;
		typedef				pair<const Key, T>								value_type;
		typedef				std::size_t										size_type;
		typedef				std::ptrdiff_t									difference_type;
		typedef				Compare											key_compare;
		typedef				Alloc											allocator_type;
		typedef				value_type&										reference;
		typedef	const 		value_type&										const_reference;

		typedef	typename	allocator_type::pointer							pointer;
		typedef	typename	allocator_type::const_pointer					const_pointer;
		
//		typedef				BidirectionalIterator<value_type>				iterator;
//		typedef				BidirectionalIterator<const value_type>			const_iterator;
//		typedef				ReverseIterator<iterator>						reverse_iterator;
//		typedef				ReverseIterator<const_iterator>					const_reverse_iterator;

		Map();
		//explicit	Map(void);

		template< class InputIt >
		Map( InputIt first, InputIt last,
     		const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() );
		~Map();


	private:

		pointer			_data;
		allocator_type	_alloc;

	};
}


#endif