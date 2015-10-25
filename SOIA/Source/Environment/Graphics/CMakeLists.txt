cmake_minimum_required(VERSION 3.1)

subproject(Graphics)
	depends_on_projects(Environment Core_E CompileTime Time Text Thread File MathematicsCore)
	depends_on_thirdparty(glfw)
	depends_on_thirdparty(glew-cmake)
	depends_on_thirdparty(freetype2)
	depends_on_thirdparty(Simple-OpenGL-Image-Library)
	depends_on_system(Windows glu32 gdi32 opengl32)
	depends_on_system(Linux GL GLU glut)

	#depends_on_thirdparty_shared(glewd libglew_sharedd liblibglew_shared)
	#depends_on_thirdparty_static(glfw3)
	#depends_on_thirdparty_static(SOIL)
	#depends_on_thirdparty_static(freetype freetype2)
	#depends_on_system(glu32 gdi32 opengl32)

in_sub(Global)
	add_Source_and_Public(
		GlobalRenderThread
		GlobalStyle
		FreeTypeProvider)
in_sub(Header)
	add_Public(
		FreeType
		FreeTypeForwardDefinitions
		OpenGL
		OpenGLForwardDefinitions
		GLFWMacroEnums)
in_sub(DataStructures)
	add_Public(
		DataUnravelerTemplate)
	add_Source_and_Public(
		iTriangle
		iLine
		pxPoint
		pxSize
		pxMargins
		pxRectangle
		fPoint
		fColor
		EventInfo_KeyChanged
		EventInfo_MouseButtonChanged
		EventInfo_SelectionChanged)
in_sub(Hierarchy)
	add_Source_and_Public(
		MBound
		MBoundaries)
in_sub(Graphics)
	add_Public(
		VertexBufferTemplate)
	add_Source_and_Public(
		RenderThread
		RenderTarget
		GraphicsWindow
		GraphicsLayer
		GraphicsObject
		TextLayer
		TextObject
		TextStyle
		StyleSheet
		FilledGeometryLayer
		UnfilledGeometryLayer
		GeometryLayer
		GeometryObject
		Font
		GlyphObject
		Shader
		ShaderProgram
		VertexBuffer
		VertexBufferVariable
		Texture2D
		FontTexture2D)
in_sub(Control)
	add_Source_and_Public(
		GraphicsControl
		ScrollBar
		TextBox
		TextBoxLine
		TextCursor
		TextBoxDialogue
		Canvas)
in_sub(Window)
	add_Source_and_Public(
		ControlWindow
		WindowArea)
end_sub()

auto_add_shared_library()
auto_include_directories()
auto_export_directories()