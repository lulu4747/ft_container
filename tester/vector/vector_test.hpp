#ifndef VECTOR_TEST_HPP
# define VECTOR_TEST_HPP

# include "../tester.hpp"
# include "../../ft_containers/vector.hpp"

/*
**			Setup Functions								**
*/

std::vector<int>	get_random_vector(size_t n);

void	get_identical_random_filled_vectors(size_t n,
			ft::vector<int> *ft, std::vector<int> *stl);

void	get_crescent_filled_vectors(size_t n,
			ft::vector<int> *ft, std::vector<int> *stl);

/*
**			Compare Functions				**
*/

bool	content_compare(ft::vector<int> &ft, std::vector<int> &stl);
bool	vector_compare(ft::vector<int> &ft, std::vector<int> &stl);

/*
**			Execution Time Functions					**
*/

void	begin(ft::vector<int> &vec);
void	begin(std::vector<int> &vec);
void	begin_to_end(ft::vector<int> &vec);
void	begin_to_end(std::vector<int> &vec);
void	end_to_begin(ft::vector<int> &vec);
void	end_to_begin(std::vector<int> &vec);
void	rbegin(ft::vector<int> &vec);
void	rbegin(std::vector<int> &vec);
void	rbegin_to_rend(ft::vector<int> &vec);
void	rbegin_to_rend(std::vector<int> &vec);
void	rend_to_rbegin(ft::vector<int> &vec);
void	rend_to_rbegin(std::vector<int> &vec);

bool	iterator_time_check(void (*ft_func)(ft::vector<int> &), void (*stl_func)(std::vector<int> &),
			ft::vector<int> &ft, std::vector<int> &stl);

/*
**			Utils										**
*/

bool	recursive_call(bool (*f)(bool, int), bool time_check, int n);
bool	at_try_catch(ft::vector<int> &ft, std::vector<int> &stl);

#endif
