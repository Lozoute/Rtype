CC		= g++

RM		= rm -rf

CXXFLAGS	+= -Wextra -Wall -Werror -std=c++11
CXXFLAGS	+= -I./Include/ -I../API/API_Loader/ -I../API/API_Thread/
CXXFLAGS	+= -I../Include/ -I../API/API_Mutex/ -I../API/API_Protocol/
CXXFLAGS	+= -I../API/API_Error/ -I../API/API_CondVar/

LDFLAGS		= -ldl -lpthread

SRCS		= main.cpp			\
		  Server/Server.cpp		\
		  GameEngine/GameEngine.cpp	\
		  GameEngine/Game.cpp		\
		  GameEngine/GameCMDS.cpp	\
		  GameEngine/MobGenerator.cpp	\
		  GameEngine/BonusGenerator.cpp	\
		  Player/Player.cpp		\
		  Player/PlayerShip.cpp		\
		  Objects/AObject.cpp		\
		  Objects/Missile.cpp		\
		  Mobs/ShipMob.cpp		\
		  Mobs/GreenArmor.cpp		\
		  Mobs/LittleShip.cpp		\
		  Mobs/Tentacle.cpp             \
		  Mobs/RedArmor.cpp		\
		  Mobs/Centiped.cpp		\
		  Mobs/MecaCrab.cpp		\
		  Mobs/Crab.cpp			\
		  Bonus/HealthPack.cpp		\
		  Bonus/FireRateBooster.cpp	\
		  Bonus/DamageBooster.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= server.exe


all:		$(NAME) lib

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

lib:
		make -C ../API/API_Protocol/Implementation/API_Protocol/
	 	make -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix/
clean:
		$(RM) $(OBJS) fed.o
		make clean -C ../API/API_Protocol/Implementation/API_Protocol/
	 	make clean -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix/

fclean:		clean
		$(RM) $(NAME) fed
		make fclean -C ../API/API_Protocol/Implementation/API_Protocol/
	 	make fclean -C ../API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix/

re:		fclean all

.PHONY:		all server clean fclean re
