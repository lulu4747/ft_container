#include <iostream>
#include "stack_test.hpp"

int	main()
{
	srand(SEED);

{
	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "default construction" << std::endl << std::endl;
	ft::stack<int>	stk;
	print_attributes(stk);
}


{
	int	val(std::rand());

	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "push test" << std::endl << std::endl
		<< "stack.push(" << val << ") on empty stack" << std::endl;

	ft::stack<int>	stk;

	stk.push(val);

	print_attributes(stk);


	val = std::rand();
	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.push(" << val << ")" << std::endl;

	stk.push(val);

	print_attributes(stk);


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.push(std::rand()) " << 20000 << " times" << std::endl;

	for (int i = 0; i < 20000; i++)
	{
		val = std::rand();
		stk.push(val);
	}

	print_attributes(stk);
}


{

	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "push test" << std::endl << std::endl
		<< "stack.pop() on random values stack whith size = " << 20000 << std::endl;

	ft::stack<int>	stk;
	int				val;

	for (int i = 0; i < 20000; i++)
	{
		val = std::rand();
		stk.push(val);
	}

	stk.pop();

	print_attributes(stk);


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.pop() " << 20000 / 2 << " times" << std::endl;

	for (int i = 0; i < 20000 / 2; i++)
	{
		stk.pop();
	}

	print_attributes(stk);


	std::cout << std::endl << std::endl
		<< "#######################################" << std::endl << std::endl
		<< "stack.pop() until stack.empty() is true" << std::endl;

	while (!stk.empty())
	{
		stk.pop();
	}

	print_attributes(stk);
}


{

	std::cout << "_______________________________________________" << std::endl
		<< "	stack" << std::endl << std::endl
		<< "push test" << std::endl << std::endl
		<< "stack.top() on random values stack whith size = " << 20000 << std::endl
		<< "			";

	ft::stack<int>	stk;
	int				val;

	for (int i = 0; i < 20000; i++)
	{
		val = std::rand();
		stk.push(val);
	}

	std::cout << "stack.top() = " << stk.top() << std::endl;


	std::cout << "stack.top() astker stack.pop() " << 20000 / 2 << " times" << std::endl
		<< "			";

	for (int i = 0; i < 20000 / 2; i++)
	{
		stk.pop();
	}

	std::cout << "stack.top() = " << stk.top() << std::endl;
}


	{
		std::cout << "_______________________________________________" << std::endl
			<< "Relational operator test" << std::endl << std::endl
			<< "stack1 = randomly filled stack of size " << 200 << ";" << std::endl
			<< "stack2 = stack1 copy;" << std::endl
			<< "stack3 = other random vec of size " << 200 << ";" << std::endl
			<< "stack4 = other random vec of size " << 2000 << ";" << std::endl
			<< "stack5 = other random vec of size " << 20 << ";" << std::endl << std::endl;

		ft::stack<int>		stk1;
		ft::stack<int>		stk2;
		ft::stack<int>		stk3;
		ft::stack<int>		stk4;
		ft::stack<int>		stk5;
		int					val;

		for (int i = 0; i < 200; i++)
		{
			val = std::rand();
			stk1.push(val);
			stk2.push(val);
		}
		for (int i = 0; i < 200; i++)
		{
			val = std::rand();
			stk3.push(val);
		}
		for (int i = 0; i < 2000; i++)
		{
			val = std::rand();
			stk4.push(val);
		}
		for (int i = 0; i < 20; i++)
		{
			val = std::rand();
			stk5.push(val);
		}

		std::cout << std::endl << std::endl
			<< "#######################################" << std::endl << std::endl
			<< " \"==\" " << std::endl << std::endl
			<< "stack1 == stack2 ? :		";

		std::cout << std::boolalpha << (stk1 == stk2) << std::endl;
		

		std::cout << "stack1 == stack3 ? :		";

		std::cout << std::boolalpha << (stk1 == stk3) << std::endl;
		

		std::cout << "stack1 == stack4 ? :		";

		std::cout << std::boolalpha << (stk1 == stk4) << std::endl;
		

		std::cout << "stack1 == stack5 ? :		";

		std::cout << std::boolalpha << (stk1 == stk5) << std::endl;
		

		std::cout << std::endl << std::endl
			<< "#######################################" << std::endl << std::endl
			<< " \"!=\" " << std::endl << std::endl
			<< "stack1 != stack2 ? :		";

		std::cout << std::boolalpha << (stk1 != stk2) << std::endl;


		std::cout << "stack1 != stack3 ? :		";

		std::cout << std::boolalpha << (stk1 != stk3) << std::endl;


		std::cout << "stack1 != stack4 ? :		";

		std::cout << std::boolalpha << (stk1 != stk4) << std::endl;


		std::cout << "stack1 != stack5 ? :		";

		std::cout << std::boolalpha << (stk1 != stk5) << std::endl;


		std::cout << std::endl << std::endl
			<< "#######################################" << std::endl << std::endl
			<< " \"<\" " << std::endl << std::endl
			<< "stack1 < stack2 ? :			";

		std::cout << std::boolalpha << (stk1 < stk2)  << std::endl;

		std::cout << "stack1 < stack3 ? :			";

		std::cout << std::boolalpha << (stk1 < stk3)  << std::endl;

		std::cout << "stack1 < stack4 ? :			";

		std::cout << std::boolalpha << (stk1 < stk4)  << std::endl;

		std::cout << "stack1 < stack5 ? :			";

		std::cout << std::boolalpha << (stk1 < stk5)  << std::endl;

		std::cout << std::endl << std::endl
			<< "#######################################" << std::endl << std::endl
			<< " \"<=\" " << std::endl << std::endl
			<< "stack1 <= stack2 ? :		";

		std::cout << std::boolalpha << (stk1 <= stk2) << std::endl;


		std::cout << "stack1 <= stack3 ? :		";

		std::cout << std::boolalpha << (stk1 <= stk3) << std::endl;


		std::cout << "stack1 <= stack4 ? :		";

		std::cout << std::boolalpha << (stk1 <= stk4) << std::endl;


		std::cout << "stack1 <= stack5 ? :		";

		std::cout << std::boolalpha << (stk1 <= stk5) << std::endl;


		std::cout << std::endl << std::endl
			<< "#######################################" << std::endl << std::endl
			<< " \">\" " << std::endl << std::endl
			<< "stack1 > stack2 ? :			";

		std::cout << std::boolalpha << (stk1 > stk2)  << std::endl;

		std::cout << "stack1 > stack3 ? :			";

		std::cout << std::boolalpha << (stk1 > stk3)  << std::endl;

		std::cout << "stack1 > stack4 ? :			";

		std::cout << std::boolalpha << (stk1 > stk4)  << std::endl;

		std::cout << "stack1 > stack5 ? :			";

		std::cout << std::boolalpha << (stk1 > stk5)  << std::endl;

		std::cout << std::endl << std::endl
			<< "#######################################" << std::endl << std::endl
			<< " \">=\" " << std::endl << std::endl
			<< "stack1 >= stack2 ? :		";

		std::cout << std::boolalpha << (stk1 >= stk2) << std::endl;


		std::cout << "stack1 >= stack3 ? :		";

		std::cout << std::boolalpha << (stk1 >= stk3) << std::endl;


		std::cout << "stack1 >= stack4 ? :		";

		std::cout << std::boolalpha << (stk1 >= stk4) << std::endl;


		std::cout << "stack1 >= stack5 ? :		";

		std::cout << std::boolalpha << (stk1 >= stk5) << std::endl;

	}
	return 0;
}