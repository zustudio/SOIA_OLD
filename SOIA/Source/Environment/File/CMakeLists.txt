cmake_minimum_required(VERSION 3.1)

subproject(File)
	depends_on_projects(Environment Reflection Log)

add_PrivatePublic(
	File
	FileObject
	FileObjectFactory
	PropertyTag
	PropertyTagFactory
	SaveFile
	TextFile)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()