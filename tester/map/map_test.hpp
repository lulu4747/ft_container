#ifndef MAP_TEST_HPP
# define MAP_TEST_HPP

#ifndef NS //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <vector>
	#include <utility>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <vector.hpp>
	#include <algorithm.hpp>
	#include <pair.hpp>
	#include <functionnal.hpp>
	#include <type_trait.hpp>
#endif

# include <iostream>
# include <stdlib.h>

#ifndef SEED
	# define SEED 10
#endif

#ifndef LEN
	# define LEN rand()	%	1000000000
#endif

#endif