cmake_minimum_required (VERSION 2.6)
include(GenerateExportHeader)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Scripts/CMake/")
include(IncludeScripts)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Scripts/CMake/cppcheck-target-cmake/")
set(CPPCHECK_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/../ThirdParty/cppcheck-1.69")
message(STATUS "cppcheck path: ${CPPCHECK_SEARCH_PATHS}")
find_package(CPPCheck)
include(CPPCheck)

project(SOIA)

# set cflags
if(CMAKE_COMPILER_IS_GNUCXX)
	set( CMAKE_CXX_FLAGS -std=c++14)
elseif(MSVC14)
	set( CMAKE_CXX_FLAGS "/EHsc /constexpr:steps4000000 /constexpr:depth50000" )
endif()
if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG 
	"${CMAKE_CXX_FLAGS_DEBUG}")
endif()

# set default directories
set( CMAKE_INSTALL_PREFIX ../Install/)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries )

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set_property( GLOBAL PROPERTY USE_FOLDERS ON)

enable_dmessage()

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

add_subdirectory(Environment)
add_subdirectory(Supervisor)
add_subdirectory(Programs)
#add_subdirectory(Apprentice)
