CC	 = g++

RM	 = rm -rf

CXXFLAGS = -Wall -Werror -Wextra -std=c++11 -fPIC -shared

LDFLAGS	 = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

SRCS	 = Ressources.cpp	\
	   Sound.cpp		\
	   Sprite.cpp

OBJS	 = $(SRCS:.cpp=.o)

NAME	 = ../API/SOs/lib_API_Ressources.so

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
