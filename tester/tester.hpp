#ifndef TESTER_HPP
# define TESTER_HPP

/*
**		utils	**
*/

# define RESET			"\033[0m"
# define BOLDRED		"\033[1m\033[31m"
# define BOLDGREEN		"\033[1m\033[32m"

# define EMPTY			0
# define SHORT			20
# define MEDIUM			200
# define LARGE			2000
# define EXTRA_LARGE	20000

# define NB_REPEAT		10000

/*
**		output	**
*/

bool	print_test_result(bool bl);

/*
**		time	**
*/

void	print_time_start(timeval *start);

double	timeval_diff_to_ms(timeval &start, timeval &end);

template < class CONTAINER >
void	default_construction()
{	CONTAINER	container;				}

template < class CONTAINER >
void	copy_construction(const CONTAINER &x)
{	CONTAINER	container(x);			}

template < class CONTAINER >
void	fill_construction(typename CONTAINER::size_type n, typename CONTAINER::value_type val)
{	CONTAINER	container(n, val);		}

template < class CONTAINER , class ITERATOR >
void	range_construction(ITERATOR first, ITERATOR last)
{	CONTAINER	container(first, last);	}

/*
**		tests	**
*/

bool	vector_test(bool time);
bool	stack_test();
bool	map_test(bool time_check);

/*
**		Util	**
*/

bool	recursive_call(bool (*f)(bool, int), bool time_check, int n);

#endif
