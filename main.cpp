#include <iostream>
#include <vector>
#include "ft.hpp"
#include "Map.hpp"
#include "Stack.hpp"
#include "Vector.hpp"

int main(void){

	ft::Vector<int>	test;
	std::vector<int> classic;

	std::cout << "test : " << test.size() << std::endl << "classic : " << classic.size() << std::endl << std::endl;
	test.assign(4, 4);
	ft::Vector<int>::iterator	it = test.begin();
	ft::Vector<int>::iterator	ite = test.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << std::endl;
	classic.assign(4, 4);
	std::cout << "test : " << test.size() << std::endl << "classic : " << classic.size() << std::endl << std::endl;
	std::vector<int>::iterator	cit = classic.begin();
	std::vector<int>::iterator	cite = classic.end();
	while (cit != cite)
	{
		std::cout << *cit << std::endl;
		cit++;
	}
	return 0;
}
