cmake_minimum_required (VERSION 2.6)
include(${CMAKE_SOURCE_DIR}/Scripts/CMake/IncludeScripts.txt)

# set cflags
set( CMAKE_CXX_FLAGS -std=c++11)

# set default directories
set( CMAKE_INSTALL_PREFIX ../Install/)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries )
set_property( GLOBAL PROPERTY USE_FOLDERS ON)

#enable_dmessage()

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

add_subdirectory(Environment)
add_subdirectory(Supervisor)
#add_subdirectory(Apprentice)
#add_subdirectory(Programs)