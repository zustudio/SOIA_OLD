cmake_minimum_required(VERSION 3.1)

project(Text)
	depends_on_projects(Environment Core)

add_PrivatePublic(
	StdDialogue
	FileDialogue)
add_Public(
	DialogueInterface)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()