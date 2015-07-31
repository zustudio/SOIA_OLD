cmake_minimum_required(VERSION 3.1)

subproject(ElementExplorer)
	depends_on_projects(Environment Core_E Reflection)
	depends_on_projects(Supervisor Core_S)

add_PrivatePublic(TElementExplorer)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
