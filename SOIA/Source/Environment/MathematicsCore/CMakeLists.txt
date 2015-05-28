cmake_minimum_required(VERSION 3.1)

project(MathematicsCore)

in_sub(TEST)
	add_PrivatePublic(add)
in_sub(Random)
	add_PrivatePublic(Random)
end_sub()

auto_include_directories()
auto_add_shared_library()
auto_export_directories()