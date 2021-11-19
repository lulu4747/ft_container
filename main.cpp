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
	std::vector<int>	std_c;
	std::vector<int>	lst(80, 5);

	output(ft_c, std_c);
	content(ft_c, std_c);

	std_c.assign(lst.begin(), lst.end());
	ft_c.assign(lst.begin(), lst.end());

	output(ft_c, std_c);
	content(ft_c, std_c);

	lst.assign(7, 4);

	std_c.insert(std_c.begin(), lst.begin(), lst.end());
	ft_c.insert(ft_c.begin(), lst.begin(), lst.end());

	output(ft_c, std_c);
	content(ft_c, std_c);

	std_c.insert(std_c.begin() + 15, lst.begin(), lst.end());
	ft_c.insert(ft_c.begin() + 15, lst.begin(), lst.end());

	output(ft_c, std_c);
	content(ft_c, std_c);

	std_c.erase(std_c.begin());
	ft_c.erase(ft_c.begin());

	output(ft_c, std_c);
	content(ft_c, std_c);

	std_c.erase(std_c.begin() + 4, std_c.begin() + 11);
	ft_c.erase(ft_c.begin() + 4, ft_c.begin() + 11);

	output(ft_c, std_c);
	content(ft_c, std_c);

	std_c.clear();
	ft_c.clear();

	for (size_t i = 0; i < ft_c.capacity(); i++)
	{
		std_c.push_back(i);
		ft_c.push_back(i);
	}

	output(ft_c, std_c);
	content(ft_c, std_c);

	std_c.erase(std_c.begin() + 2);
	ft_c.erase(ft_c.begin() + 2);

	output(ft_c, std_c);
	content(ft_c, std_c);

	std_c.erase(std_c.begin() + 2, std_c.begin() + 85);
	ft_c.erase(ft_c.begin() + 2, ft_c.begin() + 85);

	output(ft_c, std_c);
	content(ft_c, std_c);

	
	//std_c.erase(std_c.begin() + 2, std_c.begin() + 85);
	ft_c.erase(ft_c.begin() + 2, ft_c.begin() + 85);

	output(ft_c, std_c);
	content(ft_c, std_c);			//this test segfault on original vector and doesn't on mine

	return 0;
}
