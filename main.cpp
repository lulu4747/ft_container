#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "ft.hpp"
#include "Map.hpp"
#include "Stack.hpp"
#include "Vector.hpp"

template < class FT, class STD >
void	output(const FT & ft_c, const STD & std_c)
{
	std::cout << "____________________________________________" << std::endl << std::endl
		<< "ft	:	" << ft_c.size() << "	/	" << ft_c.capacity() << std::endl
		<< "std	:	" << std_c.size() << "	/	" << std_c.capacity() << std::endl
		<< "____________________________________________" << std::endl << std::endl;
}

template < class C >
void	inside(C c)
{
	typename C::iterator it(c.begin());

	while (it != c.end())
	{
		std::cout << " |" << *(it++);
	}
	std::cout << std::endl;
}

template < class FT, class STD >
void	content(const FT & ft_c, const STD & std_c)
{
	std::cout << "____________________________________________" << std::endl << std::endl
		<< "ft	:	" << std::endl;
	inside(ft_c);
	std::cout << "____________________________________________" << std::endl << std::endl
		<< "std	:	" << std::endl;
	inside(std_c);
	std::cout << "____________________________________________" << std::endl << std::endl;
}

int main(void){

	ft::Vector<int>		ft_c;
	ft::Vector<int>		ft_lst(6, 78);
	std::vector<int>	std_c;
	std::vector<int>	std_lst(6, 78);

	ft_c.assign(5, 5);
	std_c.assign(5, 5);

	output(ft_c, std_c);
	content(ft_c, std_c);
//	output(ft_lst, std_lst);
//	content(ft_lst, std_lst);

	ft_c.push_back(8);		//original does'nt augment capacity * 2 ??
	std_c.push_back(8);

	ft_c.insert(ft_c.begin() + 2, ft_lst.begin(), ft_lst.end());
	std_c.insert(std_c.begin() + 2, std_lst.begin(), std_lst.end());

	output(ft_c, std_c);		//a value is overwritten, need to go back at it with fresh mind
	content(ft_c, std_c);

	return 0;
}
