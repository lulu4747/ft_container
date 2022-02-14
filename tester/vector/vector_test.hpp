#ifndef VECTOR_TEST_HPP
# define VECTOR_TEST_HPP

# include "../tester.hpp"
# include "../../ft_containers/vector.hpp"

std::vector<int>	get_random_vector(size_t n);

void	get_identical_random_filled_vectors(size_t n, ft::vector<int> *ft, std::vector<int> *stl);

bool	recursive_call(bool (*f)(bool, int), bool time_check, int n);

template < class FTV, class STLV >
bool	content_compare(FTV &ft, STLV &stl)
{
	typename FTV::iterator	ftit(ft.begin());
	typename STLV::iterator	stlit(stl.begin());

	while (ftit != ft.end() && stlit != stl.end())
	{
		if (*ftit != *stlit)
			return false;
		ftit++;
		stlit++;
	}
	if (ftit != ft.end() || stlit != stl.end())
		return false;
	return true;
}

template < class FT, class STL >
bool	attributes_compare(FT &ft, STL &stl)
{
	bool	empty, max_size, size, capacity, content;

	std::cout << "empty() comparison :	";
	empty = print_test_result(ft.empty() == stl.empty());
	std::cout << "max_size() comparison :	";
	max_size = print_test_result(ft.max_size() == stl.max_size());
	std::cout << "size() comparison :	";
	size = print_test_result(ft.size() == stl.size());
	std::cout << "capacity() comparison :	";
	capacity = print_test_result(ft.capacity() == stl.capacity());
	std::cout << "content comparison : 	";
	content = print_test_result(content_compare(ft, stl));
	std::cout << "General comparison : 			";
	if (!empty || !max_size || !size || !capacity || !content)
		return false;
	return true;
}

#endif
