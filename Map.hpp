#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "ft.hpp"
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

		typedef	typename	Allocator::pointer								pointer;
		typedef	typename	Allocator::const_pointer						const_pointer;
		
		typedef				BidirectionalIterator<value_type>				iterator;
		typedef				LegacyBidirectionalIterator<const value_type>	const_iterator;
		typedef				ReverseIterator<iterator>						reverse_iterator;
		typedef				ReverseIterator<const_iterator>					const_reverse_iterator;

		Map()
		explicit	Map(void);

		template< class InputIt >
		Map( InputIt first, InputIt last,
     		const Compare& comp = Compare(), const Allocator& alloc = Allocator() );
		~Map();


	private:
		 _data

	};
}


#endif