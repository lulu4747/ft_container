#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "../utility/algorithm.hpp"
# include "../utility/functionnal.hpp"
# include "../utility/pair.hpp"
# include "../utility/type_trait.hpp"
# include "../utility/BST_tree/rb_tree.hpp"
# include "../utility/Iterators/Reverse_Iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
			class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map
	{

	public:

		typedef				Key													key_type;
		typedef				T													mapped_type;
		typedef				pair< const key_type, mapped_type >					value_type;
		typedef				std::size_t											size_type;
		typedef				std::ptrdiff_t										difference_type;
		typedef				Compare												key_compare;
		typedef				Alloc												allocator_type;

		typedef	typename	allocator_type::reference							reference;
		typedef	typename 	allocator_type::const_reference						const_reference;
		typedef	typename	allocator_type::pointer								pointer;
		typedef	typename	allocator_type::const_pointer						const_pointer;

		typedef	typename	rb_tree<value_type, key_compare>::iterator			iterator;
		typedef	typename	rb_tree<value_type, key_compare>::const_iterator	const_iterator;
		typedef				Reverse_Iterator<iterator>							reverse_iterator;
		typedef				Reverse_Iterator<const_iterator>					const_reverse_iterator;

		class value_compare : binary_function< value_type, value_type, bool >
		{
			friend class map< key_type, value_type, key_compare, allocator_type >;

			protected:

				key_compare	comp;

				value_compare(key_compare c): comp(c){}
			
			public:

				bool	operator()(const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};

		explicit map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
			:_data(comp, alloc),
			_comp(comp),
			_alloc(alloc)
		{}

		template< class InputIt >
		map(InputIt first, InputIt last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
				typename enable_if<!is_integral<InputIt>::value, InputIt >::type* = NULL)
			: _data(comp, alloc), _comp(comp), _alloc(alloc)
		{

			if(!(is_input_iterator_tagged< typename iterator_traits<InputIt>::iterator_category >::value))
				throw std::invalid_argument("In ft::Map(InputIt first, InputIt last), InputIt class is'nt at least InputIterator tagged");

			insert(first, last);
		}

		map( map const & src)
			:_data(src.key_comp(), src.get_allocator()),
			_comp(src.key_comp()),
			_alloc(src.get_allocator())
		{
			*this = src;
		}

		~map(){}

		map&	operator=(map const & rhs)
		{
			if (this != &rhs)
			{
				clear();
				insert(rhs.begin(), rhs.end());
			}
			return *this;
		}

		//	Iterators

		iterator	begin()
		{
			return iterator(_data.begin());
		}

		const_iterator	begin() const
		{
			return const_iterator(_data.begin());
		}

		iterator	end()
		{
			return iterator(_data.end());
		}

		const_iterator	end() const
		{
			return const_iterator(_data.end());
		}

		reverse_iterator	rbegin()
		{
			return reverse_iterator(_data.end());
		}

		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(_data.end());
		}

		reverse_iterator	rend()
		{
			return reverse_iterator(_data.begin());;
		}

		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(_data.begin());;
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
			return _data.max_size();
		}

		//	Element access

		mapped_type&	operator[](const key_type& k)
		{
			return _data[k];
		}

		//	Modifiers

		pair< iterator, bool > insert (const value_type& val)
		{
			iterator	first(find(val.first));
			bool		second(false);
			pointer		new_val(NULL);

			if (first == _data.end())
			{
				new_val = _alloc.allocate(1);
				_alloc.construct(new_val, make_pair(val.first, val.second));
				second = _data.insert(new_val);
				first = find(val.first);
			}
			return (make_pair(first, second));
		}

		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return insert(*val).first;
		}

		template <class InputIt>
		void insert (InputIt first, InputIt last)
		{

			if(!(is_input_iterator_tagged< typename iterator_traits<InputIt>::iterator_category >::value))
				throw std::invalid_argument("In ft::map::insert(InputIt first, InputIt last), InputIt class is'nt at least InputIterator tagged");

			while (first != last)
				insert(*(first++));

			return ;
		}

		void	erase(iterator position)
		{
			_data.erase(position);
		}

		void	erase(iterator first, iterator last)
		{
			while (first != last)
				_data.erase(first++);
		}

		size_type	erase(const key_type& k)
		{
			iterator	position(find(k));

			if (position == end())
				return 0;
			_data.erase(position);
			return 1;
		}

		void	swap(map& x)
		{
			_data.swap(x._data);
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

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}


		//	Operation

		iterator	find(const key_type& k)
		{
			return (_data.find(k));
		}

		const_iterator	find(const key_type& k) const
		{
			return (_data.find(k));
		}

		size_type	count(const key_type& k) const
		{
			return _data.count(k);
		}

		iterator	lower_bound(const key_type& k)
		{
			return _data.lower_bound(k);
		}

		const_iterator	lower_bound(const key_type& k) const
		{
			return _data.lower_bound(k);
		}

		iterator	upper_bound(const key_type& k)
		{
			return _data.upper_bound(k);
		}

		const_iterator	upper_bound(const key_type& k) const
		{
			return _data.upper_bound(k);
		}

		pair< iterator, iterator >	equal_range(const key_type& k)
		{
			return _data.equal_range(k);
		}

		pair< const_iterator, const_iterator >	equal_range(const key_type& k) const
		{
			return _data.equal_range(k);
		}

		// Allocator

		allocator_type	get_allocator() const
		{
			return _alloc;
		}

	private:

		rb_tree<value_type, key_compare, allocator_type>	_data;
		key_compare											_comp;
		allocator_type										_alloc;

	};

		
	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		typename map<Key,T,Compare,Alloc>::const_iterator	first1 = lhs.begin();
		typename map<Key,T,Compare,Alloc>::const_iterator	first2 = rhs.begin();

		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

}


#endif
