#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "ft.hpp"
# include "rb_tree.hpp"
# include "Iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
			class Alloc = std::allocator< ft::pair<const Key,T> > >
	class Map
	{

	public:

		typedef				Key													key_type;
		typedef				T													mapped_type;
		typedef				pair< const key_type, mapped_type >					value_type;
		typedef				std::size_t											size_type;			// a type = to unsigned difference_type
		typedef				std::ptrdiff_t										difference_type;	//temporary, will be iterator_traits<iterator>::difference_type
		typedef				Compare												key_compare;
		typedef				Alloc												allocator_type;

		typedef	typename	allocator_type::reference							reference;
		typedef	typename 	allocator_type::const_reference						const_reference;
		typedef	typename	allocator_type::pointer								pointer;
		typedef	typename	allocator_type::const_pointer						const_pointer;

		typedef	typename	rb_tree<value_type, key_compare>::iterator			iterator;
		typedef	typename	rb_tree<value_type, key_compare>::const_iterator	const_iterator;
		typedef				ReverseIterator<iterator>							reverse_iterator;
		typedef				ReverseIterator<const_iterator>						const_reverse_iterator;

		//	Canon

		explicit Map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
			:_data(rb_tree< value_type, key_compare, key_type, node< value_type >, allocator_type, std::allocator< node< value_type > > >()),
			_comp(comp),
			_alloc(alloc)
		{}

		template< class InputIt >
		Map(InputIt first, InputIt last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: Map< key_type, mapped_type, key_compare , allocator_type >(comp, alloc),
			_data(_data.copy(first, last))	// NIY, will be whith Map Iterators
		{}

		Map( Map const & src)
			:Map< key_type, mapped_type, key_compare , allocator_type >(src.key_comp(), src.get_allocator())
		{
			*this = src;
		}

		~Map()
		{	_data.clear();}

		Map&	operator=(Map const & rhs)
		{
			if (this != &rhs)
				_data = rhs._data;
			return *this;
		}

		//	Iterators

		iterator	begin()
		{
			return _data.begin();
		}

		const_iterator	begin() const
		{
			return _data.begin();
		}

		iterator	end()
		{
			return _data.end();
		}

		const_iterator	end() const
		{
			return _data.end();
		}

		reverse_iterator	rbegin()
		{
			return _data.rbegin();
		}

		const_reverse_iterator	rbegin() const
		{
			return _data.rbegin();
		}

		reverse_iterator	rend()
		{
			return _data.rend();
		}

		const_reverse_iterator	rend() const
		{
			return _data.rend();
		}

		//	Capacity

		bool	empty() const
		{
			return _data.empty();
		}

		size_type size() const
		{
			return _data.size();
		}

		size_type max_size() const
		{
			return _data.max_size();	//	NIY
		}

		//	Element access

		mapped_type&	operator[](const key_type& k)
		{
			return _data[k];	// NIY
		}

		//	Modifiers

		pair<iterator,bool> insert (const value_type& val)
		{
			iterator	first(find(val.first));
			bool		second(false);
			pointer		new_val(NULL);

			if (first == end())
			{
				_alloc.construct(new_val, val);
				_data.insert(*new_val);
				first = find(val.first);
				second = true;
			}
			return (make_pair(first, second));
		}

//		iterator insert (iterator position, const value_type& val);
//		template <class InputIterator>
//		void insert (InputIterator first, InputIterator last);

		void	erase (iterator position)
		{
			_data.erase(position);
		}

		void	erase (iterator first, iterator last)
		{
			while (first != last)
			{
				erase(first);
				first++;
			}
		}

		size_type	erase (const key_type& k)
		{
			iterator	position(find(k));

			if (position == end())
				return 0;
			erase(position);
			return 1;
		}

		void	swap(Map& x)
		{
			Map	tmp(x);

			x._data = this->_data;
			this->_data = tmp._data;
			tmp.~Map();
		}

		void	clear()
		{
			_data.clear();
		}

		//	Observer

		key_compare key_comp() const
		{
			return _comp;
		}
/*
		value_compare value_comp() const;	// define value_compare
*/

		//	Operation

		iterator	find (const key_type& k)
		{
			return (_data.find(k));	//NIY
		}

		const_iterator	find (const key_type& k) const
		{
			return (_data.find(k));	//NIY
		}

		size_type	count (const key_type& k) const
		{
			if (_data.find(k) != end())		//NIY
				return 1;
			return 0;
		}

		iterator	lower_bound (const key_type& k);

		const_iterator	lower_bound (const key_type& k) const;

		pair<iterator,iterator>	equal_range (const key_type& k);
		pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;

		// Allocator

		allocator_type	get_allocator() const
		{
			return _alloc;
		}

	protected:

	private:

		rb_tree<value_type, key_compare>	_data;
		key_compare							_comp;
		allocator_type						_alloc;

	};
}


#endif
