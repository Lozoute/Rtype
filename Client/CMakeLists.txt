cmake_minimum_required(VERSION 3.1)

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(RType)

set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Error"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Loader"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Mutex"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Protocol"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Thread"
	"${CMAKE_CURRENT_SOURCE_DIR}/Includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../Mobs"
	"${CMAKE_CURRENT_SOURCE_DIR}/../Mobs/attack"
	"${CMAKE_CURRENT_SOURCE_DIR}/../Ressources"
	)

add_executable(Client

	main.cpp
	Menu/LogFile
	Menu/Menu
	Menu/MenuJoin
	Menu/PauseMenu
	GameEngine/GameEngine
	Player/ship
	Window/Background
	Window/Hud
	Window/Graph
	Window/ProjArray
	Window/Ressources
	Window/Sound
	Window/Sprite
	Window/Window
	Window/WindowEvent
	Includes/Background
	Includes/GameEngine
	Includes/Graph
	Includes/Hud
	Includes/Menu
	Includes/MenuJoin
	Includes/PauseMenu
	Includes/ProjArray
	Includes/Ressources
	Includes/ship
	Includes/Sound
	Includes/Sprite
	Includes/Window
	../Mobs/AObject
	../Mobs/IObject
	../Mobs/attack/attack.cpp
	../Mobs/attack/attack.hpp
)

IF(UNIX)
	message("cmake Client for UNIX")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../Release)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	target_link_libraries(Client Threads::Threads)
	target_link_libraries(Client dl)
ENDIF(UNIX)
IF(WIN32)
	message("cmake Client for Windows")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)
ENDIF(WIN32)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")
find_package(SFML 2.2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Client ${SFML_LIBRARIES})
