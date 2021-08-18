#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"
# include "ft.hpp"

namespace	ft
{

	template < class T, class Container = Vector<T> >
	class Stack : public Container{

	public:

	//	Member Types :

		typedef Container	container_type;

		typedef	typename Container::value_type		value_type;
		typedef	typename Container::size_type		size_type;
		typedef	typename Container::reference		reference;
		typedef	typename Container::const_reference const_reference;

	//	Member Functions :

		explicit Stack( const Container& cont = Container() ):c(cont){}
		~Stack();

		Stack &	operator=( Stack const & other){
			if (this != &other)
				this->c = other.c;
			return *this;
		}
	
		//	Element access

		reference	top( void ){
			return	c.back();
		}
		const_reference	top( void ) const{
			return	c.back();
		}

		//	Capacity

		bool	empty( void ) const{
			return	c.empty();
		}

		size_type	size( void ) const{
			return	c.size();
		}

		//	Modifiers

		void	push(value_type const & value){
			c.push_back(value);
		}

		void	pop( void ){
			c.pop_back();
		}

	protected:
	
		container_type	c;

	};

	//	Non-member functions

	template<class T, class Container>
	bool operator==(Stack<T,Container> const & lhs, Stack<T,Container> const & rhs ){
		return lhs.c == rhs.c;
	}

	template<class T, class Container>
	bool operator!=(Stack<T,Container> const & lhs, Stack<T,Container> const & rhs ){
		return lhs.c != rhs.c;
	}

	template<class T, class Container>
	bool operator<(Stack<T,Container> const & lhs, Stack<T,Container> const & rhs ){
		return lhs.c < rhs.c;
	}

	template<class T, class Container>
	bool operator<=(Stack<T,Container> const & lhs, Stack<T,Container> const & rhs ){
		return lhs.c <= rhs.c;
	}

	template<class T, class Container>
	bool operator>(Stack<T,Container> const & lhs, Stack<T,Container> const & rhs ){
		return lhs.c > rhs.c;
	}

	template<class T, class Container>
	bool operator>=(Stack<T,Container> const & lhs, Stack<T,Container> const & rhs ){
		return lhs.c >= rhs.c;
	}

}

#endif