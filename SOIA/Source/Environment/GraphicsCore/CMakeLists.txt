cmake_minimum_required(VERSION 3.1)

subproject(GraphicsCore)
	depends_on_projects(Environment Core Log Thread)
	depends_on_thirdparty_shared(glewd libglew_sharedd liblibglew_shared)
	depends_on_thirdparty_static(glfw3)
	depends_on_system(glu32 gdi32 opengl32)

in_sub(Graphics)
	add_PrivatePublic(
		GraphicsWindow
		RenderThread
		GraphicsLayer
		Shader
		VertexBuffer)
in_sub(Global)
	add_PrivatePublic(
		RenderThreadProvider)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()