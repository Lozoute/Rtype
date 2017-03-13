CC		= g++

RM		= rm -rf

CXXFLAGS	+= -std=c++11 -Wall -Wextra -Werror -I../../.. -I../../../../API_Error/
CXXFLAGS	+=  -I..

LDFLAGS		= -lpthread

NAME		= a.out

SRC		= ../API_CondVar_STD.cpp						\
		  ../../../../API_Mutex/Implementation/API_Mutex_STD/API_Mutex_STD.cpp	\
		  main.cpp

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
