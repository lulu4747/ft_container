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
		ft::vector<int> vec; //default const
		print_attributes(vec);

		std::cout << "try/catch vector.at(rand() %" << LEN << ") 1000 times on empty vector :" << std::endl << std::endl;
		try
		{
			for (int i = 0; i < 1000; i++)
			{
				const int idx = rand() % LEN;
				vec.at(idx);
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
			vec.insert(vec.end(), rand());
		}
		print_attributes(vec);

		std::cout << "vector.reserve(vector.capacity() + 2) :" << std::endl << std::endl;

		vec.reserve(vec.capacity() + 2);
		print_attributes(vec);

		std::cout << "copy constructor and compare :" << std::endl << std::endl;

		ft::vector<int> cpy = vec; // cpy

		print_attributes(vec);
		cmp(vec, cpy); // cmp cpy
	
		std::cout << "copy.clear() and compare :" << std::endl << std::endl;
		cpy.clear();
		print_attributes(vec);
		cmp(vec, cpy); //cmp with empty
	}

	std::cout << "______________________________________" << std::endl << std::endl;
	/* ******** */ // at() swap() empty() capacity() pop_back()...

	{
		std::cout << "default construct 2 vectors :" << std::endl << std::endl;

		ft::vector<int> vec1;
		ft::vector<int> vec2;

		std::cout << "for(int i = 0; i < 125; i++)" << std::endl
			<< "	vec1.insert(vec1.end(), rand()); :" << std::endl << std::endl;

		for(int i = 0; i < 125; i++)
		{
			vec1.insert(vec1.end(), rand());
		}

		print_attributes(vec1);
		print_attributes(vec2);

		std::cout << "vec2.swap(vec1);" << std::endl << std::endl;

		vec2.swap(vec1);

		print_attributes(vec1);
		print_attributes(vec2);

		std::cout << "vec1 = vec2;" << std::endl << std::endl;

		vec1 = vec2;

		print_attributes(vec1);
		print_attributes(vec2);
		cmp(vec1, vec2);

		std::cout << "vec2[i] = rand while i < 25;" << std::endl
			<< "vec2.at(i) = rand while i < 50;" << std::endl << std::endl;

		for(int i =0; i < 25; i++)
		{
			vec2[i] = rand();
		}

		for(int i =25; i < 50; i++)
		{
			vec2.at(i) = rand();
		}

		cmp(vec2, vec1);

		std::cout << "vec2.pop_back() 4 times;" << std::endl << std::endl;

		vec2.pop_back();
		vec2.pop_back();
		vec2.pop_back();
		vec2.pop_back();

		cmp(vec2, vec1);

	}

	std::cout << "______________________________________" << std::endl << std::endl;

	/* ******** */  //fill_constructor pop_back() push_back() resize() cmp()

	{
		std::cout << "range construct (10, rand) 2 vectors :" << std::endl << std::endl;

		ft::vector<int> vec1(10, rand());
		ft::vector<int> vec2(10, rand());

		cmp(vec2, vec1);

		std::cout << "vec2.pop_back();" << std::endl << std::endl;

		vec2.pop_back();
		cmp(vec2, vec1);

		std::cout << "vec2.push_back(rand);" << std::endl << std::endl;

		vec2.push_back(rand());
		cmp(vec2, vec1);

		std::cout << "vec2.push_back(rand) 2 times;" << std::endl << std::endl;

		vec2.push_back(rand());
		vec2.push_back(rand());
		cmp(vec2, vec1);

		size_t n_len = rand() % 100;
		std::cout << "vec2.resize(" << n_len << ", rand);" << std::endl
			<< "vec1.resize(" << n_len << ");"<< std::endl << std::endl;
	
		vec2.resize(n_len, rand());
		vec1.resize(n_len);
	
		cmp(vec2, vec1);
		print_attributes(vec1);
		print_attributes(vec2);
		
	}

	std::cout << "______________________________________" << std::endl << std::endl;
	
	/* ******** */ //range_constructor front() back()

	{
		std::cout << "default construct :" << std::endl << std::endl
			<< "for(int i = 0; i < " << LEN << "; i++)" << std::endl
			<< "	vec1.insert(vec1.end(), rand()); :" << std::endl << std::endl;

		ft::vector<int> vec1;

		for(int i =0; i < LEN; i++)
		{
			vec1.insert(vec1.end(), rand());
		}

		std::cout << "range construct vec2 from vec1.begin() to vec1.begin() + rand_size:" << std::endl << std::endl;

		ft::vector<int> vec2(vec1.begin(), vec1.begin() + (rand_size(vec1)));

		std::cout << "copy construct vec3 from vec1 :" << std::endl << std::endl;

		ft::vector<int> vec3(vec1);

		std::cout << "default construct vec4 :" << std::endl << std::endl;

		ft::vector<int> vec4;

		cmp(vec2, vec1);
		cmp(vec3, vec1);
		cmp(vec3, vec2);
		print_attributes(vec1);
		print_attributes(vec2);
		print_attributes(vec3);
		print_attributes(vec4);

		std::cout << "vec3.assign(vec1.begin(), vec1.begin() + (rand_size(vec1)));" << std::endl << std::endl;
	
		vec3.assign(vec1.begin(), vec1.begin() + (rand_size(vec1)));

		std::cout << "vec4.assign(vec3.size(), rand());" << std::endl << std::endl;

		vec4.assign(vec3.size(), rand());

		cmp(vec3, vec1);
		cmp(vec3, vec2);
		cmp(vec2, vec1);
		print_attributes(vec1);
		print_attributes(vec2);

		std::cout << "erase pos;" << std::endl << std::endl;
	
		if (!vec4.empty())
			vec4.erase(vec4.begin() + rand_size(vec4));

		print_attributes(vec4);

		std::cout << "erase range;" << std::endl << std::endl;

		vec3.erase(vec3.begin(), vec3.begin() + rand_size(vec3));

		print_attributes(vec3);

		std::cout << "insert single;" << std::endl << std::endl;

		vec3.insert(vec3.begin() + rand_size(vec3), rand());
		print_attributes(vec3);

		std::cout << "insert fill;" << std::endl << std::endl;

		vec3.insert(vec3.begin() + (rand() % vec3.size()), rand() % 1000, rand());
		print_attributes(vec3);

		std::cout << "insert range;" << std::endl << std::endl;

		vec3.insert(vec3.end(), vec1.begin(), vec1.begin() + (rand() % vec1.size()));
		print_attributes(vec3);
	
		std::cout << "insert range from self;" << std::endl << std::endl;
		vec3.insert(vec3.end() , vec3.begin(), vec3.end());
		print_attributes(vec3);

		std::cout << "swap vec3 and vec4" << std::endl << std::endl;
		ft::swap(vec3, vec4);
		print_attributes(vec3);
		print_attributes(vec4);
	
		print_it(vec4.rbegin(), vec4.rend());
		
		ft::vector<int>::const_iterator first = vec3.begin();
		ft::vector<int>::const_iterator last = vec3.end();
		print_it(first, last);
	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct with class <FOO> :" << std::endl << std::endl
			<< "for(int i = 0; i < " << LEN << "; i++)" << std::endl
			<< "	vec1.insert(vec1.end(), rand()); :" << std::endl << std::endl;

		ft::vector<Foo> vec1;

		for(int i =0; i < LEN; i++)
		{
			vec1.insert(vec1.end(), rand());
		}

		std::cout << "range construct from vec1;" << std::endl << std::endl;

		ft::vector<Foo> vec2(vec1.begin(), vec1.begin() + (rand_size(vec1)));

		std::cout << "copy construct from vec1;" << std::endl << std::endl;

		ft::vector<Foo> vec3(vec1);

		std::cout << "Default construct;" << std::endl << std::endl;
		ft::vector<Foo> vec4;

		std::cout << "range assign from vec1;" << std::endl << std::endl;

		vec3.assign(vec1.begin(), vec1.begin() + (rand_size(vec1)));

		std::cout << "fill assign;" << std::endl << std::endl;

		vec4.assign(vec3.size(), rand());


		cmp(vec3, vec1);
		cmp(vec3, vec2);
		cmp(vec2, vec1);
		print_attributes(vec1);
		print_attributes(vec2);
		print_attributes(vec3);
		print_attributes(vec4);

		std::cout << "erase pos;" << std::endl << std::endl;

		vec4.erase(vec4.begin() + rand_size(vec4));
		print_attributes(vec4);

		std::cout << "erase range;" << std::endl << std::endl;

		vec3.erase(vec3.begin(), vec3.begin() + rand_size(vec3));
		print_attributes(vec3);

		std::cout << "insert single;" << std::endl << std::endl;

		vec3.insert(vec3.begin() + rand_size(vec3), rand());
		print_attributes(vec3);

		std::cout << "erase fill;" << std::endl << std::endl;

		vec3.insert(vec3.begin() + (rand() % vec3.size()), rand() % 1000, rand());
		print_attributes(vec3);

		std::cout << "insert range;" << std::endl << std::endl;

		vec3.insert(vec3.end(), vec1.begin(), vec1.begin() + (rand() % vec1.size()));
		print_attributes(vec3);

		std::cout << "insert from self;" << std::endl << std::endl;

		vec3.insert(vec3.end() , vec3.begin(), vec3.end());
		print_attributes(vec3);

		std::cout << "swap;" << std::endl << std::endl;
		ft::swap(vec3, vec4);
		print_attributes(vec3);
		print_attributes(vec4);
	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct with class <std::string> :" << std::endl << std::endl
			<< "push_back increasingly 2000 std::string" << std::endl << std::endl;
		ft::vector<std::string> vec1;

		
		std::string str = "A";
		size_t len = rand() % 250;
		for (size_t i = 0; i < len; i++)
		{
			str += static_cast<char>(rand() % 127 + 'A');
			vec1.push_back(str);
		}

		print_attributes(vec1);

		std::cout << "copy construct from vec1;" << std::endl << std::endl;

		ft::vector<std::string> vec2(vec1);

		cmp(vec1, vec2);

		std::cout << "Default construct;" << std::endl << std::endl;

		ft::vector<std::string> vec3;

		std::cout << "push_back random elements from vec2;" << std::endl << std::endl;

		for (size_t i = 0; i < len; i++)
		{
			size_t index = rand() % vec2.size();

			std::cout << index << " | " << vec2.size() << std::endl;
			vec3.push_back(vec2[index]);
		}

		print_attributes(vec3);

		std::cout << "erase random number of random elements from vec2;" << std::endl << std::endl;

		erase_rand_el(vec2, rand_size(vec2));

		print_attributes(vec2);
		cmp(vec1, vec2);

		std::cout << "insert random number of random elements from vec2;" << std::endl << std::endl;

		insert_rand_el(vec2, vec1.size() - vec2.size(), "A");

		cmp(vec1, vec2);
		cmp(vec1, vec3);
		cmp(vec3, vec2);

	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct<int> 2 vectors :" << std::endl << std::endl
			<< "push_back 200 rand() on both" << std::endl << std::endl;

		std::string		begin("begin()");
		std::string		str_it("begin()");
		ft::vector<int>	vec1;
		ft::vector<int>	vec2;
	
		for (int i = 0; i < 200; i++)
		{
			vec1.push_back(std::rand());
			vec2.push_back(std::rand());
		}

		std::cout  << "copy construct from vec1 :" << std::endl << std::endl;

		ft::vector<int>	vec3(vec1);

		std::cout << "//////////////////////////Default iterator//////////////////////////" << std::endl << std::endl
			<< "it = vec1.begin()" << std::endl;

		ft::vector<int>::iterator	it(vec1.begin());

		std::cout << "*it = " << *it << std::endl
			<< "it2 = vec2.begin()" << std::endl;

		ft::vector<int>::iterator	it2(vec2.begin());

		std::cout << "*it2 = " << *it2 << std::endl
			<< "it3 = vec3.begin()" << std::endl;

		ft::vector<int>::iterator	it3(vec3.begin());
		std::cout << "*it3 = " << *it3 << std::endl
			<< "compare (range from it to it + vec1.size() / 2) to (range from it2 to it2 + vec2.size() / 2)" << std::endl;

		cmp_it_range(it, it + vec1.size() / 2, it2, it2 + vec2.size() / 2);
		
		std::cout << "compare (range from it to it + vec1.size() / 2) to (range from it3 to it3 + vec3.size() / 2)" << std::endl;

		cmp_it_range(it, it + vec1.size() / 2, it3, it3 + vec3.size() / 2);
		
		std::cout << "compare (range from it to it + vec1.size() / 2) to (range it + vec1.size() / 2 to vec1.end())" << std::endl;

		cmp_it_range(it, it + vec1.size() / 2, it + vec1.size() / 2, vec1.end());


		std::cout << "----------Arithmetic operators----------" << std::endl
			<< "Mostly using \"operator*()\" to print output" << std::endl
			<< std::endl << str_it << " += " << vec1.size() / 2 << " :			";

		std::cout << *(it += vec1.size() / 2) << std::endl;

		std::cout << str_it << " + " << vec1.size() / 5 << " :			";

		std::cout << *(it + vec1.size() / 5) << std::endl;

		std::cout << str_it << " - " << vec1.size() / 3 << " :			";

		std::cout << *(it - vec1.size() / 3) << std::endl;

		std::cout << str_it << " - vector." << begin << "() :		";

		std::cout << (it - vec1.begin()) << std::endl;

		std::cout << str_it << " -= " << vec1.size() / 4 << " :			";

		std::cout << *(it -= vec1.size() / 4) << std::endl;

		std::cout << str_it << " = vector." << begin << "() :	";

		std::cout << *(it = vec1.begin()) << std::endl;

		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			<< str_it << " == vector." << begin << "() ? :	";

		std::cout << (it == vec1.begin())
			<< str_it << " != vector." << begin << "() ? :	"
				<< (it != vec1.begin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (it <= vec1.begin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (it >= vec1.begin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (it < vec1.begin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (it > vec1.begin()) << std::endl
				<< str_it << "++ == vector." << begin << "() ? :	"
				<< (it++ == vec1.begin()) << std::endl
				<< str_it << " != vector." << begin << "() ? :	"
				<< (it != vec1.begin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (it <= vec1.begin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (it >= vec1.begin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (it < vec1.begin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (it > vec1.begin()) << std::endl
				<< "--" << str_it << " == vector." << begin << "() ? :	"
				<< (--it == vec1.begin()) << std::endl;

		std::cout << std::endl << "----------Access operators----------" << std::endl << std::endl
			<< str_it << "[" << vec1.size() / 5 << "] :			";

		std::cout << (it[vec1.size() / 5]) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "iterator		tmp(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::vector<int>::iterator		tmp(it);

		std::cout << (it++ == tmp) << std::endl;

		std::cout << std::endl << "tmp = " << str_it << ";" << std::endl << str_it << "-- == tmp ? :	";

		tmp = it;

		std::cout << (it-- == tmp) << std::endl;

		std::cout << std::endl << "tmp = " << str_it << ";" << std::endl << "++" << str_it << " == tmp ? :	";

		tmp = it;

		std::cout << (++it == tmp) << std::endl;

		std::cout << std::endl << "tmp = " << str_it << ";" << std::endl << "--" << str_it << " == tmp ? :	";

		tmp = it;

		std::cout << (--it == tmp) << std::endl;


		str_it = "cit";

		std::cout << "//////////////////////////Const iterator//////////////////////////" << std::endl << std::endl
			<< "cit = vec1.begin()" << std::endl;

		ft::vector<int>::const_iterator	cit(vec1.begin());

		std::cout << "*cit = " << *cit << std::endl
			<< "cit2 = vec2.begin()" << std::endl;

		ft::vector<int>::const_iterator	cit2(vec2.begin());

		std::cout << "*cit2 = " << *cit2 << std::endl
			<< "cit3 = vec3.begin()" << std::endl;

		ft::vector<int>::const_iterator	cit3(vec3.begin());
		std::cout << "*cit3 = " << *cit3 << std::endl
			<< "compare (range from cit to cit + vec1.size() / 2) to (range from cit2 to cit2 + vec2.size() / 2)" << std::endl;

		cmp_it_range(cit, cit + vec1.size() / 2, cit2, cit2 + vec2.size() / 2);
		
		std::cout << "compare (range from cit to cit + vec1.size() / 2) to (range from cit3 to cit3 + vec3.size() / 2)" << std::endl;

		cmp_it_range(cit, cit + vec1.size() / 2, cit3, cit3 + vec3.size() / 2);
		
		std::cout << "compare (range from cit to cit + vec1.size() / 2) to (range cit + vec1.size() / 2 to vec1.end())" << std::endl;

		cmp_it_range(cit, cit + vec1.size() / 2, cit + vec1.size() / 2, vec1.end());


		std::cout << "----------Arcithmetic operators----------" << std::endl
			<< "Mostly using \"operator*()\" to print output" << std::endl
			<< std::endl << str_it << " += " << vec1.size() / 2 << " :			";

		std::cout << *(cit += vec1.size() / 2) << std::endl;

		std::cout << str_it << " + " << vec1.size() / 5 << " :			";

		std::cout << *(cit + vec1.size() / 5) << std::endl;

		std::cout << str_it << " - " << vec1.size() / 3 << " :			";

		std::cout << *(cit - vec1.size() / 3) << std::endl;

		std::cout << str_it << " - vector." << begin << "() :		";

		std::cout << (cit - vec1.begin()) << std::endl;

		std::cout << str_it << " -= " << vec1.size() / 4 << " :			";

		std::cout << *(cit -= vec1.size() / 4) << std::endl;

		std::cout << str_it << " = vector." << begin << "() :	";

		std::cout << *(cit = vec1.begin()) << std::endl;

		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			<< str_it << " == vector." << begin << "() ? :	";

		std::cout << (cit == vec1.begin())
			<< str_it << " != vector." << begin << "() ? :	"
				<< (cit != vec1.begin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (cit <= vec1.begin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (cit >= vec1.begin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (cit < vec1.begin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (cit > vec1.begin()) << std::endl
				<< str_it << "++ == vector." << begin << "() ? :	"
				<< (cit++ == vec1.begin()) << std::endl
				<< str_it << " != vector." << begin << "() ? :	"
				<< (cit != vec1.begin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (cit <= vec1.begin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (cit >= vec1.begin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (cit < vec1.begin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (cit > vec1.begin()) << std::endl
				<< "--" << str_it << " == vector." << begin << "() ? :	"
				<< (--cit == vec1.begin()) << std::endl;

		std::cout << std::endl << "----------Access operators----------" << std::endl << std::endl
			<< str_it << "[" << vec1.size() / 5 << "] :			";

		std::cout << (cit[vec1.size() / 5]) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "const_iterator		tmp2(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::vector<int>::const_iterator		tmp2(cit);

		std::cout << (cit++ == tmp2) << std::endl;

		std::cout << std::endl << "tmp2 = " << str_it << ";" << std::endl << str_it << "-- == tmp2 ? :	";

		tmp2 = cit;

		std::cout << (cit-- == tmp2) << std::endl;

		std::cout << std::endl << "tmp2 = " << str_it << ";" << std::endl << "++" << str_it << " == tmp2 ? :	";

		tmp2 = cit;

		std::cout << (++cit == tmp2) << std::endl;

		std::cout << std::endl << "tmp2 = " << str_it << ";" << std::endl << "--" << str_it << " == tmp2 ? :	";

		tmp2 = cit;

		std::cout << (--cit == tmp2) << std::endl;
		
		str_it = "rit";
		begin = "rbegin";

		std::cout << "//////////////////////////reverse iterator//////////////////////////" << std::endl << std::endl
			<< "rit = vec1.rbegin()" << std::endl;

		ft::vector<int>::reverse_iterator	rit(vec1.rbegin());

		std::cout << "*rit = " << *rit << std::endl
			<< "rit2 = vec2.rbegin()" << std::endl;

		ft::vector<int>::reverse_iterator	rit2(vec2.rbegin());

		std::cout << "*rit2 = " << *rit2 << std::endl
			<< "rit3 = vec3.rbegin()" << std::endl;

		ft::vector<int>::reverse_iterator	rit3(vec3.rbegin());
		std::cout << "*rit3 = " << *rit3 << std::endl
			<< "compare (range from rit to rit + vec1.size() / 2) to (range from rit2 to rit2 + vec2.size() / 2)" << std::endl;

		cmp_it_range(rit, rit + vec1.size() / 2, rit2, rit2 + vec2.size() / 2);
		
		std::cout << "compare (range from rit to rit + vec1.size() / 2) to (range from rit3 to rit3 + vec3.size() / 2)" << std::endl;

		cmp_it_range(rit, rit + vec1.size() / 2, rit3, rit3 + vec3.size() / 2);
		
		std::cout << "compare (range from rit to rit + vec1.size() / 2) to (range rit + vec1.size() / 2 to vec1.rend())" << std::endl;

		cmp_it_range(rit, rit + vec1.size() / 2, rit + vec1.size() / 2, vec1.rend());


		std::cout << "----------Arrithmetic operators----------" << std::endl
			<< "Mostly using \"operator*()\" to print output" << std::endl
			<< std::endl << str_it << " += " << vec1.size() / 2 << " :			";

		std::cout << *(rit += vec1.size() / 2) << std::endl;

		std::cout << str_it << " + " << vec1.size() / 5 << " :			";

		std::cout << *(rit + vec1.size() / 5) << std::endl;

		std::cout << str_it << " - " << vec1.size() / 3 << " :			";

		std::cout << *(rit - vec1.size() / 3) << std::endl;

		std::cout << str_it << " - vector." << begin << "() :		";

		std::cout << (rit - vec1.rbegin()) << std::endl;

		std::cout << str_it << " -= " << vec1.size() / 4 << " :			";

		std::cout << *(rit -= vec1.size() / 4) << std::endl;

		std::cout << str_it << " = vector." << begin << "() :	";

		std::cout << *(rit = vec1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			<< str_it << " == vector." << begin << "() ? :	";

		std::cout << (rit == vec1.rbegin())
			<< str_it << " != vector." << begin << "() ? :	"
				<< (rit != vec1.rbegin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (rit <= vec1.rbegin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (rit >= vec1.rbegin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (rit < vec1.rbegin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (rit > vec1.rbegin()) << std::endl
				<< str_it << "++ == vector." << begin << "() ? :	"
				<< (rit++ == vec1.rbegin()) << std::endl
				<< str_it << " != vector." << begin << "() ? :	"
				<< (rit != vec1.rbegin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (rit <= vec1.rbegin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (rit >= vec1.rbegin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (rit < vec1.rbegin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (rit > vec1.rbegin()) << std::endl
				<< "--" << str_it << " == vector." << begin << "() ? :	"
				<< (--rit == vec1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Access operators----------" << std::endl << std::endl
			<< str_it << "[" << vec1.size() / 5 << "] :			";

		std::cout << (rit[vec1.size() / 5]) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "reverse_iterator		tmp3(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::vector<int>::reverse_iterator		tmp3(rit);

		std::cout << (rit++ == tmp3) << std::endl;

		std::cout << std::endl << "tmp3 = " << str_it << ";" << std::endl << str_it << "-- == tmp3 ? :	";

		tmp3 = rit;

		std::cout << (rit-- == tmp3) << std::endl;

		std::cout << std::endl << "tmp3 = " << str_it << ";" << std::endl << "++" << str_it << " == tmp3 ? :	";

		tmp3 = rit;

		std::cout << (++rit == tmp3) << std::endl;

		std::cout << std::endl << "tmp3 = " << str_it << ";" << std::endl << "--" << str_it << " == tmp3 ? :	";

		tmp3 = rit;

		std::cout << (--rit == tmp3) << std::endl;
		
		str_it = "crit";

		std::cout << "//////////////////////////const reverse iterator//////////////////////////" << std::endl << std::endl
			<< "crit = vec1.rbegin()" << std::endl;

		ft::vector<int>::const_reverse_iterator	crit(vec1.rbegin());

		std::cout << "*crit = " << *crit << std::endl
			<< "crit2 = vec2.rbegin()" << std::endl;

		ft::vector<int>::const_reverse_iterator	crit2(vec2.rbegin());

		std::cout << "*crit2 = " << *crit2 << std::endl
			<< "crit3 = vec3.rbegin()" << std::endl;

		ft::vector<int>::const_reverse_iterator	crit3(vec3.rbegin());
		std::cout << "*crit3 = " << *crit3 << std::endl
			<< "compare (range from crit to crit + vec1.size() / 2) to (range from crit2 to crit2 + vec2.size() / 2)" << std::endl;

		cmp_it_range(crit, crit + vec1.size() / 2, crit2, crit2 + vec2.size() / 2);
		
		std::cout << "compare (range from crit to crit + vec1.size() / 2) to (range from crit3 to crit3 + vec3.size() / 2)" << std::endl;

		cmp_it_range(crit, crit + vec1.size() / 2, crit3, crit3 + vec3.size() / 2);
		
		std::cout << "compare (range from crit to crit + vec1.size() / 2) to (range crit + vec1.size() / 2 to vec1.rend())" << std::endl;

		cmp_it_range(crit, crit + vec1.size() / 2, crit + vec1.size() / 2, vec1.rend());


		std::cout << "----------Arcrithmetic operators----------" << std::endl
			<< "Mostly using \"operator*()\" to print output" << std::endl
			<< std::endl << str_it << " += " << vec1.size() / 2 << " :			";

		std::cout << *(crit += vec1.size() / 2) << std::endl;

		std::cout << str_it << " + " << vec1.size() / 5 << " :			";

		std::cout << *(crit + vec1.size() / 5) << std::endl;

		std::cout << str_it << " - " << vec1.size() / 3 << " :			";

		std::cout << *(crit - vec1.size() / 3) << std::endl;

		std::cout << str_it << " - vector." << begin << "() :		";

		std::cout << (crit - vec1.rbegin()) << std::endl;

		std::cout << str_it << " -= " << vec1.size() / 4 << " :			";

		std::cout << *(crit -= vec1.size() / 4) << std::endl;

		std::cout << str_it << " = vector." << begin << "() :	";

		std::cout << *(crit = vec1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			<< str_it << " == vector." << begin << "() ? :	";

		std::cout << (crit == vec1.rbegin())
			<< str_it << " != vector." << begin << "() ? :	"
				<< (crit != vec1.rbegin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (crit <= vec1.rbegin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (crit >= vec1.rbegin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (crit < vec1.rbegin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (crit > vec1.rbegin()) << std::endl
				<< str_it << "++ == vector." << begin << "() ? :	"
				<< (crit++ == vec1.rbegin()) << std::endl
				<< str_it << " != vector." << begin << "() ? :	"
				<< (crit != vec1.rbegin()) << std::endl
				<< str_it << " <= vector." << begin << "() ? :	"
				<< (crit <= vec1.rbegin()) << std::endl
				<< str_it << " >= vector." << begin << "() ? :	"
				<< (crit >= vec1.rbegin()) << std::endl
				<< str_it << " < vector." << begin << "() ? :		"
				<< (crit < vec1.rbegin()) << std::endl
				<< str_it << " > vector." << begin << "() ? :		"
				<< (crit > vec1.rbegin()) << std::endl
				<< "--" << str_it << " == vector." << begin << "() ? :	"
				<< (--crit == vec1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Access operators----------" << std::endl << std::endl
			<< str_it << "[" << vec1.size() / 5 << "] :			";

		std::cout << (crit[vec1.size() / 5]) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "const_reverse_iterator		tmp4(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::vector<int>::const_reverse_iterator		tmp4(crit);

		std::cout << (crit++ == tmp4) << std::endl;

		std::cout << std::endl << "tmp4 = " << str_it << ";" << std::endl << str_it << "-- == tmp4 ? :	";

		tmp4 = crit;

		std::cout << (crit-- == tmp4) << std::endl;

		std::cout << std::endl << "tmp4 = " << str_it << ";" << std::endl << "++" << str_it << " == tmp4 ? :	";

		tmp4 = crit;

		std::cout << (++crit == tmp4) << std::endl;

		std::cout << std::endl << "tmp4 = " << str_it << ";" << std::endl << "--" << str_it << " == tmp4 ? :	";

		tmp4 = crit;

		std::cout << (--crit == tmp4) << std::endl;

	}

	std::cout << "_______________________________________________" << std::endl;

	{
	std::cout << "Relational operator test" << std::endl << std::endl
		<< "vector1 = randomly filled vector of size " << 200 << ";" << std::endl
		<< "vector2 = vector1 copy;" << std::endl
		<< "vector3 = other random vec of size " << 200 << ";" << std::endl
		<< "vector4 = other random vec of size " << 2000 << ";" << std::endl
		<< "vector5 = other random vec of size " << 20 << ";" << std::endl << std::endl;

	ft::vector<int>		vct1;
	ft::vector<int>		vct2;
	ft::vector<int>		vct3;
	ft::vector<int>		vct4;
	ft::vector<int>		vct5;
	int					val;

	for (int i = 0; i < 200; i++)
	{
		val = std::rand();
		vct1.push_back(val);
		vct2.push_back(val);
	}
	for (int i = 0; i < 200; i++)
	{
		val = std::rand();
	}
	for (int i = 0; i < 2000; i++)
	{
		val = std::rand();
	}
	for (int i = 0; i < 20; i++)
	{
		val = std::rand();
		vct5.push_back(val);
	}

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"==\" " << std::endl << std::endl
		<< "vector1 == vector2 ? :		";

	std::cout << std::boolalpha << (vct1 == vct2) << std::endl;
	

	std::cout << "vector1 == vector3 ? :		";

	std::cout << std::boolalpha << (vct1 == vct3) << std::endl;
	

	std::cout << "vector1 == vector4 ? :		";

	std::cout << std::boolalpha << (vct1 == vct4) << std::endl;
	

	std::cout << "vector1 == vector5 ? :		";

	std::cout << std::boolalpha << (vct1 == vct5) << std::endl;
	

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"!=\" " << std::endl << std::endl
		<< "vector1 != vector2 ? :		";

	std::cout << std::boolalpha << (vct1 != vct2) << std::endl;


	std::cout << "vector1 != vector3 ? :		";

	std::cout << std::boolalpha << (vct1 != vct3) << std::endl;


	std::cout << "vector1 != vector4 ? :		";

	std::cout << std::boolalpha << (vct1 != vct4) << std::endl;


	std::cout << "vector1 != vector5 ? :		";

	std::cout << std::boolalpha << (vct1 != vct5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<\" " << std::endl << std::endl
		<< "vector1 < vector2 ? :			";

	std::cout << std::boolalpha << (vct1 < vct2)  << std::endl;

	std::cout << "vector1 < vector3 ? :			";

	std::cout << std::boolalpha << (vct1 < vct3)  << std::endl;

	std::cout << "vector1 < vector4 ? :			";

	std::cout << std::boolalpha << (vct1 < vct4)  << std::endl;

	std::cout << "vector1 < vector5 ? :			";

	std::cout << std::boolalpha << (vct1 < vct5)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<=\" " << std::endl << std::endl
		<< "vector1 <= vector2 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct2) << std::endl;


	std::cout << "vector1 <= vector3 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct3) << std::endl;


	std::cout << "vector1 <= vector4 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct4) << std::endl;


	std::cout << "vector1 <= vector5 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">\" " << std::endl << std::endl
		<< "vector1 > vector2 ? :			";

	std::cout << std::boolalpha << (vct1 > vct2)  << std::endl;

	std::cout << "vector1 > vector3 ? :			";

	std::cout << std::boolalpha << (vct1 > vct3)  << std::endl;

	std::cout << "vector1 > vector4 ? :			";

	std::cout << std::boolalpha << (vct1 > vct4)  << std::endl;

	std::cout << "vector1 > vector5 ? :			";

	std::cout << std::boolalpha << (vct1 > vct5)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">=\" " << std::endl << std::endl
		<< "vector1 >= vector2 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct2) << std::endl;


	std::cout << "vector1 >= vector3 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct3) << std::endl;


	std::cout << "vector1 >= vector4 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct4) << std::endl;


	std::cout << "vector1 >= vector5 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct5) << std::endl;

	}

	return 0;
}
