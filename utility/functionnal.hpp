#ifndef LESS_HPP
# define LESS_HPP

namespace	ft
{
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
}

#endif
