CC		= g++

RM		= rm -rf

CXXFLAGS	+= -std=c++11 -Wall -Wextra -Werror -fPIC -shared -I../.. -I../../../API_Error/

LDFLAGS		=

NAME		= ../../../SOs/lib_API_Mutex_STD.so

SRC		= API_CondVar_STD.cpp	\
		  API_Mutex_STD.cpp

OBJS		= $(SRC:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
