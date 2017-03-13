cmake_minimum_required(VERSION 2.6)

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
project(RType CXX)

set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API_Error"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API_Loader"
	"${CMAKE_CURRENT_SOURCE_DIR}/../API_Mutex"
	)

IF(UNIX)
	set(LIBNAME "_API_Socket_Udp_Unix")
	set(LIBFOLDER "API_Socket_Udp_Unix")
	message("cmake ${LIBNAME} for UNIX")
	set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SOs")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
ENDIF(UNIX)
IF(WIN32)
	link_libraries(ws2_32.lib)
	set(LIBNAME "lib_API_Socket_Udp_Windows")
	set(LIBFOLDER "API_Socket_Udp_Windows")
	message("cmake ${LIBNAME} ${CMAKE_CONFIGURATION_TYPES} for WINDOWS")
	set( LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../DLLs")
ENDIF(WIN32)

add_library(${LIBNAME} SHARED
	API_Socket_Udp
	Implementation/${LIBFOLDER}/Address
	Implementation/${LIBFOLDER}/SocketUdp
)
IF(MSVC)
    set_target_properties( ${LIBNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH} )
    set_target_properties( ${LIBNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH} )
    set_target_properties( ${LIBNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH} )
endif(MSVC)