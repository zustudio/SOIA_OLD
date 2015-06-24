cmake_minimum_required(VERSION 3.1)

subproject(CompileTime)

in_sub(Generic)
	add_Public(
		IndexPack
		ConstExprDynamicList)
in_sub(Number)
	add_Public(
		Vector4Int
		Vector8Int
		IntExpressions)
in_sub(String)
	add_Public(
		CharArrayLiteral
		CharReplacer)
in_sub(Type)
	add_Public(
		TypeCharArrayLiteral)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_headeronly_library()


#add_custom_target(${PROJECT_NAME} SOURCES ${PUBLIC_H_FILES})
#set_target_properties(${PROJECT_NAME} PROPERTIES SOURCES )