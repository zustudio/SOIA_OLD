cmake_minimum_required (VERSION 3.0)

include(GenerateExportHeader)

# set options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set cflags
if(CMAKE_COMPILER_IS_GNUCXX)
	set( CMAKE_CXX_FLAGS -std=c++14)
elseif(MSVC)
	set( CMAKE_CXX_FLAGS "/EHsc /constexpr:steps4000000 /constexpr:depth50000" )
endif()
if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG 
	"${CMAKE_CXX_FLAGS_DEBUG}")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

add_subdirectory(Environment)
add_subdirectory(Supervisor)
add_subdirectory(Programs)
#add_subdirectory(Apprentice)
