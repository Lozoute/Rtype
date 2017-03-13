cmake_minimum_required(VERSION 2.6)

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(RType CXX)

set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API_Error"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API_Loader"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API_Socket_Udp"
	)

IF(UNIX)
	set(LIBNAME "_API_Protocol")
	message("cmake ${LIBNAME} for UNIX")
	set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SOs")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
ENDIF(UNIX)
IF(WIN32)
	set(LIBNAME "lib_API_Protocol")
	message("cmake ${LIBNAME} ${CMAKE_CONFIGURATION_TYPES} for WINDOWS")
	set( LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../DLLs")
ENDIF(WIN32)

add_library(${LIBNAME} SHARED
	API_Protocol
	Srtp
	Implementation/API_Protocol/Header
	Implementation/API_Protocol/Packet
	Implementation/API_Protocol/SrtpLight
	Implementation/API_Protocol/AckQueue
	Implementation/API_Protocol/AProtocol
	Implementation/API_Protocol/ClientInfo
	Implementation/API_Protocol/ProtocolClient
	Implementation/API_Protocol/ProtocolServer
)
IF(MSVC)
    set_target_properties( ${LIBNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
    set_target_properties( ${LIBNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH} )
    set_target_properties( ${LIBNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
endif(MSVC)