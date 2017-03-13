CC		= clang++ -g

RM		= rm -rf

CXXFLAGS	+= -Wextra -Wall -Werror -std=c++11
CXXFLAGS	+= -I./include/ -I../API/API_Loader/ -I../API/API_Thread/
CXXFLAGS	+= -I../include/ -I../API/API_Mutex/ -I../API/API_Protocol/
CXXFLAGS	+= -I../API/API_Error/

LDFLAGS		= -L/usr/local/lib -ldl -lpthread -L/usr/lib64 -lstdc++
LDFLAGS		+= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system


SRCS		= main.cpp          \
		  GraphEngine.cpp   \
	          Object.cpp        \
		  NetworkThread.cpp \
		  Background.cpp    \
		  Sprite.cpp        \
	          RessourcesV2.cpp  \
		  Explosion.cpp     \
		  Sound.cpp         \
		  DrawMap.cpp       \

OBJS		= $(SRCS:.cpp=.o)

NAME		= clientFedou


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS) fed.o

fclean:		clean
		$(RM) $(NAME) fed

re:		fclean all

.PHONY:		all server clean fclean re
