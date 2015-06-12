cmake_minimum_required(VERSION 3.1)

project(ToolsCore)
	depends_on_projects(Environment Core CompileTime Text Thread Reflection)

add_PrivatePublic(
	RTool
	RToolContainer)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()