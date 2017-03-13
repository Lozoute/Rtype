CC	 = g++

RM	 = rm -rf

CXXFLAGS =  -I.. -I../../Ressources
CXXFLAGS += -I../../API/API_Protocol
CXXFLAGS += -I../../API/API_Loader
CXXFLAGS += -I../../API/API_Error
CXXFLAGS += -Wall -Werror -Wextra -std=c++11 -fPIC -shared

LDFLAGS	 = -lsfml-graphics -lsfml-window -lsfml-system

SRCS	 = attack.cpp

OBJS	 = $(SRCS:.cpp=.o)

NAME	 = ../../API/SOs/lib_API_attack.so

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
