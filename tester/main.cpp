#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "../ft_containers/Map.hpp"
#include "../ft_containers/Stack.hpp"
#include "../ft_containers/Vector.hpp"

/*
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
*/
int main(void){
/*
	ft::Vector<int>		ft_c;
	ft::Vector<int>		ft_lst(7, 78);
	std::vector<int>	std_c;
	std::vector<int>	std_lst(7, 78);


	for (int i = 1; i < 6; i++)
	{
		ft_c.push_back(i);
		std_c.push_back(i);
	}

	output(ft_c, std_c);
	content(ft_c, std_c);

	for (int i = 1; i < 6; i++)
	{
		ft_c.pop_back();
		std_c.pop_back();
	}

	output(ft_c, std_c);
	content(ft_c, std_c);

	for (int i = 1; i < 6; i++)
	{
		ft_c.push_back(i);
		std_c.push_back(i);
	}

	output(ft_c, std_c);
	content(ft_c, std_c);

	ft_c.clear();
	std_c.clear();

	output(ft_c, std_c);
	content(ft_c, std_c);

	ft_c.assign(5, 5);
	std_c.assign(5, 5);

	output(ft_c, std_c);
	content(ft_c, std_c);

	ft_c.push_back(8);
	std_c.push_back(8);

	//ft_c.insert(ft_c.end() + 2, ft_lst.begin(), ft_lst.end());		//	undefined behaviour mais
	//std_c.insert(std_c.end() + 2, std_lst.begin(), std_lst.end());	//	OSKOUUUUUUR

	output(ft_c, std_c);
	content(ft_c, std_c);

	return 0;*/
/*
  std::map<char,int> first;
  std::map<char,int> second;

  first['x']=8;
  first['y']=16;
  first['z']=32;

  second=first;                // second now contains 3 ints
  first=std::map<char,int>();  // and first is now empty

  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';
*/

	ft::Map<char,int> first;
	ft::Map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;                // second now contains 3 ints
	first=ft::Map<char,int>();  // and first is now empty

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';
	return 0;
}
