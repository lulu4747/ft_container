FT_MAP		= ft_map_test.exe
STD_MAP		= std_map_test.exe
FT_STACK	= ft_stack_test.exe
STD_STACK	= std_stack_test.exe
FT_VECTOR	= ft_vector_test.exe
STD_VECTOR	= std_vector_test.exe

SRC_MAP		= tester/map/map_test.cpp
SRC_STACK	= tester/stack/stack_test.cpp
SRC_VECTOR	= tester/vector/vector_test.cpp

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

CC			= clang++
CFLAGS		= -std=c++98 -Wall -Werror -Wextra
NS			= -D NS=ft
IFLAG		= -I ./ft_containers/ -I ./utility/
RM			= rm -f
RM_DIR		= rm -rf

all:
	$(MAKE) $(FT_MAP) --no-print-directory
	$(MAKE) $(STD_MAP) --no-print-directory
	$(MAKE) $(FT_STACK) --no-print-directory
	$(MAKE) $(STD_STACK) --no-print-directory
	$(MAKE) $(FT_VECTOR) --no-print-directory
	$(MAKE) $(STD_VECTOR) --no-print-directory

map:$(SRC_MAP) $(INC)
	$(MAKE) $(FT_MAP) --no-print-directory
	$(MAKE) $(STD_MAP) --no-print-directory
	./test.sh map

stack:$(SRC_STACK) $(INC)
	$(MAKE) $(FT_STACK) --no-print-directory
	$(MAKE) $(STD_STACK) --no-print-directory
	./test.sh stack

vector:$(SRC_VECTOR) $(INC)
	$(MAKE) $(FT_VECTOR) --no-print-directory
	$(MAKE) $(STD_VECTOR) --no-print-directory
	./test.sh vector

test:all
	./test.sh

$(FT_MAP):$(SRC_MAP) $(INC)
	$(CC) $(CFLAGS) $(SRC_MAP) $(NS) $(IFLAG) -o $(FT_MAP)

$(STD_MAP):$(SRC_MAP) $(INC)
	$(CC) $(CFLAGS) $(SRC_MAP) $(IFLAG) -o $(STD_MAP)

$(FT_STACK):$(SRC_STACK) $(INC)
	$(CC) $(CFLAGS) $(SRC_STACK) $(NS) $(IFLAG) -o $(FT_STACK)

$(STD_STACK):$(SRC_STACK) $(INC)
	$(CC) $(CFLAGS) $(SRC_STACK) $(IFLAG) -o $(STD_STACK)

$(FT_VECTOR):$(SRC_VECTOR) $(INC)
	$(CC) $(CFLAGS) $(SRC_VECTOR) $(NS) $(IFLAG) -o $(FT_VECTOR)

$(STD_VECTOR):$(SRC_VECTOR) $(INC)
	$(CC) $(CFLAGS) $(SRC_VECTOR) $(IFLAG) -o $(STD_VECTOR)

clean:

fclean:
	$(MAKE) clean
	$(RM) $(FT_MAP)
	$(RM) $(FT_MAP).g
	$(RM) $(STD_MAP)
	$(RM) $(STD_MAP).g
	$(RM) $(FT_STACK)
	$(RM) $(FT_STACK).g
	$(RM) $(STD_STACK)
	$(RM) $(STD_STACK).g
	$(RM) $(FT_VECTOR)
	$(RM) $(FT_VECTOR).g
	$(RM) $(STD_VECTOR)
	$(RM) $(STD_VECTOR).g
	$(RM) *.out

re:
	$(MAKE) fclean --no-print-directory
	$(MAKE) all --no-print-directory

.PHONY:all map stack vector test clean fclean re
