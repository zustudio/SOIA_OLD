cmake_minimum_required(VERSION 3.1)

subproject(Core_E)
	depends_on_projects(Environment CompileTime)

in_sub(PreProcessor)
	add_Public(Definitions)
	add_PrivatePublic(CPPExtensions)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()