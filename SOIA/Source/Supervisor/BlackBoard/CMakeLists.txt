cmake_minimum_required(VERSION 3.1)

subproject(BlackBoard)
	depends_on_projects(Environment Graphics)
	depends_on_projects(Supervisor Core_S)

in_sub(Tool)
	add_Source_and_Public(TBlackBoard)
in_sub(UserInterface)
	add_Source_and_Public(BlackBoardWindow)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()