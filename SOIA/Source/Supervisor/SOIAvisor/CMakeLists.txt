cmake_minimum_required(VERSION 3.1)

project(SOIAvisor)
	depends_on_projects(Environment Reflection MathematicsCore Meta)

add_Private(main)
add_PrivatePublic(Testing)
end_sub()

auto_include_directories()
auto_add_executable()