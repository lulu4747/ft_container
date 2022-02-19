#include <iostream>
#include <string>
#include <stdlib.h>
#include "map_test.hpp"
#include "../Foo.hpp"

int main(void)
{
	srand(SEED);

	{
		ft::map<int, int> mymap;
		ft::map<int, int> mymap2;
		size_t len = LEN;
		for( size_t i = 0; i < len; i++)
		{
			mymap.insert(ft::pair<int, int>(rand(), (int)rand()));
			mymap2.insert(ft::pair<int, int>(rand(), (int)rand()));
		}
		cmp(mymap, mymap2);
		cmp(mymap2, mymap);
		printSize(mymap);
		printSize(mymap2);

		erase_key(mymap2);
		erase_key(mymap);

		for (size_t i =0; i < 10; i++)
			test_bound(mymap, rand());

		cmp(mymap, mymap2);
		cmp(mymap2, mymap);
		printSize(mymap);
		printSize(mymap2);

		ft::map<int, int> clear_map;

		mymap.swap(clear_map); //mymy is clear

		printSize(mymap);

		clear_map.clear();
		mymap.clear(); //clear clear map

		printSize(mymap);
		printSize(clear_map);

	}


	{
		ft::map<Foo, int> mymap;
		ft::map<Foo, int> mymap2;
		size_t len = LEN;
		for( size_t i = 0; i < len; i++)
		{
			mymap.insert(ft::pair<int, int>(rand(), (int)rand()));
			mymap2.insert(ft::pair<int, int>(rand(), (int)rand()));
		}
		cmp(mymap, mymap2);
		cmp(mymap2, mymap);
		printSize(mymap);
		printSize(mymap2);

		erase_key(mymap2);
		erase_key(mymap);

		for (size_t i =0; i < 10; i++)
			test_bound(mymap, rand());

		cmp(mymap, mymap2);
		cmp(mymap2, mymap);
		printSize(mymap);
		printSize(mymap2);

		ft::map<Foo, int> clear_map;

		mymap.swap(clear_map); //mymy is clear

		printSize(mymap);

		clear_map.clear();
		mymap.clear(); //clear clear map

		printSize(mymap);
		printSize(clear_map);

	}

	{
		ft::map<char, int> mymap;
		ft::vector<char> letter;

		for (char i = 'a'; i != 'z' + 1; i++)
			letter.push_back(i);
		

		for(ft::vector<char>::iterator it = letter.begin(); it != letter.end(); it++)
			mymap.insert(ft::make_pair(*it, rand()));

		ft::map<char, int> mymap2;

		//mymap2.insert(mymap.begin(), mymap.end());
		mymap2 = mymap;

		for (size_t i =0; i < 5; i++)
			test_bound(mymap, (char)rand());
		cmp(mymap, mymap2);
		printSize(mymap2);

		//erase_key(mymap2);
		erase_key(mymap, 155);

		cmp(mymap, mymap2);
		printSize(mymap, false);

	}

	//iterator compile
	{
		ft::vector<ft::pair<int, int> > vct;

		for (int i = 0; i != 100; i++)
			vct.push_back(ft::make_pair(rand(), rand()));
	

		ft::map<int, int> mymap(vct.begin(), vct.end());


		ft::map<int, int>::iterator a; //default
		
		a = mymap.begin(); //operator=
		
		ft::map<int, int>::iterator b(a++); //copy

		std::cout << "b == a " << (b == a) << std::endl;
		std::cout << "b != a " << (b != a) << std::endl;

		std::cout << b->first << " => " << (*b).second << std::endl; // a-> *a

		++b;
		b++;

		std::cout << (*b).first << " => " << (*b++).second << std::endl; 
		std::cout << b->first << " => " << (*b).second << std::endl;

		--b;
		b--;
		std::cout << "b == a " << (*b-- == *a) << std::endl;

		b->second = rand();
		std::cout << b->first << " => " << (*b).second << std::endl;
		//*b = ft::make_pair<const int, int>(rand(), rand()); error


		ft::map<int, int>::const_iterator ca;

		ca = a;

		ft::map<int, int>::const_iterator cb(b);

		std::cout << cb->first << " => " << (*cb).second << std::endl;
		
	}

		std::cout << "default constructor :" << std::endl << std::endl;
	{	
		ft::map<int, int> mp; //default const
		print_attributes(mp);

		std::cout << "map.insert(map.end(), ft::make_pair(rand(), rand())) " << LEN << " times :" << std::endl << std::endl;

		for(int i = 0; i < LEN; i++)
		{
			mp.insert(mp.end(), ft::make_pair(rand(), rand()));
		}
		print_attributes(mp);

		std::cout << "copy constructor and compare :" << std::endl << std::endl;

		ft::map<int, int> cpy = mp; // cpy

		print_attributes(mp);
		cmp(mp, cpy); // cmp cpy
	
		std::cout << "copy.clear() and compare :" << std::endl << std::endl;
		cpy.clear();
		print_attributes(mp);
		cmp(mp, cpy); //cmp with empty
	}

	std::cout << "______________________________________" << std::endl << std::endl;
	/* ******** */ // at() swap() empty() capacity() pop_back()...

	{
		std::cout << "default construct 2 maps :" << std::endl << std::endl;

		ft::map<int, int> mp1;
		ft::map<int, int> mp2;

		std::cout << "for(int i = 0; i < 125; i++)" << std::endl
			<< "	mp1.insert(mp1.end(), ft::make_pair(rand(), rand())); :" << std::endl << std::endl;

		for(int i = 0; i < 125; i++)
		{
			mp1.insert(mp1.end(), ft::make_pair(rand(), rand()));
		}

		print_attributes(mp1);
		print_attributes(mp2);

		std::cout << "mp2.swap(mp1);" << std::endl << std::endl;

		mp2.swap(mp1);

		print_attributes(mp1);
		print_attributes(mp2);

		std::cout << "mp1 = mp2;" << std::endl << std::endl;

		mp1 = mp2;

		print_attributes(mp1);
		print_attributes(mp2);
		cmp(mp1, mp2);

	}

	std::cout << "______________________________________" << std::endl << std::endl;
	
	/* ******** */ //range_constructor front() back()

	{
		std::cout << "default construct :" << std::endl << std::endl
			<< "for(int i = 0; i < " << LEN << "; i++)" << std::endl
			<< "	mp1.insert(mp1.end(), ft::make_pair(rand(), rand())); :" << std::endl << std::endl;

		ft::map<int, int> mp1;

		for(int i =0; i < LEN; i++)
		{
			mp1.insert(mp1.end(), ft::make_pair(rand(), rand()));
		}

		std::cout << "range construct mp2 from mp1.begin() to mp1.end()" << std::endl << std::endl;

		ft::map<int, int> mp2(mp1.begin(), mp1.end());

		std::cout << "copy construct mp3 from mp1 :" << std::endl << std::endl;

		ft::map<int, int> mp3(mp1);

		std::cout << "default construct mp4 :" << std::endl << std::endl;

		ft::map<int, int> mp4;

		cmp(mp2, mp1);
		cmp(mp3, mp1);
		cmp(mp3, mp2);
		print_attributes(mp1);
		print_attributes(mp2);
		print_attributes(mp3);
		print_attributes(mp4);

		std::cout << "mp4.insert(mp3.size(), ft::make_pair(rand(), rand()));" << std::endl << std::endl;

		mp4.insert(mp3.begin(), ft::make_pair(rand(), rand()));

		cmp(mp3, mp1);
		cmp(mp3, mp2);
		cmp(mp2, mp1);
		print_attributes(mp1);
		print_attributes(mp2);

		std::cout << "erase pos;" << std::endl << std::endl;
	
		if (!mp4.empty())
			mp4.erase(mp4.begin());

		std::cout << "swap mp3 and mp4" << std::endl << std::endl;
		mp3.swap(mp4);
		print_attributes(mp3);
		print_attributes(mp4);
	
		print_it(mp4.rbegin(), mp4.rend());
		
		ft::map<int, int>::const_iterator first = mp3.begin();
		ft::map<int, int>::const_iterator last = mp3.end();
		print_it(first, last);
	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct with class <std::string> :" << std::endl << std::endl
			<< "push_back increasingly 2000 std::string" << std::endl << std::endl;
		ft::map<std::string, int> mp1;

		
		std::string str = "A";
		size_t len = rand() % 250;
		for (size_t i = 0; i < len; i++)
		{
			str += static_cast<char>(rand() % 127 + 'A');
			mp1.insert(ft::make_pair(str, int()));
		}

		print_attributes(mp1);

		std::cout << "copy construct from mp1;" << std::endl << std::endl;

		ft::map<std::string, int> mp2(mp1);

		cmp(mp1, mp2);

	}

	std::cout << "______________________________________" << std::endl << std::endl;

	{
		std::cout << "default construct<int> 2 maps :" << std::endl << std::endl
			<< "insert 200 ft::make_pair(rand(), rand()) on both" << std::endl << std::endl;

		std::string		begin("begin()");
		std::string		str_it("begin()");
		ft::map<int, int>	mp1;
		ft::map<int, int>	mp2;
	
		for (int i = 0; i < 200; i++)
		{
			mp1.insert(ft::make_pair(rand(), rand()));
			mp2.insert(ft::make_pair(rand(), rand()));
		}

		std::cout  << "copy construct from mp1 :" << std::endl << std::endl;

		ft::map<int, int>	mp3(mp1);

		std::cout << "//////////////////////////Default iterator//////////////////////////" << std::endl << std::endl
			<< "it = mp1.begin()" << std::endl;

		ft::map<int, int>::iterator	it(mp1.begin());

		std::cout << "it->first = " << it->first << std::endl
			<< "it2 = mp2.begin()" << std::endl;

		ft::map<int, int>::iterator	it2(mp2.begin());

		std::cout << "it2->first = " << it2->first << std::endl
			<< "it3 = mp3.begin()" << std::endl;

		ft::map<int, int>::iterator	it3(mp3.begin());
		std::cout << "it3->first = " << it3->first << std::endl;

		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			<< str_it << " == map." << begin << "() ? :	";

		std::cout << (it == mp1.begin())
			<< str_it << " != map." << begin << "() ? :	"
				<< (it != mp1.begin()) << std::endl
				<< str_it << " <= map." << begin << "() ? :	"
				<< str_it << "++ == map." << begin << "() ? :	"
				<< (it++ == mp1.begin()) << std::endl
				<< str_it << " != map." << begin << "() ? :	"
				<< (it != mp1.begin()) << std::endl
				<< "--" << str_it << " == map." << begin << "() ? :	"
				<< (--it == mp1.begin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "iterator		tmp(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::map<int, int>::iterator		tmp(it);

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
			<< "cit = mp1.begin()" << std::endl;

		ft::map<int, int>::const_iterator	cit(mp1.begin());

		std::cout << "cit->first = " << cit->first << std::endl
			<< "cit2 = mp2.begin()" << std::endl;

		ft::map<int, int>::const_iterator	cit2(mp2.begin());

		std::cout << "cit2->first = " << cit2->first << std::endl
			<< "cit3 = mp3.begin()" << std::endl;

		ft::map<int, int>::const_iterator	cit3(mp3.begin());
		std::cout << "cit3->first = " << cit3->first << std::endl;

		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			<< str_it << " == map." << begin << "() ? :	";

		std::cout << (cit == mp1.begin())
			<< str_it << " != map." << begin << "() ? :	"
				<< (cit != mp1.begin()) << std::endl
				<< str_it << "++ == map." << begin << "() ? :	"
				<< (cit++ == mp1.begin()) << std::endl
				<< str_it << " != map." << begin << "() ? :	"
				<< (cit != mp1.begin()) << std::endl
				<< "--" << str_it << " == map." << begin << "() ? :	"
				<< (--cit == mp1.begin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "const_iterator		tmp2(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::map<int, int>::const_iterator		tmp2(cit);

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
			<< "rit = mp1.rbegin()" << std::endl;

		ft::map<int, int>::reverse_iterator	rit(mp1.rbegin());

		std::cout << "rit->first = " << rit->first << std::endl
			<< "rit2 = mp2.rbegin()" << std::endl;

		ft::map<int, int>::reverse_iterator	rit2(mp2.rbegin());

		std::cout << "rit2->first = " << rit2->first << std::endl
			<< "rit3 = mp3.rbegin()" << std::endl;

		ft::map<int, int>::reverse_iterator	rit3(mp3.rbegin());
		std::cout << "rit3->first = " << rit3->first << std::endl;
		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			 << str_it << " == map." << begin << "() ? :	";

		std::cout << (rit == mp1.rbegin()) << std::endl
			<< str_it << " != map." << begin << "() ? :	"
				<< (rit != mp1.rbegin()) << std::endl
				<< str_it << "++ == map." << begin << "() ? :	"
				<< (rit++ == mp1.rbegin()) << std::endl
				<< str_it << " != map." << begin << "() ? :	"
				<< (rit != mp1.rbegin()) << std::endl
				<< "--" << str_it << " == map." << begin << "() ? :	"
				<< (--rit == mp1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "reverse_iterator		tmp3(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::map<int, int>::reverse_iterator		tmp3(rit);

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
/*
		str_it = "crit";

		std::cout << "//////////////////////////const reverse iterator//////////////////////////" << std::endl << std::endl
			<< "crit = mp1.rbegin()" << std::endl;

		ft::map<int, int>::const_reverse_iterator	crit(mp1.rbegin());

		std::cout << "crit->first = " << crit->first << std::endl
			<< "crit2 = mp2.rbegin()" << std::endl;

		ft::map<int, int>::const_reverse_iterator	crit2(mp2.rbegin());

		std::cout << "crit2->first = " << crit2->first << std::endl
			<< "crit3 = mp3.rbegin()" << std::endl;

		ft::map<int, int>::const_reverse_iterator	crit3(mp3.rbegin());
		std::cout << "crit3->first = " << crit3->first << std::endl;

		std::cout << std::endl << "----------Comparison operators----------" << std::endl << std::endl
			<< str_it << " == map." << begin << "() ? :	";

		std::cout << (crit == mp1.rbegin()) << std::endl
				<< str_it << " != map." << begin << "() ? :	" << std::endl
				<< (crit != mp1.rbegin()) << std::endl
				<< str_it << "++ == map." << begin << "() ? :	"
				<< (crit++ == mp1.rbegin()) << std::endl
				<< str_it << " != map." << begin << "() ? :	"
				<< (crit != mp1.rbegin()) << std::endl
				<< "--" << str_it << " == map." << begin << "() ? :	"
				<< (--crit == mp1.rbegin()) << std::endl;

		std::cout << std::endl << "----------Increment/Decrement operators----------" << std::endl << std::endl
			<< "const_reverse_iterator		tmp4(" << str_it << ");" << std::endl << std::endl << str_it << "++ == tmp ? :	";
		
		ft::map<int, int>::const_reverse_iterator		tmp4(crit);

		std::cout << (crit++ == tmp4) << std::endl;

		std::cout << std::endl << "tmp4 = " << str_it << ";" << std::endl << str_it << "-- == tmp4 ? :	";

		tmp4 = crit;

		std::cout << (crit-- == tmp4) << std::endl;

		std::cout << std::endl << "tmp4 = " << str_it << ";" << std::endl << "++" << str_it << " == tmp4 ? :	";

		tmp4 = crit;

		std::cout << (++crit == tmp4) << std::endl;

		std::cout << std::endl << "tmp4 = " << str_it << ";" << std::endl << "--" << str_it << " == tmp4 ? :	";

		tmp4 = crit;

		std::cout << (--crit == tmp4) << std::endl;*/

	}

	std::cout << "_______________________________________________" << std::endl;

	{
	std::cout << "Relational operator test" << std::endl << std::endl
		<< "map1 = randomly filled map of size " << 200 << ";" << std::endl
		<< "map2 = map1 copy;" << std::endl
		<< "map3 = other random mp of size " << 200 << ";" << std::endl
		<< "map4 = other random mp of size " << 2000 << ";" << std::endl
		<< "map5 = other random mp of size " << 20 << ";" << std::endl << std::endl;

	ft::map<int, int>		vct1;
	ft::map<int, int>		vct2;
	ft::map<int, int>		vct3;
	ft::map<int, int>		vct4;
	ft::map<int, int>		vct5;
	ft::pair<int, int>		val;

	for (int i = 0; i < 200; i++)
	{
		val = ft::make_pair(rand(), rand());
		vct1.insert(val);
		vct2.insert(val);
	}
	for (int i = 0; i < 200; i++)
	{
		val = ft::make_pair(rand(), rand());
	}
	for (int i = 0; i < 2000; i++)
	{
		val = ft::make_pair(rand(), rand());
	}
	for (int i = 0; i < 20; i++)
	{
		val = ft::make_pair(rand(), rand());
		vct5.insert(val);
	}

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"==\" " << std::endl << std::endl
		<< "map1 == map2 ? :		";

	std::cout << (vct1 == vct2) << std::endl;
	

	std::cout << "map1 == map3 ? :		";

	std::cout << (vct1 == vct3) << std::endl;
	

	std::cout << "map1 == map4 ? :		";

	std::cout << (vct1 == vct4) << std::endl;
	

	std::cout << "map1 == map5 ? :		";

	std::cout << (vct1 == vct5) << std::endl;
	

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"!=\" " << std::endl << std::endl
		<< "map1 != map2 ? :		";

	std::cout << (vct1 != vct2) << std::endl;


	std::cout << "map1 != map3 ? :		";

	std::cout << (vct1 != vct3) << std::endl;


	std::cout << "map1 != map4 ? :		";

	std::cout << (vct1 != vct4) << std::endl;


	std::cout << "map1 != map5 ? :		";

	std::cout << (vct1 != vct5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<\" " << std::endl << std::endl
		<< "map1 < map2 ? :			";

	std::cout << (vct1 < vct2)  << std::endl;

	std::cout << "map1 < map3 ? :			";

	std::cout << (vct1 < vct3)  << std::endl;

	std::cout << "map1 < map4 ? :			";

	std::cout << (vct1 < vct4)  << std::endl;

	std::cout << "map1 < map5 ? :			";

	std::cout << (vct1 < vct5)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<=\" " << std::endl << std::endl
		<< "map1 <= map2 ? :		";

	std::cout << (vct1 <= vct2) << std::endl;


	std::cout << "map1 <= map3 ? :		";

	std::cout << (vct1 <= vct3) << std::endl;


	std::cout << "map1 <= map4 ? :		";

	std::cout << (vct1 <= vct4) << std::endl;


	std::cout << "map1 <= map5 ? :		";

	std::cout << (vct1 <= vct5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">\" " << std::endl << std::endl
		<< "map1 > map2 ? :			";

	std::cout << (vct1 > vct2)  << std::endl;

	std::cout << "map1 > map3 ? :			";

	std::cout << (vct1 > vct3)  << std::endl;

	std::cout << "map1 > map4 ? :			";

	std::cout << (vct1 > vct4)  << std::endl;

	std::cout << "map1 > map5 ? :			";

	std::cout << (vct1 > vct5)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">=\" " << std::endl << std::endl
		<< "map1 >= map2 ? :		";

	std::cout << (vct1 >= vct2) << std::endl;


	std::cout << "map1 >= map3 ? :		";

	std::cout << (vct1 >= vct3) << std::endl;


	std::cout << "map1 >= map4 ? :		";

	std::cout << (vct1 >= vct4) << std::endl;


	std::cout << "map1 >= map5 ? :		";

	std::cout << (vct1 >= vct5) << std::endl;

	}

	return 0;
}
