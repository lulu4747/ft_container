FT_MAP		= ft_map_test.exe
STD_MAP		= std_map_test.exe
FT_STACK	= ft_stack_test.exe
STD_STACK	= std_stack_test.exe
FT_VECTOR	= ft_vector_test.exe
STD_VECTOR	= std_vector_test.exe

MAP_MAIN	= tester/map/map_test.cpp
STACK_MAIN	= tester/stack/stack_test.cpp
VECTOR_MAIN	= tester/vector/vector_test.cpp

INC			= ft_containers/map.hpp
INC			+= ft_containers/stack.hpp
INC			+= ft_containers/vector.hpp
INC			+= tester/map/map_test.hpp
INC			+= tester/stack/stack_test.hpp
INC			+= tester/vector/vector_test.hpp
INC			+= utility/BST_tree/node.hpp
INC			+= utility/BST_tree/rb_tree.hpp
INC			+= utility/Iterators/Binary_Search_Tree_Iterator.hpp
INC			+= utility/Iterators/Iterator.hpp
INC			+= utility/Iterators/Random_Access_Iterator.hpp
INC			+= utility/Iterators/Reverse_Iterator.hpp
INC			+= utility/algorithm.hpp
INC			+= utility/pair.hpp
INC			+= utility/type_trait.hpp

FT_SET		= ft_set_test.exe
STD_SET		= std_set_test.exe

SET_MAIN	= bonus/set_test.cpp

SET_INC		= bonus/node.hpp
SET_INC		+= bonus/rb_tree.hpp
SET_INC		+= bonus/set_test.hpp
SET_INC		+= bonus/set.hpp

CC			= clang++
CFLAGS		= -std=c++98 -Wall -Werror -Wextra
NS			= -D NS=ft
IFLAG		= -I ./ft_containers/ -I ./utility/
IFLAG_BONUS	= -I ./bonus/
RM			= rm -f
RM_DIR		= rm -rf

all:
	$(MAKE) $(FT_MAP) --no-print-directory
	$(MAKE) $(STD_MAP) --no-print-directory
	$(MAKE) $(FT_STACK) --no-print-directory
	$(MAKE) $(STD_STACK) --no-print-directory
	$(MAKE) $(FT_VECTOR) --no-print-directory
	$(MAKE) $(STD_VECTOR) --no-print-directory

map:$(MAP_MAIN) $(INC)
	$(MAKE) $(FT_MAP) --no-print-directory
	$(MAKE) $(STD_MAP) --no-print-directory

stack:$(STACK_MAIN) $(INC)
	$(MAKE) $(FT_STACK) --no-print-directory
	$(MAKE) $(STD_STACK) --no-print-directory

vector:$(VECTOR_MAIN) $(INC)
	$(MAKE) $(FT_VECTOR) --no-print-directory
	$(MAKE) $(STD_VECTOR) --no-print-directory

test:all
	./test.sh

map_test:map
	./test.sh map

stack_test:stack
	./test.sh stack

vector_test:vector
	./test.sh vector

$(FT_MAP):$(MAP_MAIN) $(INC)
	$(CC) $(CFLAGS) $(MAP_MAIN) $(NS) $(IFLAG) -o $(FT_MAP)

$(STD_MAP):$(MAP_MAIN) $(INC)
	$(CC) $(CFLAGS) $(MAP_MAIN) $(IFLAG) -o $(STD_MAP)

$(FT_STACK):$(STACK_MAIN) $(INC)
	$(CC) $(CFLAGS) $(STACK_MAIN) $(NS) $(IFLAG) -o $(FT_STACK)

$(STD_STACK):$(STACK_MAIN) $(INC)
	$(CC) $(CFLAGS) $(STACK_MAIN) $(IFLAG) -o $(STD_STACK)

$(FT_VECTOR):$(VECTOR_MAIN) $(INC)
	$(CC) $(CFLAGS) $(VECTOR_MAIN) $(NS) $(IFLAG) -o $(FT_VECTOR)

$(STD_VECTOR):$(VECTOR_MAIN) $(INC)
	$(CC) $(CFLAGS) $(VECTOR_MAIN) $(IFLAG) -o $(STD_VECTOR)

bonus:
	$(MAKE) $(FT_SET) --no-print-directory
	$(MAKE) $(STD_SET) --no-print-directory

bonus_test:bonus
	./test.sh set

$(FT_SET):$(INC) $(SET_INC) $(SET_MAIN)
	$(CC) $(CFLAGS) $(SET_MAIN) $(NS) $(IFLAG) $(IFLAG_BONUS) -o $(FT_SET)

$(STD_SET):$(SET_MAIN) $(INC)
	$(CC) $(CFLAGS) $(SET_MAIN) $(IFLAG) $(IFLAG_BONUS) -o $(STD_SET)

clean:

fclean:
	$(MAKE) clean
	$(RM) $(FT_MAP)
	$(RM) $(STD_MAP)
	$(RM) $(FT_STACK)
	$(RM) $(STD_STACK)
	$(RM) $(FT_VECTOR)
	$(RM) $(STD_VECTOR)
	$(RM) $(FT_SET)
	$(RM) $(STD_SET)
	$(RM) *.out

re:
	$(MAKE) fclean --no-print-directory
	$(MAKE) all --no-print-directory

.PHONY:all map stack vector test map_test stack_test vector_test bonus bonus_test clean fclean re
