cmake_minimum_required(VERSION 3.1)

subproject(Pipeline)
	depends_on_projects(Environment Core_E Text Thread Reflection)
	depends_on_projects(Supervisor Core_S)

in_sub(Tool)
	add_Source_and_Public(
		PipelineTool
		RConversionPipes)
in_sub(Pipe)
	add_Source_and_Public(
		Pipe
		Port
		OutPort
		InPort)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
