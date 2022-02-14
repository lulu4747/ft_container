#include <cstring>
#include <cstdlib>
#include <ctime>
#include "tester.hpp"

int main(int argc, char **argv)
{
	bool	time_check = false;

	srand(time(NULL));
	if (argc == 2 && !strcmp(argv[1], "time_check"))
		time_check = true;
	if (!(vector_test(time_check)))
		return 1;
	//stack_test();
	return 0;
}