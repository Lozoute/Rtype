##
## Makefile for  in /home/sabbah_j/rendu/TEK3/B5-ADVANCED-CPP/rtype/API/API_Protocol/Implementation/API_Protocol
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Wed Jul 15 01:59:06 2015 jordan sabbah
## Last update Sun Jul 26 16:31:00 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -Wextra
CXXFLAGS	+= -std=c++11 -fPIC
CXXFLAGS	+= -I../.. -I../../../API_Error
CXXFLAGS	+= -I../../../API_Loader -I../../../API_Socket_Udp

LDFLAGS		= -shared

SRCS		= ClientInfo.cpp	\
		  AProtocol.cpp		\
		  ProtocolClient.cpp	\
		  ProtocolServer.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= ../../../SOs/lib_API_Protocol.so

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(CXXFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
