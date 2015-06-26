cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Scripts/CMake/")
include(IncludeScripts)

project(SOIA)

option( BUILD_SOIA "OFF => Builds thirdparty dependencies. ON => Builds SOIA." OFF)
if ("${BUILD_SOIA}" STREQUAL "ON")
	add_subdirectory(Source)
else()
	add_subdirectory(ThirdParty)
endif()