cmake_minimum_required(VERSION 3.1)

subproject(GraphicsTest)
	depends_on_projects(Environment Core_E File Graphics)
	#depends_on_thirdparty_shared(glewd libglew_sharedd liblibglew_shared)
	#depends_on_thirdparty_static(glfw3)
	#depends_on_system(glu32 gdi32 opengl32)

add_Source(Main)
add_Source_and_Public(TestWindow)
end_sub()

auto_add_executable()
auto_include_directories()
auto_export_directories()