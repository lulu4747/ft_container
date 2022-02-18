#include <iostream>
#include <string>
#include "vector_test.hpp"
#include "../Foo.hpp"

int main()
{
	srand(SEED);
	/* ********* */ // reserve() cmp() ope=() insert(rand_len) at() exception
	std::cout << "---------------------VECTOR---------------------" << std::endl << std::endl
		<< "default constructor :" << std::endl << std::endl;
	{	
		ft::vector<int> vct; //default const
		print_attributes(vct);

		std::cout << "try/catch vector.at(rand() %" << LEN << ") 1000 times on empty vector :" << std::endl << std::endl;
		try
		{
			for (int i = 0; i < 1000; i++)
			{
				const int idx = rand() % LEN;
				vct.at(idx);
				std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
			}
		}
		catch(const std::exception& e)
		{
			std::cout << "OK" << std::endl << std::endl;
		}

		std::cout << "vector.insert(vector.end(), rand()) " << LEN << " times :" << std::endl << std::endl;

		for(int i = 0; i < LEN; i++)
		{
			vct.insert(vct.end(), rand());
		}
		print_attributes(vct);

		std::cout << "vector.reserve(vector.capacity() + 2) :" << std::endl << std::endl;

		vct.reserve(vct.capacity() + 2);
		print_attributes(vct);

		std::cout << "copy constructor and compare :" << std::endl << std::endl;

		ft::vector<int> cpy = vct; // cpy

		print_attributes(vct);
		cmp(vct, cpy); // cmp cpy
	
		std::cout << "copy.clear() and compare :" << std::endl << std::endl;
		cpy.clear();
		print_attributes(vct);
		cmp(vct, cpy); //cmp with empty
	}

	std::cout << "______________________________________" << std::endl << std::endl;
	/* ******** */ // at() swap() empty() capacity() pop_back()...

	{
		std::cout << "default construct 2 vectors :" << std::endl << std::endl;

		ft::vector<int> vct1;
		ft::vector<int> vct2;

		std::cout << "for(int i = 0; i < 125; i++)" << std::endl
			<< "	vct1.insert(vct1.end(), rand()); :" << std::endl << std::endl;

		for(int i = 0; i < 125; i++)
		{
			vct1.insert(vct1.end(), rand());
		}

		print_attributes(vct1);
		print_attributes(vct2);

		std::cout << "vct2.swap(vct1);" << std::endl << std::endl;

		vct2.swap(vct1);

		print_attributes(vct1);
		print_attributes(vct2);

		std::cout << "vct1 = vct2;" << std::endl << std::endl;

		vct1 = vct2;

		print_attributes(vct1);
		print_attributes(vct2);
		cmp(vct1, vct2);

		std::cout << "vct2[i] = rand while i < 25;" << std::endl
			<< "vct2.at(i) = rand while i < 50;" << std::endl << std::endl;

		for(int i =0; i < 25; i++)
		{
			vct2[i] = rand();
		}

		for(int i =25; i < 50; i++)
		{
			vct2.at(i) = rand();
		}

		cmp(vct2, vct1);

		std::cout << "vct2.pop_back() 4 times;" << std::endl << std::endl;

		vct2.pop_back();
		vct2.pop_back();
		vct2.pop_back();
		vct2.pop_back();

		cmp(vct2, vct1);

	}

	std::cout << "______________________________________" << std::endl << std::endl;

	/* ******** */  //fill_constructor pop_back() push_back() resize() cmp()

	{
		std::cout << "range construct (10, rand) 2 vectors :" << std::endl << std::endl;

		ft::vector<int> vct1(10, rand());
		ft::vector<int> vct2(10, rand());

		cmp(vct2, vct1);

		std::cout << "vct2.pop_back();" << std::endl << std::endl;

		vct2.pop_back();
		cmp(vct2, vct1);

		std::cout << "vct2.push_back(rand);" << std::endl << std::endl;

		vct2.push_back(rand());
		cmp(vct2, vct1);

		std::cout << "vct2.push_back(rand) 2 times;" << std::endl << std::endl;

		vct2.push_back(rand());
		vct2.push_back(rand());
		cmp(vct2, vct1);

		size_t n_len = rand() % 100;
		std::cout << "vct2.resize(" << n_len << ", rand);" << std::endl
			<< "vct1.resize(" << n_len << ");"<< std::endl << std::endl;
	
		vct2.resize(n_len, rand());
		vct1.resize(n_len);
	
		cmp(vct2, vct1);
		print_attributes(vct1);
		print_attributes(vct2);
		
	}

	std::cout << "______________________________________" << std::endl << std::endl;
	
	/* ******** */ //range_constructor front() back()

	{
		std::cout << "default construct :" << std::endl << std::endl
			<< "for(int i = 0; i < " << LEN << "; i++)" << std::endl
			<< "	vct1.insert(vct1.end(), rand()); :" << std::endl << std::endl;

		ft::vector<int> vct1;

		for(int i =0; i < LEN; i++)
		{
			vct1.insert(vct1.end(), rand());
		}

		std::cout << "range construct vct2 from vct1.begin() to vct1.begin() + rand_size:" << std::endl << std::endl;

		ft::vector<int> vct2(vct1.begin(), vct1.begin() + (rand_size(vct1)));

		std::cout << "copy construct vct3 from vct1 :" << std::endl << std::endl;

		ft::vector<int> vct3(vct1);

		std::cout << "default construct vct4 :" << std::endl << std::endl;

		ft::vector<int> vct4;

		cmp(vct2, vct1);
		cmp(vct3, vct1);
		cmp(vct3, vct2);
		print_attributes(vct1);
		print_attributes(vct2);
		print_attributes(vct3);
		print_attributes(vct4);

		std::cout << "vct3.assign(vct1.begin(), vct1.begin() + (rand_size(vct1)));" << std::endl << std::endl;
	
		vct3.assign(vct1.begin(), vct1.begin() + (rand_size(vct1)));

		std::cout << "vct4.assign(vct3.size(), rand());" << std::endl << std::endl;

		vct4.assign(vct3.size(), rand());

		cmp(vct3, vct1);
		cmp(vct3, vct2);
		cmp(vct2, vct1);
		print_attributes(vct1);
		print_attributes(vct2);

		std::cout << "erase pos;" << std::endl << std::endl;
	
		if (!vct4.empty())
			vct4.erase(vct4.begin() + rand_size(vct4));

		print_attributes(vct4);

		std::cout << "erase range;" << std::endl << std::endl;

		vct3.erase(vct3.begin(), vct3.begin() + rand_size(vct3));

		print_attributes(vct3);

		std::cout << "insert single;" << std::endl << std::endl;

		vct3.insert(vct3.begin() + rand_size(vct3), rand());
		print_attributes(vct3);

		std::cout << "insert fill;" << std::endl << std::endl;

		vct3.insert(vct3.begin() + (rand() % vct3.size()), rand() % 1000, rand());
		print_attributes(vct3);

		std::cout << "insert range;" << std::endl << std::endl;

		vct3.insert(vct3.end(), vct1.begin(), vct1.begin() + (rand() % vct1.size()));
		print_attributes(vct3);
	
		std::cout << "insert range from self;" << std::endl << std::endl;
		vct3.insert(vct3.end() , vct3.begin(), vct3.end());
		print_attributes(vct3);

		std::cout << "swap vec3 and vec4" << std::endl << std::endl;
		ft::swap(vct3, vct4);
		print_attributes(vct3);
		print_attributes(vct4);
	
		print_it(vct4.rbegin(), vct4.rend());
		
		ft::vector<int>::const_iterator first = vct3.begin();
		ft::vector<int>::const_iterator last = vct3.end();
		print_it(first, last);
	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct with class <FOO> :" << std::endl << std::endl
			<< "for(int i = 0; i < " << LEN << "; i++)" << std::endl
			<< "	vct1.insert(vct1.end(), rand()); :" << std::endl << std::endl;

		ft::vector<Foo> vct1;

		for(int i =0; i < LEN; i++)
		{
			vct1.insert(vct1.end(), rand());
		}

		std::cout << "range construct from vct1;" << std::endl << std::endl;

		ft::vector<Foo> vct2(vct1.begin(), vct1.begin() + (rand_size(vct1)));

		std::cout << "copy construct from vct1;" << std::endl << std::endl;

		ft::vector<Foo> vct3(vct1);

		std::cout << "Default construct;" << std::endl << std::endl;
		ft::vector<Foo> vct4;

		std::cout << "range assign from vct1;" << std::endl << std::endl;

		vct3.assign(vct1.begin(), vct1.begin() + (rand_size(vct1)));

		std::cout << "fill assign;" << std::endl << std::endl;

		vct4.assign(vct3.size(), rand());


		cmp(vct3, vct1);
		cmp(vct3, vct2);
		cmp(vct2, vct1);
		print_attributes(vct1);
		print_attributes(vct2);
		print_attributes(vct3);
		print_attributes(vct4);

		std::cout << "erase pos;" << std::endl << std::endl;

		vct4.erase(vct4.begin() + rand_size(vct4));
		print_attributes(vct4);

		std::cout << "erase range;" << std::endl << std::endl;

		vct3.erase(vct3.begin(), vct3.begin() + rand_size(vct3));
		print_attributes(vct3);

		std::cout << "insert single;" << std::endl << std::endl;

		vct3.insert(vct3.begin() + rand_size(vct3), rand());
		print_attributes(vct3);

		std::cout << "erase fill;" << std::endl << std::endl;

		vct3.insert(vct3.begin() + (rand() % vct3.size()), rand() % 1000, rand());
		print_attributes(vct3);

		std::cout << "insert range;" << std::endl << std::endl;

		vct3.insert(vct3.end(), vct1.begin(), vct1.begin() + (rand() % vct1.size()));
		print_attributes(vct3);

		std::cout << "insert from self;" << std::endl << std::endl;

		vct3.insert(vct3.end() , vct3.begin(), vct3.end());
		print_attributes(vct3);

		std::cout << "swap;" << std::endl << std::endl;
		ft::swap(vct3, vct4);
		print_attributes(vct3);
		print_attributes(vct4);
	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct with class <std::string> :" << std::endl << std::endl
			<< "push_back increasingly large std::string" << std::endl << std::endl;
		ft::vector<std::string> vct1;

		
		std::string str = "A";
		size_t len = rand() % 250;
		for (size_t i = 0; i < len; i++)
		{
			str += static_cast<char>(rand() % 127 + 'A');
			vct1.push_back(str);
		}

		print_attributes(vct1);

		std::cout << "copy construct from vct1;" << std::endl << std::endl;

		ft::vector<std::string> vct2(vct1);

		cmp(vct1, vct2);

		std::cout << "Default construct;" << std::endl << std::endl;

		ft::vector<std::string> vct3;

		std::cout << "push_back random elements from vct2;" << std::endl << std::endl;

		for (size_t i = 0; i < len; i++)
		{
			size_t index = rand() % vct2.size();

			std::cout << index << " | " << vct2.size() << std::endl;
			vct3.push_back(vct2[index]);
		}

		print_attributes(vct3);

		std::cout << "erase random number of random elements from vct2;" << std::endl << std::endl;

		erase_rand_el(vct2, rand_size(vct2));

		print_attributes(vct2);
		cmp(vct1, vct2);

		std::cout << "insert random number of random elements from vct2;" << std::endl << std::endl;

		insert_rand_el(vct2, vct1.size() - vct2.size(), "A");

		cmp(vct1, vct2);
		cmp(vct1, vct3);
		cmp(vct3, vct2);

	}
/*
	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << std::endl << "#######################################" << std::endl
			<< "iterators operators test" << std::endl
			<< "Crescent values filled vector from 0 to " << 500 << std::endl << std::endl
			<< "normal iterator :" << std::endl
			<< "it(vector.begin());" << std::endl << std::endl;

		ft::vector<int>		vec;
		std::string			str("it");
		for (int i = 0; i < 500; i++)
			vec.push_back(i);

		ft::vector<int>::iterator				it(vec.begin());

		op_test(vec, it, str);
		
		std::cout << std::endl << "constant iterator :" << std::endl
			<< "cit(vector.begin());" << std::endl << std::endl;

		ft::vector<int>::const_iterator			cit(vec.begin());
		str = "cit";

		op_test(vec, cit, str);
		
		std::cout << std::endl << "reverse iterator :" << std::endl
			<< "rit(vector.rbegin());" << std::endl << std::endl;

		ft::vector<int>::reverse_iterator		rit(vec.rbegin());
		str = "rit";

		op_test(vec, rit, str);
		
		std::cout << std::endl << "const reverse iterator :" << std::endl
			<< "crit(vector.rbegin());" << std::endl << std::endl;

		ft::vector<int>::const_reverse_iterator		crit(vec.rbegin());
		str = "crit";

		op_test(vec, crit, str);
	}

*/
	return 0;
}
