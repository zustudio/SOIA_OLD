cmake_minimum_required(VERSION 3.1)

subproject(Console)
	depends_on_projects(Environment Core_E Reflection)
	depends_on_projects(Supervisor Core_S)

add_Source_and_Public(
	TConsole)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
