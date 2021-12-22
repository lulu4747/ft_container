#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "../utility/functionnal.hpp"
# include "../utility/pair.hpp"
# include "../utility/type_trait.hpp"
# include "../utility/BST_tree/rb_tree.hpp"
# include "../utility/Iterators/Reverse_Iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
			class Alloc = std::allocator< ft::pair<const Key, T> > >
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
		typedef				Reverse_Iterator<iterator>							reverse_iterator;
		typedef				Reverse_Iterator<const_iterator>					const_reverse_iterator;

		class value_compare : binary_function< value_type, value_type, bool >
		{
			friend class Map< key_type, value_type, key_compare, allocator_type >;

			protected:

				key_compare	comp;

				value_compare(key_compare c): comp(c){}
			
			public:

				bool	operator()(const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};

		void	tmp() const
		{
			_data.tmp();
		}
		//	Canon

		explicit Map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
			:_data(comp, alloc),
			_comp(comp),
			_alloc(alloc)
		{}

		template< class InputIt >
		Map(InputIt first, InputIt last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
				typename enable_if<!is_integral<InputIt>::value, InputIt >::type* = NULL)
			: Map< key_type, mapped_type, key_compare , allocator_type >(comp, alloc)
		{

			if(!(is_input_iterator_tagged< typename iterator_traits<InputIt>::iterator_category >::value))
				throw std::invalid_argument("In ft::Map(InputIt first, InputIt last), InputIt class is'nt at least ft::InputIterator tagged");

			pointer	new_val;

			while (first != last)
			{
				new_val = &(*first);
				_data.insert(*new_val);
				new_val = NULL;
				first++;
			}
		}

		Map( Map const & src)
			:_data(src.key_comp(), src.get_allocator()),
			_comp(src.key_comp()),
			_alloc(src.get_allocator())
		{
			*this = src;
		}

		~Map()
		{
			_data.clear();
		}

		Map&	operator=(Map const & rhs)
		{
			if (this != &rhs)
			{
				_comp = rhs.key_comp();
				_alloc = rhs.get_allocator();
				_data = rhs._data;
			}
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
			reverse_iterator rit(--(_data.end()));

			return rit;
		}

		const_reverse_iterator	rbegin() const
		{
			const_reverse_iterator rit(--(_data.end()));

			return rit;
		}

		reverse_iterator	rend()
		{
			reverse_iterator rit((_data.end()));

			return rit;
		}

		const_reverse_iterator	rend() const
		{
			const_reverse_iterator rit((_data.end()));

			return rit;
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
				_alloc.construct(new_val, val);
				_data.insert(new_val);
				first = find(val.first);
				second = true;
			}
			return (make_pair(first, second));
		}

		iterator insert (iterator position, const value_type& val)
		{
			iterator	it(_data.find(val.first));
			pointer		new_val(NULL);

			if (it == _data.end())
			{
				new_val = _alloc.allocate(1);
				_alloc.construct(new_val, val);
				_data.insert(new_val);
				it = find(val.first);
			}
			static_cast<void>(position);
			return it;
		}

		template <class InputIt>
		void insert (InputIt first, InputIt last)
		{

			if(!(is_input_iterator_tagged< typename iterator_traits<InputIt>::iterator_category >::value))
				throw std::invalid_argument("In ft::Map::insert(InputIt first, InputIt last), InputIt class is'nt at least ft::InputIterator tagged");

			while (first != last)
			{
				_data[*first.first] = *first.second;
				first++;
			}
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

		const_iterator	lower_bound(const key_type& k) const;

		iterator	upper_bound(const key_type& k);

		const_iterator	upper_bound(const key_type& k) const;

		pair< iterator, iterator >	equal_range(const key_type& k);
		pair< const_iterator, const_iterator >	equal_range(const key_type& k) const;

		// Allocator

		allocator_type	get_allocator() const
		{
			return _alloc;
		}

	protected:

	private:

		rb_tree<value_type, key_compare, allocator_type>	_data;
		key_compare											_comp;
		allocator_type										_alloc;

	};
}


#endif
