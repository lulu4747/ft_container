#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace	ft
{

	template < class T, class Container = vector<T> >
	class stack
	{

	public:

	//	Member Types :

		typedef Container	container_type;

		typedef	typename Container::value_type		value_type;
		typedef	typename Container::size_type		size_type;
		typedef	typename Container::reference		reference;
		typedef	typename Container::const_reference const_reference;

	//	Member Functions :

		explicit stack( const container_type& cont = container_type() )
			:c(cont)
		{}

		virtual ~stack()
		{}

		stack &	operator=( stack const & other)
		{
			if (this != &other)
				this->c = other.c;
			return *this;
		}
	
		//	Element access

		reference	top( void )
		{
			return	c.back();
		}

		const_reference	top( void ) const
		{
			return	c.back();
		}

		//	Capacity

		bool	empty( void ) const
		{
			return	c.empty();
		}

		size_type	size( void ) const
		{
			return	c.size();
		}

		//	Modifiers

		void	push(value_type const & value)
		{
			c.push_back(value);
		}

		void	pop( void )
		{
			c.pop_back();
		}

		template < class T_, class Container_ >
			friend bool operator== (const ft::stack<T_, Container_>& lhs, const ft::stack<T_, Container_>& rhs);

		template < class T_, class Container_ >
			friend bool operator!= (const ft::stack<T_, Container_>& lhs, const ft::stack<T_, Container_>& rhs);
			
		template < class T_, class Container_ >
			friend bool operator< (const ft::stack<T_, Container_>& lhs, const ft::stack<T_, Container_>& rhs);

		template < class T_, class Container_ >
			friend bool operator<= (const ft::stack<T_, Container_>& lhs, const ft::stack<T_, Container_>& rhs);

		template < class T_, class Container_ >
			friend bool operator> (const ft::stack<T_, Container_>& lhs, const ft::stack<T_, Container_>& rhs);

		template < class T_, class Container_ >
			friend bool operator>= (const ft::stack<T_, Container_>& lhs, const ft::stack<T_, Container_>& rhs);

	protected:
	
		container_type	c;

	};

	//	Non-member functions

	template<class T, class Container>
	bool operator==(stack<T,Container> const & lhs, stack<T,Container> const & rhs )
	{
		return lhs.c == rhs.c;
	}

	template<class T, class Container>
	bool operator!=(stack<T,Container> const & lhs, stack<T,Container> const & rhs )
	{
		return lhs.c != rhs.c;
	}

	template<class T, class Container>
	bool operator<(stack<T,Container> const & lhs, stack<T,Container> const & rhs )
	{
		return lhs.c < rhs.c;
	}

	template<class T, class Container>
	bool operator<=(stack<T,Container> const & lhs, stack<T,Container> const & rhs )
	{
		return lhs.c <= rhs.c;
	}

	template<class T, class Container>
	bool operator>(stack<T,Container> const & lhs, stack<T,Container> const & rhs )
	{
		return lhs.c > rhs.c;
	}

	template<class T, class Container>
	bool operator>=(stack<T,Container> const & lhs, stack<T,Container> const & rhs )
	{
		return lhs.c >= rhs.c;
	}

}

#endif
