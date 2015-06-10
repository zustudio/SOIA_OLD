cmake_minimum_required(VERSION 3.1)

project(ToolsCore)
	depends_on_projects(Environment Core Thread Reflection)

add_PrivatePublic(
	Application
	Service)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()