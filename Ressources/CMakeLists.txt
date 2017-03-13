cmake_minimum_required(VERSION 2.6)

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(RType CXX)

set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
#	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Protocol"
#	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Loader"
#	"${CMAKE_CURRENT_SOURCE_DIR}/../API/API_Error"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

IF(UNIX)
	set(RESSOURCES "_API_Ressources")

	message("cmake Ressources for UNIX")
	set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../API/SOs")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
ENDIF(UNIX)
IF(WIN32)
	set(RESSOURCES "lib_API_Ressources")

	message("cmake Ressources ${CMAKE_CONFIGURATION_TYPES} for WINDOWS")
	set( LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../API/DLLs")
ENDIF(WIN32)

add_library(${RESSOURCES} SHARED

  Ressources.cpp
  Sound.cpp
  Sprite.cpp
  IRessources.hpp
  ISound.hpp
  ISprite.hpp
  Ressources.hpp
  Sound.hpp
  Sprite.hpp
)

IF(MSVC)
	set_target_properties( ${RESSOURCES} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
	set_target_properties( ${RESSOURCES} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH} )
	set_target_properties( ${RESSOURCES} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
endif(MSVC)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")
find_package(SFML 2.2 REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${RESSOURCES} ${SFML_LIBRARIES})
