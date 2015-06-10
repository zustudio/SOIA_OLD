cmake_minimum_required(VERSION 3.1)

project(Time)
	depends_on_projects(Environment Core)

add_PrivatePublic(CurrentTime)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()