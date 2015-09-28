cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Scripts/CMake/")
include(IncludeScripts)
include(ExternalProject)
include(CMakeParseArguments)

project(SOIA)

# set default directories
set( CMAKE_INSTALL_PREFIX ../Install/)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries )

# set directory settings for helper macros
set(THIRDPARTY_DIRECTORY ${CMAKE_BINARY_DIR}/Install/Thirdparty)
set(WORKFLOW_DIRECTORY ${CMAKE_SOURCE_DIR}/Scripts/Workflow)
if(MSVC)
	set(BINARY_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
else()
	set(BINARY_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
file(MAKE_DIRECTORY "${BINARY_DIRECTORY}")

# add subdirectories
dmessage(STATUS "generating ThirdParty")
add_subdirectory(ThirdParty)
dmessage(STATUS "generating Source")
add_subdirectory(Source)
dmessage(STATUS "generating Documentation")
add_subdirectory(Documentation)

uacrequest_subdirectory_link(Projects "${CMAKE_CURRENT_SOURCE_DIR}/Projects")
uacrequest_subdirectory_link(Resources "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
execute_uacrequests()