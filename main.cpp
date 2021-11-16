#include <iostream>
#include <vector>
#include "ft.hpp"
#include "Map.hpp"
#include "Stack.hpp"
#include "Vector.hpp"

int main(void){

	ft::Vector<int>	test;
	std::vector<int> classic;
/*
	std::cout << "test : " << test.size() << std::endl << "classic : " << classic.size() << std::endl << std::endl;
	test.assign(4, 4);
	ft::Vector<int>::iterator	it = test.begin();
	ft::Vector<int>::iterator	ite = test.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	classic.assign(10, 98);
	std::cout << "test : " << test.size() << std::endl << "classic : " << classic.size() << std::endl << std::endl;
	std::vector<int>::iterator	cit = classic.begin();
	std::vector<int>::iterator	cite = classic.end();
	while (cit != cite)
	{
		std::cout << *cit << std::endl;
		cit++;
	}
	test.assign(classic.begin(), classic.end());
	it = test.begin();
	ite = test.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}*/
	for (int i = 0; i < 10; i++)
	{
		test.push_back(i);
		classic.push_back(i);
	}
	std::cout << "test : " << test.size() << "	/	" << test.capacity() << std::endl
		<< "classic : " << classic.size() << "	/	" << classic.capacity() << std::endl << std::endl;
	test.erase(test.begin(), test.begin() + 4);
	classic.erase(classic.begin(), classic.begin() + 4);
	std::cout << "test : " << test.size() << "	/	" << test.capacity() << std::endl
		<< "classic : " << classic.size() << "	/	" << classic.capacity() << std::endl << std::endl;
	std::vector<int>::iterator	cit = classic.begin();
	ft::Vector<int>::iterator	it = test.begin();
	while (it < test.end())
	{
		std::cout << "test : " << *it << std::endl << "classic : " << *cit << std::endl << std::endl;
		cit++;
		it++;
	}
	it = test.begin();
	cit = classic.begin();
	test.pop_back();
	classic.pop_back();
	std::cout << std::endl << "test : " << test.size() << "	/	" << test.capacity() << std::endl
		<< "classic : " << classic.size() << "	/	" << classic.capacity() << std::endl << std::endl;
	while (it < test.end())
	{
		std::cout << "test : " << *it << std::endl << "classic : " << *cit << std::endl << std::endl;
		cit++;
		it++;
	}
	test.clear();
	classic.clear();
	std::cout << std::endl << "test : " << test.size() << "	/	" << test.capacity() << std::endl
		<< "classic : " << classic.size() << "	/	" << classic.capacity() << std::endl << std::endl;
	test.insert(test.begin(), 1);
	classic.insert(classic.begin(), 1);


	classic.assign(5, 47);
	test.insert(test.begin(), classic.begin(), classic.end());													// need to correct
	std::cout << std::endl << "test : " << test.size() << "	/	" << test.capacity() << std::endl
		<< "classic : " << classic.size() << "	/	" << classic.capacity() << std::endl << std::endl;
	it = test.begin();
	while (it < test.end())
		std::cout << *it++ << std::endl;
	test.assign(5, 47);																							// capacity() should'nt change
	std::cout << std::endl << "test : " << test.size() << "	/	" << test.capacity() << std::endl
		<< "classic : " << classic.size() << "	/	" << classic.capacity() << std::endl << std::endl;
	it = test.begin();
	while (it < test.end())
		std::cout << *it++ << std::endl;
	return 0;
}
