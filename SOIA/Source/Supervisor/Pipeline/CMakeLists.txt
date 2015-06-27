cmake_minimum_required(VERSION 3.1)

subproject(Pipeline)
	depends_on_projects(Environment Core Log Reflection)
	depends_on_projects(Supervisor ToolsCore AnalyzerCore)

in_sub(Tool)
	add_PrivatePublic(PipelineTool)
in_sub(Pipe)
	add_PrivatePublic(
		Pipe
		Port
		OutPort
		InPort)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
