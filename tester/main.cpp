#include <cstring>
#include <cstdlib>
#include <ctime>
#include "tester.hpp"

static	void	parsing(int argc, char **argv,
					bool *vector, bool *stack, bool *map, bool *time_check)
{
	if (argc == 2 || argc == 3)
	{
		if ((argc == 2 && !strcmp(argv[1], "time_check")) || (argc == 3 && !strcmp(argv[2], "time_check")))
			*time_check = true;
		if (!strcmp(argv[1], "vector"))
		{
			*stack = false;
			*map = false;
		}
		else if (!strcmp(argv[1], "stack"))
		{
			*vector = false;
			*map = false;
		}
		else if (!strcmp(argv[1], "map"))
		{
			*vector = false;
			*stack = false;
		}
	}
	return ;
}

int main(int argc, char **argv)
{
	bool	vector = true;
	bool	stack = true;
	bool	map = true;
	bool	time_check = false;

	srand(time(NULL));
	parsing(argc, argv, &vector, &stack, &map, &time_check);
	if (vector)
	{
		if (!(vector_test(time_check)))
			return 1;
	}
	if (stack)
	{
		if (!(stack_test()))
			return 1;
	}
	if (map)
	{
		if (!(map_test(time_check)))
			return 1;
	}
	return 0;
}