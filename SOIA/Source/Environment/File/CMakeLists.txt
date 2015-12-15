cmake_minimum_required(VERSION 3.1)

subproject(File)
	depends_on_projects(Environment Reflection Text)

in_sub(Global)
	add_Source_and_Public(FileSystemProvider)
in_sub(System)
	add_Source_and_Public(
		FileSystem
		CommonFileSytemAccess
		File
		IOFile
		Directory
		Path)
in_sub(Platform_Linux Linux)
	add_Source_and_Public(
		TEST LinuxFileSystemAccess)
in_sub(Platform_Windows Windows)
	add_Public(
		dirent)
	add_Source_and_Public(
		WindowsFileSystemAccess)
in_sub(Serialization)
	add_Source_and_Public(
		ElementFile
		ElementTokenizer)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()
