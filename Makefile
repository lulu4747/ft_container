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
INC		+= utility/less.hpp
INC		+= utility/pair.hpp
INC		+= utility/type_trait.hpp

OBJ		= $(SRCS:.cpp=.o)

CC		= clang++
CFLAGS	= -std=c++98 -Wall -Werror -Wextra
RM		= rm -f
RM_DIR	= rm -rf

all:
	$(MAKE) $(NAME) --no-print-directory

%.o:%.cpp $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM_DIR) $(OBJ)

fclean:
	$(RM_DIR) $(OBJ)
	$(RM) $(NAME)

re:
	$(MAKE) fclean --no-print-directory
	$(MAKE) all --no-print-directory

.PHONY:all clean fclean re
