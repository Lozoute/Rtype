##
## Makefile for  in /home/sabbah_j/rendu/TEK3/B5-ADVANCED-CPP/rtype/API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Tue Jul 14 23:53:02 2015 jordan sabbah
## Last update Sat Jul 18 22:53:13 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -Wextra
CXXFLAGS	+= -std=c++11 -fPIC
CXXFLAGS	+= -I../.. -I../../../API_Error
CXXFLAGS	+= -I../../../API_Mutex
CXXFLAGS	+= -I../../../API_Loader

LDFLAGS		= -shared

SRCS		= Address.cpp	\
		  SocketUdp.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= ../../../SOs/lib_API_Socket_Udp_Unix.so

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ../../../API_Mutex/Implementation/API_Mutex_STD
	$(CC) $(OBJS) $(LDFLAGS) $(CXXFLAGS) -o $(NAME)

clean:
	$(MAKE) -C ../../../API_Mutex/Implementation/API_Mutex_STD clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ../../../API_Mutex/Implementation/API_Mutex_STD fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
