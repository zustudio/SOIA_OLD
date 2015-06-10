cmake_minimum_required(VERSION 3.1)

project(Graphics)
	depends_on_projects(Environment Core MathematicsCore)

in_sub(Core)
	add_PrivatePublic(
		Window_Base
		Window)
in_sub(DataStructures)
	add_PrivatePublic(
		pxPoint
		fPoint
		cPoint
		fColor
		fCanvasObject)
in_sub(Controls)
	add_PrivatePublic(
		Control
		CCanvas
		CTable
		CTextBox
		CGraph)
in_sub(Platform_Linux Linux)
	add_PrivatePublic(Window_Linux)
in_sub(Platform_Windows Windows)
	add_PrivatePublic(Window_Windows)
end_sub()

auto_include_directories()
auto_export_directories()
auto_add_shared_library()
		