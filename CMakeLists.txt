# UNIX: mkdir build_unix; cd build; cmake ..; make
#
cmake_minimum_required(VERSION 3.1)

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(RType CXX)

set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11")

IF(UNIX)
	message("cmake RType for UNIX")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Release)
ENDIF(UNIX)
IF(WIN32)
	message("cmake RType for Windows")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
ENDIF(WIN32)

add_subdirectory(API/API_Mutex)
add_subdirectory(API/API_Socket_Udp)
add_subdirectory(API/API_Protocol)
add_subdirectory(Mobs)
add_subdirectory(Ressources)
add_subdirectory(Client)
add_subdirectory(Server)
