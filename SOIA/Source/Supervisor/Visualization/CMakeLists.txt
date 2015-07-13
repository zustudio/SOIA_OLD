cmake_minimum_required(VERSION 3.1)

subproject(Visualization)
	depends_on_projects(Environment Core)
	depends_on_projects(Supervisor ToolsCore)

in_sub(Tool)
	add_PrivatePublic(RGraphTool2D)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()

	