#ifndef STACK_TEST_HPP
# define STACK_TEST_HPP

# include "../tester.hpp"
# include "../../ft_containers/stack.hpp"

/*
**		Compare Functions	**
*/

template< class T, class Container = ft::vector<T> >
class Mutant_FT_Stack : public ft::stack<T, Container>
{

	public:

		Mutant_FT_Stack(void): ft::stack<T, Container>(){}
		Mutant_FT_Stack(ft::stack<T, Container> const & src): ft::stack<T, Container>(src){}
		Mutant_FT_Stack(Mutant_FT_Stack const & src): ft::stack<T, Container>(src){}
		virtual ~Mutant_FT_Stack(void){}
		Mutant_FT_Stack &	operator=(Mutant_FT_Stack const & rhs){return *this = ft::stack<T, Container>::operator=(rhs);}

		typedef	typename Container::iterator				iterator;
		typedef	typename Container::const_iterator			const_iterator;
		typedef	typename Container::reverse_iterator		reverse_iterator;
		typedef	typename Container::const_reverse_iterator	const_reverse_iterator;

		iterator				begin(void){return ft::stack<T, Container>::c.begin();}
		const_iterator			begin(void) const{return ft::stack<T, Container>::c.begin();}

		iterator				end(void){return ft::stack<T, Container>::c.end();}
		const_iterator			end(void) const{return ft::stack<T, Container>::c.end();}

		reverse_iterator		rbegin(void){return ft::stack<T, Container>::c.rbegin();}
		const_reverse_iterator	rbegin(void) const{return ft::stack<T, Container>::c.rbegin();}

		reverse_iterator		rend(void){return ft::stack<T, Container>::c.rend();}
		const_reverse_iterator	rend(void) const{return ft::stack<T, Container>::c.rend();}

};

template< class T, class Container = std::deque<T> >
class Mutant_STL_Stack : public std::stack<T, Container>
{

	public:

		Mutant_STL_Stack(void): std::stack<T, Container>(){}
		Mutant_STL_Stack(std::stack<T, Container> const & src): std::stack<T, Container>(src){}
		Mutant_STL_Stack(Mutant_STL_Stack const & src): std::stack<T, Container>(src){}
		virtual ~Mutant_STL_Stack(void){}
		Mutant_STL_Stack &	operator=(Mutant_STL_Stack const & rhs){return *this = std::stack<T, Container>::operator=(rhs);}

		typedef	typename Container::iterator				iterator;
		typedef	typename Container::const_iterator			const_iterator;
		typedef	typename Container::reverse_iterator		reverse_iterator;
		typedef	typename Container::const_reverse_iterator	const_reverse_iterator;

		iterator				begin(void){return std::stack<T, Container>::c.begin();}
		const_iterator			begin(void) const{return std::stack<T, Container>::c.begin();}

		iterator				end(void){return std::stack<T, Container>::c.end();}
		const_iterator			end(void) const{return std::stack<T, Container>::c.end();}

		reverse_iterator		rbegin(void){return std::stack<T, Container>::c.rbegin();}
		const_reverse_iterator	rbegin(void) const{return std::stack<T, Container>::c.rbegin();}

		reverse_iterator		rend(void){return std::stack<T, Container>::c.rend();}
		const_reverse_iterator	rend(void) const{return std::stack<T, Container>::c.rend();}

};

bool	content_compare(ft::stack<int> ft, std::stack<int> stl);
bool	stack_compare(ft::stack<int> ft, std::stack<int> stl);

#endif