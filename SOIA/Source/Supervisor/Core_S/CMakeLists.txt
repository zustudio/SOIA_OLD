cmake_minimum_required(VERSION 3.1)

subproject(Core_S)
	depends_on_projects(Environment Core_E CompileTime Text Thread Reflection)

in_sub(Tool)
	add_Source_and_Public(
		TTool
		TMainTool
		RGUI)
in_sub(Dialogue)
	add_Source_and_Public(
		RDialogue
		RStdDialogue)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
