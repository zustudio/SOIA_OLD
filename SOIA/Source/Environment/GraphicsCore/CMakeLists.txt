cmake_minimum_required(VERSION 3.1)

subproject(GraphicsCore)
	depends_on_projects(Environment Core CompileTime Log Thread)
	depends_on_thirdparty_shared(glewd libglew_sharedd liblibglew_shared)
	depends_on_thirdparty_static(glfw3)
	depends_on_thirdparty_static(SOIL)
	depends_on_system(glu32 gdi32 opengl32)

in_sub(Graphics)
	add_Public(
		VertexBufferTemplate
		DataUnravelerTemplate)
	add_PrivatePublic(
		GraphicsWindow
		RenderThread
		GraphicsLayer
		Shader
		ShaderProgram
		VertexBuffer
		VertexBufferVariable
		Texture2D)
in_sub(Global)
	add_PrivatePublic(
		RenderThreadProvider)
in_sub(Header)
	add_Public(
		OpenGL
		OpenGLForwardDefinitions)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()