#ifndef FT_HPP
# define FT_HPP

namespace	ft
{

	// less template for Map

	template < class T >
	struct less
	{
		typedef	bool	result_type;
		typedef	T		first_argument_type;
		typedef	T		second_argument_type;

		bool operator()( T const & lhs, T const & rhs ) const
		{
			return lhs < rhs;
		}
	};

	// std::pair reimplementation

		// std::pair Member elements
	template < class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	first;
		second_type	second;

		pair(void)
		:
			first(),
			second()
		{}

		pair(T1 const & x, T2 const & y)
		:
			first(x),
			second(y)
		{}

		template< class U1, class U2 >
		pair( const pair<U1, U2>& p )
		:
			first(p.first),
			second(p.second)
		{}

		pair & operator=(pair<T1, T2> const & rhs)
		{
			if (this != &rhs)
			{
				this->first = rhs.first;
				this->second = rhs.second;
			}
			return *this;
		}
	};

		// std::pair Non-Member elements

			// std::pair Non-Member Function
	template < class T1, class T2>
	pair<T1, T2>	make_pair(T1 k, T2 d){
		return pair<T1, T2>(k, d);}

			// std::pair lexicographical comparison operators
	template < class T1, class T2>
	bool	operator==(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs){
		return (lhs.first == rhs.first && lhs.second == rhs.second);}

	template < class T1, class T2>
	bool	operator!=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs){
		return (lhs.first != rhs.first || lhs.second != rhs.second);}

	template < class T1, class T2>
	bool	operator<(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs){
		return (lhs.first == rhs.first && lhs.second < rhs.second);}

	template < class T1, class T2>
	bool	operator<=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{	return (lhs.first == rhs.first && lhs.second <= rhs.second);	}

	template < class T1, class T2>
	bool	operator>(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{	return (lhs.first == rhs.first && lhs.second > rhs.second);	}

	template < class T1, class T2>
	bool	operator>=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{	return (lhs.first == rhs.first && lhs.second >= rhs.second);	}

}

#endif
