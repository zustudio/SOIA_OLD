cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Scripts/CMake/")
include(IncludeScripts)

project(SOIA)

add_subdirectory(ThirdParty)

if ("${THIRDPARTY_SUCCESS}" STREQUAL "TRUE")
	add_subdirectory(Source)
endif()