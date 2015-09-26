cmake_minimum_required(VERSION 3.1)

subproject(Visualization)
	depends_on_projects(Environment Core_E)
	depends_on_projects(Supervisor Core_S)

in_sub(Tool)
	add_Source_and_Public(RGraphTool2D)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()

	