cmake_minimum_required(VERSION 3.1)

project(Pipe)
	depends_on_projects(Environment Core Reflection)
	depends_on_projects(Supervisor ToolsCore AnalyzerCore)

add_PrivatePublic(PipeTool)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()