cmake_minimum_required(VERSION 3.1)

subproject(GraphicsCore)
	depends_on_projects(Environment Core_E CompileTime Text Thread MathematicsCore)
	depends_on_thirdparty_shared(glewd libglew_sharedd liblibglew_shared)
	depends_on_thirdparty_static(glfw3)
	depends_on_thirdparty_static(SOIL)
	depends_on_thirdparty_static(freetype freetype2)
	depends_on_system(glu32 gdi32 opengl32)

in_sub(Global)
	add_PrivatePublic(
		RenderThreadProvider
		FreeTypeProvider)
in_sub(Header)
	add_Public(
		FreeType
		FreeTypeForwardDefinitions
		OpenGL
		OpenGLForwardDefinitions)
in_sub(DataStructures)
	add_Public(
		DataUnravelerTemplate)
	add_PrivatePublic(
		fPoint
		fColor)
in_sub(Graphics)
	add_Public(
		VertexBufferTemplate)
	add_PrivatePublic(
		GraphicsWindow
		RenderThread
		GraphicsLayer
		GraphicsTextLayer
		Font
		TextObject
		GlyphObject
		Shader
		ShaderProgram
		VertexBuffer
		VertexBufferVariable
		Texture2D
		FontTexture2D)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()