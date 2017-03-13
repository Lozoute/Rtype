CC		= g++

RM		= rm -rf

CXXFLAGS	+= -std=c++11 -Wall -Wextra -Werror -fPIC -shared -I../../

LDFLAGS		=

NAME		= ../../../SOs/lib_API_Socket_Unix.so

SRC		= API_Socket_Unix.cpp

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
