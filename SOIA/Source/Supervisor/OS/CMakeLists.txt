cmake_minimum_required(VERSION 3.1)

subproject(OS)
	depends_on_projects(Environment Core Text Reflection File)
	depends_on_projects(Supervisor ToolsCore Pipeline Visualization Console ElementExplorer)

in_sub(Runtime)
	add_PrivatePublic(
		PersistentRuntime
		TRuntime)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()