cmake_minimum_required(VERSION 3.1)

project(SOIAvisor)
	depends_on_projects(Environment MathematicsCore)

add_Private(main)
end_sub()

auto_include_directories()
auto_add_executable()