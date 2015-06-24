cmake_minimum_required(VERSION 3.1)

subproject(Core)

in_sub(PreProcessor)
	add_Public(Definitions)
	add_PrivatePublic(CPPExtensions)
end_sub()

auto_include_directories()
auto_export_directories()
dmessage(STATUS "[CORE] H-Files: ${PUBLIC_H_FILES}")
dmessage(STATUS "[CORE] CPP-Files: ${CPP_FILES}")
dmessage(STATUS "[CORE] Public dirs: ${PROJECT_Public_DIRS}")
auto_add_shared_library()