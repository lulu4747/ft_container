#include <iostream>
#include "ft.hpp"
#include "Map.hpp"
#include "Stack.hpp"
#include "Vector.hpp"

int main(void){

	ft::Vector<int>	test;

	test.assign(4, 4);
	ft::VectorIterator<int>	it = test.begin();
	ft::VectorIterator<int>	ite = test.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	return 0;
}
