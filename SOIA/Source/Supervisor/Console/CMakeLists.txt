cmake_minimum_required(VERSION 3.1)

subproject(Console)
	depends_on_projects(Environment Core Reflection)
	depends_on_projects(Supervisor ToolsCore)

add_PrivatePublic(
	ConsoleWorker)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
