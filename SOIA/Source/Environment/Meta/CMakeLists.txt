cmake_minimum_required(VERSION 3.1)

project(Meta)

add_Public(
	ConstExprList
	StringParser
	ConstExprByteParser)
end_sub()

auto_include_directories()
auto_export_directories()

add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_H_FILES})
#set_target_properties(${PROJECT_NAME} PROPERTIES SOURCES )