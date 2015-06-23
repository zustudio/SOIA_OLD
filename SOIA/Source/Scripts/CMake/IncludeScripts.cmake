cmake_minimum_required(VERSION 3.1)
include(${CMAKE_CURRENT_LIST_DIR}/ListOperations.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Logging.txt)
include(${CMAKE_CURRENT_LIST_DIR}/ProjectHelpers.txt)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cppcheck-target-cmake/")
set(CPPCHECK_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/../ThirdParty/cppcheck-1.69")
message(STATUS "cppcheck path: ${CPPCHECK_SEARCH_PATHS}")
find_package(CPPCheck)