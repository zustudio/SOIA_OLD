cmake_minimum_required(VERSION 3.1)

subproject(File)
	depends_on_projects(Environment Reflection Log)

add_PrivatePublic(
	File_DEPRECATED
	FileObject
	FileObjectFactory
	PropertyTag
	PropertyTagFactory
	SaveFile
	TextFile)
in_sub(System)
	add_PrivatePublic(
		FileSystem
		CommonFileSytemAccess
		File
		Directory
		Path)
in_sub(Platform_Linux Linux)
	add_PrivatePublic(
		LinuxFileSystemAccess)
in_sub(Platform_Windows Windows)
	add_Public(
		dirent)
	add_PrivatePublic(
		WindowsFileSystemAccess)
in_sub(Global)
	add_PrivatePublic(FileSystemProvider)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
