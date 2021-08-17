#ifndef FT_HPP
# define FT_HPP

namespace	ft
{

	// Containers

	class Map;
	class Stack;
	template < class T, class Alloc = std::allocator<T> >
	class Vector;

	// std::pair reimplementation

		// std::pair Member elements
	template < class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	first;
		second_type	second;

		pair(void){};
		pair(T1 k, T2 t):first(k), second(t){};
		pair(pair<T1, T2> const & src){*this = src;}
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
