cmake_minimum_required(VERSION 3.1)

subproject(Log)
	depends_on_projects(Environment Core_E Text Time)

in_sub(Logger)
	add_PrivatePublic(Logger)
in_sub(Global)
	add_PrivatePublic(LogProvider)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
