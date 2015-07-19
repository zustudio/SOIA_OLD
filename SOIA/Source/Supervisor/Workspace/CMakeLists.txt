cmake_minimum_required(VERSION 3.1)

subproject(Workspace)
	depends_on_projects(Environment Core Text Reflection File)
	depends_on_projects(Supervisor ToolsCore Pipeline Visualization)

in_sub(Main)
	add_PrivatePublic(
		Workspace)
in_sub(Tool)
	add_PrivatePublic(
		RWorkspaceTool)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()