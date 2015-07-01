cmake_minimum_required (VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/Install/ThirdParty/script/soia-cppcheck-target-cmake/")

include(GenerateExportHeader)
message(STATUS "module paths: ${CMAKE_MODULE_PATH}")

cmake_policy(VERSION 3.1)
find_package(CPPCheck)
include(CPPCheck)

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

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# set directory settings for helper macros
set(THIRDPARTY_DIRECTORY ${CMAKE_BINARY_DIR}/Install/Thirdparty)
set(WORKFLOW_DIRECTORY ${CMAKE_SOURCE_DIR}/Scripts/Workflow)

add_subdirectory(Environment)
add_subdirectory(Supervisor)
add_subdirectory(Programs)
#add_subdirectory(Apprentice)
