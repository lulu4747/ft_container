#include <iostream>
#include <stack>
#include <sys/time.h>
#include "stack_test.hpp"
#include "../tester.hpp"
#include "../../ft_containers/stack.hpp"

static bool	default_constructor_test()
{
	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::stack<int>	ft;
	std::stack<int>	stl;

	if (!(print_test_result(stack_compare(ft, stl))))
		return false;

	return true;
}

static bool	push_test()
{
	int	val(std::rand());

	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "push test" << std::endl << std::endl
		<< "stack.push(" << val << ") on empty stack" << std::endl;

	ft::stack<int>	ft;
	std::stack<int>	stl;

	ft.push(val);
	stl.push(val);

	if (!(print_test_result(stack_compare(ft, stl))))
		return false;

	val = std::rand();
	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.push(" << val << ")" << std::endl;

	ft.push(val);
	stl.push(val);

	if (!(print_test_result(stack_compare(ft, stl))))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.push(std::rand()) " << EXTRA_LARGE << " times" << std::endl;

	for (int i = 0; i < EXTRA_LARGE; i++)
	{
		val = std::rand();
		ft.push(val);
		stl.push(val);
	}

	if (!(print_test_result(stack_compare(ft, stl))))
		return false;

	return true;
}

static bool	pop_test()
{

	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "push test" << std::endl << std::endl
		<< "stack.pop() on random values stack whith size = " << EXTRA_LARGE << std::endl;

	ft::stack<int>	ft;
	std::stack<int>	stl;
	int				val;

	for (int i = 0; i < EXTRA_LARGE; i++)
	{
		val = std::rand();
		ft.push(val);
		stl.push(val);
	}

	ft.pop();
	stl.pop();

	if (!(print_test_result(stack_compare(ft, stl))))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.pop() " << EXTRA_LARGE / 2 << " times" << std::endl;

	for (int i = 0; i < EXTRA_LARGE / 2; i++)
	{
		ft.pop();
		stl.pop();
	}

	if (!(print_test_result(stack_compare(ft, stl))))
		return false;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.pop() until stack.empty() is true" << std::endl;

	while (!ft.empty())
	{
		ft.pop();
		stl.pop();
	}

	if (!(print_test_result(stack_compare(ft, stl))))
		return false;

	return true;
}

static bool	top_test()
{

	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "push test" << std::endl << std::endl
		<< "stack.top() on random values stack whith size = " << EXTRA_LARGE << std::endl
		<< "			";

	ft::stack<int>	ft;
	std::stack<int>	stl;
	int				val;

	for (int i = 0; i < EXTRA_LARGE; i++)
	{
		val = std::rand();
		ft.push(val);
		stl.push(val);
	}

	if (!(print_test_result(ft.top() == stl.top())))
		return false;

	std::cout << "stack.top() after stack.pop() " << EXTRA_LARGE / 2 << " times" << std::endl
		<< "			";

	for (int i = 0; i < EXTRA_LARGE / 2; i++)
	{
		ft.pop();
		stl.pop();
	}

	if (!(print_test_result(ft.top() == stl.top())))
		return false;

	return true;
}

static bool	relationnal_operators_test()
{
	std::cout << "_______________________________________________" << std::endl
		<< "Relational operator test" << std::endl << std::endl
		<< "stack1 = randomly filled stack of size " << MEDIUM << ";" << std::endl
		<< "stack2 = stack1 copy;" << std::endl
		<< "stack3 = other random vec of size " << MEDIUM << ";" << std::endl
		<< "stack4 = other random vec of size " << LARGE << ";" << std::endl
		<< "stack5 = other random vec of size " << SHORT << ";" << std::endl << std::endl;

	ft::stack<int>		ft1;
	ft::stack<int>		ft2;
	ft::stack<int>		ft3;
	ft::stack<int>		ft4;
	ft::stack<int>		ft5;
	std::stack<int>		stl1;
	std::stack<int>		stl2;
	std::stack<int>		stl3;
	std::stack<int>		stl4;
	std::stack<int>		stl5;
	int					val;

	for (int i = 0; i < MEDIUM; i++)
	{
		val = std::rand();
		ft1.push(val);
		ft2.push(val);
		stl1.push(val);
		stl2.push(val);
	}
	for (int i = 0; i < MEDIUM; i++)
	{
		val = std::rand();
		ft3.push(val);
		stl3.push(val);
	}
	for (int i = 0; i < LARGE; i++)
	{
		val = std::rand();
		ft4.push(val);
		stl4.push(val);
	}
	for (int i = 0; i < SHORT; i++)
	{
		val = std::rand();
		ft5.push(val);
		stl5.push(val);
	}

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"==\" " << std::endl << std::endl
		<< "stack1 == stack2 ? :		";

	std::cout << std::boolalpha << (vct1 == vct2) << std::endl;
	

	std::cout << "stack1 == stack3 ? :		";

	std::cout << std::boolalpha << (vct1 == vct3) << std::endl;
	

	std::cout << "stack1 == stack4 ? :		";

	std::cout << std::boolalpha << (vct1 == vct4) << std::endl;
	

	std::cout << "stack1 == stack5 ? :		";

	std::cout << std::boolalpha << (vct1 == vct5) << std::endl;
	

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"!=\" " << std::endl << std::endl
		<< "stack1 != stack2 ? :		";

	std::cout << std::boolalpha << (vct1 != vct2) << std::endl;


	std::cout << "stack1 != stack3 ? :		";

	std::cout << std::boolalpha << (vct1 != vct3) << std::endl;


	std::cout << "stack1 != stack4 ? :		";

	std::cout << std::boolalpha << (vct1 != vct4) << std::endl;


	std::cout << "stack1 != stack5 ? :		";

	std::cout << std::boolalpha << (vct1 != vct5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<\" " << std::endl << std::endl
		<< "stack1 < stack2 ? :			";

	std::cout << std::boolalpha << (vct1 < fvct)  << std::endl;

	std::cout << "stack1 < stack3 ? :			";

	std::cout << std::boolalpha << (vct1 < fvct)  << std::endl;

	std::cout << "stack1 < stack4 ? :			";

	std::cout << std::boolalpha << (vct1 < fvct)  << std::endl;

	std::cout << "stack1 < stack5 ? :			";

	std::cout << std::boolalpha << (vct1 < fvct)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \"<=\" " << std::endl << std::endl
		<< "stack1 <= stack2 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct2) << std::endl;


	std::cout << "stack1 <= stack3 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct3) << std::endl;


	std::cout << "stack1 <= stack4 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct4) << std::endl;


	std::cout << "stack1 <= stack5 ? :		";

	std::cout << std::boolalpha << (vct1 <= vct5) << std::endl;


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">\" " << std::endl << std::endl
		<< "stack1 > stack2 ? :			";

	std::cout << std::boolalpha << (vct1 > fvct)  << std::endl;

	std::cout << "stack1 > stack3 ? :			";

	std::cout << std::boolalpha << (vct1 > fvct)  << std::endl;

	std::cout << "stack1 > stack4 ? :			";

	std::cout << std::boolalpha << (vct1 > fvct)  << std::endl;

	std::cout << "stack1 > stack5 ? :			";

	std::cout << std::boolalpha << (vct1 > fvct)  << std::endl;

	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< " \">=\" " << std::endl << std::endl
		<< "stack1 >= stack2 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct2) << std::endl;


	std::cout << "stack1 >= stack3 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct3) << std::endl;


	std::cout << "stack1 >= stack4 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct4) << std::endl;


	std::cout << "stack1 >= stack5 ? :		";

	std::cout << std::boolalpha << (vct1 >= vct5) << std::endl;

}

bool	stack_test()
{
	if (default_constructor_test() == false)
		return false;

	if (push_test() == false)
		return false;

	if (pop_test() == false)
		return false;

	if (top_test() == false)
		return false;

	if (relationnal_operators_test() == false)
		return false;

	std::cout << std::endl << "*****************************************************" << std::endl << std::endl
		<< "Stack :					";
	print_test_result(true);
	std::cout << std::endl << "*****************************************************" << std::endl;

	return true;
}