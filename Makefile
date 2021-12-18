NAME	= ft_container_tester

SRCS	= tester/main.cpp

INC		= ft_containers/Map.hpp
INC		+= ft_containers/Stack.hpp
INC		+= ft_containers/Vector.hpp
INC		+= utility/BST_tree/node.hpp
INC		+= utility/BST_tree/rb_tree.hpp
INC		+= utility/Iterators/Binary_Search_Tree_Iterator.hpp
INC		+= utility/Iterators/Iterator.hpp
INC		+= utility/Iterators/Random_Access_Iterator.hpp
INC		+= utility/Iterators/Reverse_Iterator.hpp
INC		+= utility/algorithm.hpp
INC		+= utility/functionnal.hpp
INC		+= utility/pair.hpp
INC		+= utility/type_trait.hpp

OBJ		= $(SRCS:.cpp=.o)

CC		= clang++
CFLAGS	= -std=c++98 -Wall -Werror -Wextra
GDBFLAG	= -g
RM		= rm -f
RM_DIR	= rm -rf

all:
	$(MAKE) $(NAME) --no-print-directory

%.o:%.cpp $(INC)
	$(CC) $(GDBFLAG) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

gdb:$(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME).g
	gdb $(NAME).g

clean:
	$(RM_DIR) $(OBJ)

fclean:
	$(RM_DIR) $(OBJ)
	$(RM) $(NAME)
	$(RM) $(NAME).g

re:
	$(MAKE) fclean --no-print-directory
	$(MAKE) all --no-print-directory

.PHONY:all clean fclean re
