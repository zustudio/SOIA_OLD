cmake_minimum_required(VERSION 3.1)

subproject(OS)
	depends_on_projects(Environment Core_E Text Reflection File)
	depends_on_projects(Supervisor Core_S Equation Pipeline Visualization Console ElementExplorer BlackBoard)

in_sub(Runtime)
	add_Source_and_Public(
		PersistentRuntime
		TRuntime)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()