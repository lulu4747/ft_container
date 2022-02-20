#include <iostream>
#include <string>
#include <stdlib.h>
#include "set_test.hpp"
#include "../tester/Foo.hpp"

int main(int argc, char **argv)
{
	int		seed;
	size_t	len;

	if (argc != 3)
	{
		std::cout << "Provide seed and len" << std::endl;
		return 1;
	}

	seed = atoi(argv[1]);
	len = atoi(argv[2]);

	srand(seed);

	{
		ft::set<int> myset;
		ft::set<int> myset2;
		for( size_t i = 0; i < len; i++)
		{
			myset.insert(rand());
			myset2.insert(rand());
		}
		cmp(myset, myset2);
		cmp(myset2, myset);
		printSize(myset);
		printSize(myset2);

		erase_key(myset2);
		erase_key(myset);

		for (size_t i =0; i < 10; i++)
			test_bound(myset, rand());

		cmp(myset, myset2);
		cmp(myset2, myset);
		printSize(myset);
		printSize(myset2);

		ft::set<int> clear_set;

		myset.swap(clear_set); //mymy is clear

		printSize(myset);

		clear_set.clear();
		myset.clear(); //clear clear set

		printSize(myset);
		printSize(clear_set);

	}


	{
		ft::set<Foo> myset;
		ft::set<Foo> myset2;
		for( size_t i = 0; i < len; i++)
		{
			myset.insert(rand());
			myset2.insert(rand());
		}
		cmp(myset, myset2);
		cmp(myset2, myset);
		printSize(myset);
		printSize(myset2);

		erase_key(myset2);
		erase_key(myset);

		for (size_t i =0; i < 10; i++)
			test_bound(myset, rand());

		cmp(myset, myset2);
		cmp(myset2, myset);
		printSize(myset);
		printSize(myset2);

		ft::set<Foo> clear_set;

		myset.swap(clear_set); //mymy is clear

		printSize(myset);

		clear_set.clear();
		myset.clear(); //clear clear set

		printSize(myset);
		printSize(clear_set);

	}

	{
		ft::set<char> myset;
		ft::vector<char> letter;

		for (char i = 'a'; i != 'z' + 1; i++)
			letter.push_back(i);
		

		for(ft::vector<char>::iterator it = letter.begin(); it != letter.end(); it++)
			myset.insert(*it);

		ft::set<char> myset2;

		//myset2.insert(myset.begin(), myset.end());
		myset2 = myset;

		for (size_t i =0; i < 5; i++)
			test_bound(myset, (char)rand());
		cmp(myset, myset2);
		printSize(myset2);

		//erase_key(myset2);
		erase_key(myset, 155);

		cmp(myset, myset2);
		printSize(myset, false);

	}

	//iterator costile
	{
		ft::vector<int> vct;

		for (int i = 0; i != 100; i++)
			vct.push_back(rand());
	

		ft::set<int> myset(vct.begin(), vct.end());


		ft::set<int>::iterator a; //default
		
		a = myset.begin(); //operator=
		
		ft::set<int>::iterator b(a++); //copy

		std::cout << "b == a " << (b == a) << std::endl;
		std::cout << "b != a " << (b != a) << std::endl;

		std::cout << *b << std::endl; //

		++b;
		b++;

		std::cout << (*b++) << std::endl; 
		std::cout << *b << std::endl;

		--b;
		b--;
		std::cout << "b == a " << (*b-- == *a) << std::endl;

		std::cout << *b << std::endl;


		ft::set<int>::const_iterator ca;

		ca = a;

		ft::set<int>::const_iterator cb(b);

		std::cout << *cb << std::endl;
		
	}

		std::cout << "default constructor :" << std::endl << std::endl;
	{	
		ft::set<int> st; //default const
		print_attributes(st);

		std::cout << "set.insert(set.end(), rand()) " << 2000 << " times :" << std::endl << std::endl;

		for(int i = 0; i < 2000; i++)
		{
			st.insert(st.end(), rand());
		}
		print_attributes(st);

		std::cout << "copy constructor and costare :" << std::endl << std::endl;

		ft::set<int> cpy = st; // cpy

		print_attributes(st);
		cmp(st, cpy); // cmp cpy
	
		std::cout << "copy.clear() and costare :" << std::endl << std::endl;
		cpy.clear();
		print_attributes(st);
		cmp(st, cpy); //cmp with empty
	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct 2 sets :" << std::endl << std::endl;

		ft::set<int> st1;
		ft::set<int> st2;

		std::cout << "for(int i = 0; i < 125; i++)" << std::endl
			<< "	st1.insert(st1.end(), rand()); :" << std::endl << std::endl;

		for(int i = 0; i < 125; i++)
		{
			st1.insert(st1.end(), rand());
		}

		print_attributes(st1);
		print_attributes(st2);

		std::cout << "st2.swap(st1);" << std::endl << std::endl;

		st2.swap(st1);

		print_attributes(st1);
		print_attributes(st2);

		std::cout << "st1 = st2;" << std::endl << std::endl;

		st1 = st2;

		print_attributes(st1);
		print_attributes(st2);
		cmp(st1, st2);

	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct :" << std::endl << std::endl
			<< "for(int i = 0; i < " << 2000 << "; i++)" << std::endl
			<< "	st1.insert(st1.end(), rand()); :" << std::endl << std::endl;

		ft::set<int> st1;

		for(int i =0; i < 2000; i++)
		{
			st1.insert(st1.end(), rand());
		}

		std::cout << "range construct st2 from st1.begin() to st1.end()" << std::endl << std::endl;

		ft::set<int> st2(st1.begin(), st1.end());

		std::cout << "copy construct st3 from st1 :" << std::endl << std::endl;

		ft::set<int> st3(st1);

		std::cout << "default construct st4 :" << std::endl << std::endl;

		ft::set<int> st4;

		cmp(st2, st1);
		cmp(st3, st1);
		cmp(st3, st2);
		print_attributes(st1);
		print_attributes(st2);
		print_attributes(st3);
		print_attributes(st4);

		std::cout << "st4.insert(st3.size(), rand());" << std::endl << std::endl;

		st4.insert(st3.begin(), rand());

		cmp(st3, st1);
		cmp(st3, st2);
		cmp(st2, st1);
		print_attributes(st1);
		print_attributes(st2);

		std::cout << "erase pos;" << std::endl << std::endl;
	
		if (!st4.empty())
			st4.erase(st4.begin());

		std::cout << "swap st3 and st4" << std::endl << std::endl;
		st3.swap(st4);
		print_attributes(st3);
		print_attributes(st4);
	
		print_it(st4.rbegin(), st4.rend());
		
		ft::set<int>::const_iterator first = st3.begin();
		ft::set<int>::const_iterator last = st3.end();
		print_it(first, last);
	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct with class <std::string> :" << std::endl << std::endl
			<< "push_back increasingly 2000 std::string" << std::endl << std::endl;
		ft::set<std::string> st1;

		
		std::string str = "A";
		size_t n = rand() % 250;
		for (size_t i = 0; i < n; i++)
		{
			str += static_cast<char>(rand() % 127 + 'A');
			st1.insert(str);
		}

		print_attributes(st1);

		std::cout << "copy construct from st1;" << std::endl << std::endl;

		ft::set<std::string> st2(st1);

		cmp(st1, st2);

	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct<int> 2 sets :" << std::endl << std::endl
			<< "insert 200 rand() on both" << std::endl << std::endl;

		std::string		begin("begin()");
		std::string		str_it("it");
		ft::set<int>	st1;
		ft::set<int>	st2;
	
		for (int i = 0; i < 200; i++)
		{
			st1.insert(rand());
			st2.insert(rand());
		}

		std::cout  << "copy construct from st1 :" << std::endl << std::endl;

		ft::set<int>	st3(st1);

		std::cout << "//////////////////////////Default iterator//////////////////////////" << std::endl << std::endl
			<< "it = st1.begin()" << std::endl;

		ft::set<int>::iterator	it(st1.begin());

		std::cout << "*it = " << *it << std::endl
			<< "it2 = st2.begin()" << std::endl;

		ft::set<int>::iterator	it2(st2.begin());

		std::cout << "*it2 = " << *it2 << std::endl
			<< "it3 = st3.begin()" << std::endl;

		ft::set<int>::iterator	it3(st3.begin());
		std::cout << "*it3 = " << *it3 << std::endl;

		std::cout << std::endl << "----------Costarison operators----------" << std::endl << std::endl
			<< str_it << " == set." << begin << "() ? :	";

		std::cout << (it == st1.begin())
			<< str_it << " != set." << begin << "() ? :	"
				<< (it != st1.begin()) << std::endl
				<< str_it << " <= set." << begin << "() ? :	"
				<< str_it << "++ == set." << begin << "() ? :	"
				<< (it++ == st1.begin()) << std::endl
				<< str_it << " != set." << begin << "() ? :	"
				<< (it != st1.begin()) << std::endl
				<< "--" << str_it << " == set." << begin << "() ? :	"
				<< (--it == st1.begin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "iterator		tst(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tst ? :	";
		
		ft::set<int>::iterator		tst(it);

		std::cout << (it++ == tst) << std::endl;

		std::cout << std::endl << "tst = " << str_it << ";" << std::endl << str_it << "-- == tst ? :	";

		tst = it;

		std::cout << (it-- == tst) << std::endl;

		std::cout << std::endl << "tst = " << str_it << ";" << std::endl << "++" << str_it << " == tst ? :	";

		tst = it;

		std::cout << (++it == tst) << std::endl;

		std::cout << std::endl << "tst = " << str_it << ";" << std::endl << "--" << str_it << " == tst ? :	";

		tst = it;

		std::cout << (--it == tst) << std::endl;


		str_it = "cit";

		std::cout << "//////////////////////////Const iterator//////////////////////////" << std::endl << std::endl
			<< "cit = st1.begin()" << std::endl;

		ft::set<int>::const_iterator	cit(st1.begin());

		std::cout << "*cit = " << *cit << std::endl
			<< "cit2 = st2.begin()" << std::endl;

		ft::set<int>::const_iterator	cit2(st2.begin());

		std::cout << "*cit2 = " << *cit2 << std::endl
			<< "cit3 = st3.begin()" << std::endl;

		ft::set<int>::const_iterator	cit3(st3.begin());
		std::cout << "*cit3 = " << *cit3 << std::endl;

		std::cout << std::endl << "----------Costarison operators----------" << std::endl << std::endl
			<< str_it << " == set." << begin << "() ? :	";

		std::cout << (cit == st1.begin())
			<< str_it << " != set." << begin << "() ? :	"
				<< (cit != st1.begin()) << std::endl
				<< str_it << "++ == set." << begin << "() ? :	"
				<< (cit++ == st1.begin()) << std::endl
				<< str_it << " != set." << begin << "() ? :	"
				<< (cit != st1.begin()) << std::endl
				<< "--" << str_it << " == set." << begin << "() ? :	"
				<< (--cit == st1.begin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "const_iterator		tst2(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tst ? :	";
		
		ft::set<int>::const_iterator		tst2(cit);

		std::cout << (cit++ == tst2) << std::endl;

		std::cout << std::endl << "tst2 = " << str_it << ";" << std::endl << str_it << "-- == tst2 ? :	";

		tst2 = cit;

		std::cout << (cit-- == tst2) << std::endl;

		std::cout << std::endl << "tst2 = " << str_it << ";" << std::endl << "++" << str_it << " == tst2 ? :	";

		tst2 = cit;

		std::cout << (++cit == tst2) << std::endl;

		std::cout << std::endl << "tst2 = " << str_it << ";" << std::endl << "--" << str_it << " == tst2 ? :	";

		tst2 = cit;

		std::cout << (--cit == tst2) << std::endl;

		str_it = "rit";
		begin = "rbegin";

		std::cout << "//////////////////////////reverse iterator//////////////////////////" << std::endl << std::endl
			<< "rit = st1.rbegin()" << std::endl;

		ft::set<int>::reverse_iterator	rit(st1.rbegin());

		std::cout << "*rit = " << *rit << std::endl
			<< "rit2 = st2.rbegin()" << std::endl;

		ft::set<int>::reverse_iterator	rit2(st2.rbegin());

		std::cout << "*rit2 = " << *rit2 << std::endl
			<< "rit3 = st3.rbegin()" << std::endl;

		ft::set<int>::reverse_iterator	rit3(st3.rbegin());
		std::cout << "*rit3 = " << *rit3 << std::endl;
		std::cout << std::endl << "----------Costarison operators----------" << std::endl << std::endl
			 << str_it << " == set." << begin << "() ? :	";

		std::cout << (rit == st1.rbegin()) << std::endl
			<< str_it << " != set." << begin << "() ? :	"
				<< (rit != st1.rbegin()) << std::endl
				<< str_it << "++ == set." << begin << "() ? :	"
				<< (rit++ == st1.rbegin()) << std::endl
				<< str_it << " != set." << begin << "() ? :	"
				<< (rit != st1.rbegin()) << std::endl
				<< "--" << str_it << " == set." << begin << "() ? :	"
				<< (--rit == st1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "reverse_iterator		tst3(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tst ? :	";
		
		ft::set<int>::reverse_iterator		tst3(rit);

		std::cout << (rit++ == tst3) << std::endl;

		std::cout << std::endl << "tst3 = " << str_it << ";" << std::endl << str_it << "-- == tst3 ? :	";

		tst3 = rit;

		std::cout << (rit-- == tst3) << std::endl;

		std::cout << std::endl << "tst3 = " << str_it << ";" << std::endl << "++" << str_it << " == tst3 ? :	";

		tst3 = rit;

		std::cout << (++rit == tst3) << std::endl;

		std::cout << std::endl << "tst3 = " << str_it << ";" << std::endl << "--" << str_it << " == tst3 ? :	";

		tst3 = rit;

		std::cout << (--rit == tst3) << std::endl;

		str_it = "crit";

		std::cout << "//////////////////////////const reverse iterator//////////////////////////" << std::endl << std::endl
			<< "crit = st1.rbegin()" << std::endl;

		ft::set<int>::const_reverse_iterator	crit(st1.rbegin());

		std::cout << "*crit = " << *crit << std::endl
			<< "crit2 = st2.rbegin()" << std::endl;

		ft::set<int>::const_reverse_iterator	crit2(st2.rbegin());

		std::cout << "*crit2 = " << *crit2 << std::endl
			<< "crit3 = st3.rbegin()" << std::endl;

		ft::set<int>::const_reverse_iterator	crit3(st3.rbegin());
		std::cout << "*crit3 = " << *crit3 << std::endl;

		std::cout << std::endl << "----------Costarison operators----------" << std::endl << std::endl
			<< str_it << " == set." << begin << "() ? :	";

		std::cout << (crit == st1.rbegin()) << std::endl
				<< str_it << " != set." << begin << "() ? :	" << std::endl
				<< (crit != st1.rbegin()) << std::endl
				<< str_it << "++ == set." << begin << "() ? :	"
				<< (crit++ == st1.rbegin()) << std::endl
				<< str_it << " != set." << begin << "() ? :	"
				<< (crit != st1.rbegin()) << std::endl
				<< "--" << str_it << " == set." << begin << "() ? :	"
				<< (--crit == st1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "const_reverse_iterator		tst4(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tst ? :	";
		
		ft::set<int>::const_reverse_iterator		tst4(crit);

		std::cout << (crit++ == tst4) << std::endl;

		std::cout << std::endl << "tst4 = " << str_it << ";" << std::endl << str_it << "-- == tst4 ? :	";

		tst4 = crit;

		std::cout << (crit-- == tst4) << std::endl;

		std::cout << std::endl << "tst4 = " << str_it << ";" << std::endl << "++" << str_it << " == tst4 ? :	";

		tst4 = crit;

		std::cout << (++crit == tst4) << std::endl;

		std::cout << std::endl << "tst4 = " << str_it << ";" << std::endl << "--" << str_it << " == tst4 ? :	";

		tst4 = crit;

		std::cout << (--crit == tst4) << std::endl;

	}

	std::cout << "_______________________________________________" << std::endl;

	{
	std::cout << "Relational operator test" << std::endl << std::endl
		<< "set1 = randomly filled set of size " << 200 << ";" << std::endl
		<< "set2 = set1 copy;" << std::endl
		<< "set3 = other random st of size " << 200 << ";" << std::endl
		<< "set4 = other random st of size " << 2000 << ";" << std::endl
		<< "set5 = other random st of size " << 20 << ";" << std::endl << std::endl;

	ft::set<int>		st1;
	ft::set<int>		st2;
	ft::set<int>		st3;
	ft::set<int>		st4;
	ft::set<int>		st5;
	int					val;

	for (int i = 0; i < 200; i++)
	{
		val = rand();
		st1.insert(val);
		st2.insert(val);
	}
	for (int i = 0; i < 200; i++)
	{
		val = rand();
	}
	for (int i = 0; i < 2000; i++)
	{
		val = rand();
	}
	for (int i = 0; i < 20; i++)
	{
		val = rand();
		st5.insert(val);
	}

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"==\" " << std::endl << std::endl
		<< "set1 == set2 ? :		";

	std::cout << (st1 == st2) << std::endl;
	

	std::cout << "set1 == set3 ? :		";

	std::cout << (st1 == st3) << std::endl;
	

	std::cout << "set1 == set4 ? :		";

	std::cout << (st1 == st4) << std::endl;
	

	std::cout << "set1 == set5 ? :		";

	std::cout << (st1 == st5) << std::endl;
	

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"!=\" " << std::endl << std::endl
		<< "set1 != set2 ? :		";

	std::cout << (st1 != st2) << std::endl;


	std::cout << "set1 != set3 ? :		";

	std::cout << (st1 != st3) << std::endl;


	std::cout << "set1 != set4 ? :		";

	std::cout << (st1 != st4) << std::endl;


	std::cout << "set1 != set5 ? :		";

	std::cout << (st1 != st5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<\" " << std::endl << std::endl
		<< "set1 < set2 ? :			";

	std::cout << (st1 < st2)  << std::endl;

	std::cout << "set1 < set3 ? :			";

	std::cout << (st1 < st3)  << std::endl;

	std::cout << "set1 < set4 ? :			";

	std::cout << (st1 < st4)  << std::endl;

	std::cout << "set1 < set5 ? :			";

	std::cout << (st1 < st5)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<=\" " << std::endl << std::endl
		<< "set1 <= set2 ? :		";

	std::cout << (st1 <= st2) << std::endl;


	std::cout << "set1 <= set3 ? :		";

	std::cout << (st1 <= st3) << std::endl;


	std::cout << "set1 <= set4 ? :		";

	std::cout << (st1 <= st4) << std::endl;


	std::cout << "set1 <= set5 ? :		";

	std::cout << (st1 <= st5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">\" " << std::endl << std::endl
		<< "set1 > set2 ? :			";

	std::cout << (st1 > st2)  << std::endl;

	std::cout << "set1 > set3 ? :			";

	std::cout << (st1 > st3)  << std::endl;

	std::cout << "set1 > set4 ? :			";

	std::cout << (st1 > st4)  << std::endl;

	std::cout << "set1 > set5 ? :			";

	std::cout << (st1 > st5)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">=\" " << std::endl << std::endl
		<< "set1 >= set2 ? :		";

	std::cout << (st1 >= st2) << std::endl;


	std::cout << "set1 >= set3 ? :		";

	std::cout << (st1 >= st3) << std::endl;


	std::cout << "set1 >= set4 ? :		";

	std::cout << (st1 >= st4) << std::endl;


	std::cout << "set1 >= set5 ? :		";

	std::cout << (st1 >= st5) << std::endl;

	}

	return 0;
}
