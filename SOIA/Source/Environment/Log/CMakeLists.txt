cmake_minimum_required(VERSION 3.1)

project(Log)
	depends_on_projects(Environment Core Text Time)

in_sub(Logger)
	add_PrivatePublic(Logger)
in_sub(Global)
	add_PrivatePublic(LogProvider)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()