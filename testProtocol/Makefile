##
## Makefile for  in /home/sabbah_j/rendu/TEK3/B5-ADVANCED-CPP/rtype/testProtocol
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Fri Jul 17 00:34:54 2015 jordan sabbah
## Last update Sun Jul 19 19:13:41 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -std=c++11 -I../API/API_Loader -I../API/API_Error -I../API/API_Protocol -g3

LDFLAGS		= -ldl

SRCS		= main.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME	= a.out

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix all
	$(MAKE) -C ../API/API_Protocol/Implementation/API_Protocol all
	$(CC) $(OBJS) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix clean
	$(MAKE) -C ../API/API_Protocol/Implementation/API_Protocol clean

fclean: clean
	$(MAKE) -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix fclean
	$(MAKE) -C ../API/API_Protocol/Implementation/API_Protocol fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
