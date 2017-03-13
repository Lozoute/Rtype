cmake_minimum_required(VERSION 3.1)

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(RType CXX)

set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Error"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Loader"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Mutex"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Protocol"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Thread"
	"${CMAKE_CURRENT_SOURCE_DIR}/Include"
	)

add_executable(Server
	Include/AObject
	Include/BonusGenerator
	Include/GameEngine
	Include/Game
	Include/GreenArmor
	Include/HealthPack
	Include/LittleShip
	Include/Missile
	Include/MobGenerator
	Include/Player
	Include/PlayerShip
	Include/RedArmor
	Include/Server
	Include/ShipMob
	Include/Tentacle
	Bonus/DamageBooster
	Bonus/FireRateBooster
	Bonus/HealthPack
	GameEngine/BonusGenerator
	GameEngine/Game
	GameEngine/GameCMDS
	GameEngine/GameEngine
	GameEngine/MobGenerator
	Mobs/Centiped
	Mobs/GreenArmor
	Mobs/LittleShip
	Mobs/RedArmor
	Mobs/ShipMob
	Mobs/Tentacle
	Objects/AObject
	Objects/Missile
	Player/Player
	Player/PlayerShip
	Server/Server
	main
)

IF(UNIX)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  target_link_libraries(Server Threads::Threads)
  target_link_libraries(Server dl)
  message("cmake Server for UNIX")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../Release)
ENDIF(UNIX)

IF(WIN32)
	message("cmake Server for Windows")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)
ENDIF(WIN32)
