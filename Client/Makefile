CC		= g++

RM		= rm -f

CXXFLAGS	+= -Wextra -Wall -Werror -std=c++11
CXXFLAGS	+= -I../API/API_Loader -I./Includes/ -I../Includes/
CXXFLAGS	+= -I../API/API_Error -I../API/API_Mutex
CXXFLAGS	+= -I../API/API_Thread -I../API/API_Protocol
CXXFLAGS	+= -I/usr/local/include
CXXFLAGS	+= -I../Mobs
CXXFLAGS	+= -I../Ressources

LDFLAGS		= -L/usr/local/lib -ldl -lpthread -L/usr/lib64 -lstdc++
LDFLAGS		+= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

NAME		= client.exe

SRCS		= main.cpp \
		  Window/Window.cpp \
		  Window/WindowEvent.cpp \
		  Window/Background.cpp \
		  Window/Graph.cpp \
		  Window/ProjArray.cpp \
		  Window/Hud.cpp \
		  GameEngine/GameEngine.cpp \
		  Player/ship.cpp \
		  Menu/Menu.cpp \
		  Menu/MenuJoin.cpp \
		  Menu/LogFile.cpp \
		  Menu/PauseMenu.cpp

OBJS		= $(SRCS:.cpp=.o)


all:		$(NAME)

$(NAME):	$(OBJS)
		$(MAKE) -C ../Mobs all
		$(MAKE) -C ../Ressources all
		$(MAKE) -C ../API/API_Protocol/Implementation/API_Protocol all
		$(MAKE) -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix all
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)


client:		$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)

clean:
		$(MAKE) -C ../Mobs clean
		$(MAKE) -C ../Ressources clean
		$(MAKE) -C ../API/API_Protocol/Implementation/API_Protocol clean
		$(MAKE) -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix clean
		$(RM) $(OBJS)

fclean:
		$(MAKE) -C ../Mobs fclean
		$(MAKE) -C ../Ressources fclean
		$(MAKE) -C ../API/API_Protocol/Implementation/API_Protocol fclean
		$(MAKE) -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix fclean
		$(RM) $(OBJS) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
