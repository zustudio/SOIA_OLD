cmake_minimum_required(VERSION 3.1)

# prepare thirdparty build
make_thirdparty_directories()

add_thirdparty_project(
	NAME glfw
	INCLUDE_FOLDER GLFW
	STATIC_LIB glfw3)
#add_thirdparty_project(
#	NAME soia-glew-cmake
#	INCLUDE_FOLDER GL
#	SHARED_IMPLIB libglew_sharedd.lib
#	SHARED_LIB glewd.dll)
add_thirdparty_project(
	NAME glew-cmake
	INCLUDE_FOLDER GL
	SHARED_IMPLIB glewmx
	SHARED_LIB glewmx)
add_thirdparty_project(
	NAME freetype2
	INCLUDE_FOLDER freetype2
	STATIC_LIB freetype
	#	CMAKE_ARGS "-DBUILD_SHARED_LIBS:BOOL=true")
	CMAKE_ARGS "-DCMAKE_C_FLAGS:string=-fPIC")
add_thirdparty_project(
	NAME Simple-OpenGL-Image-Library
	INCLUDE_FOLDER SOIL
	STATIC_LIB SOIL
	CMAKE_ARGS "-DCMAKE_C_FLAGS:string=-fPIC")
add_thirdparty_project(
	NAME unittest-cpp
	INCLUDE_FOLDER UnitTest++
	STATIC_LIB UnitTest++
	)

# generate build scripts
#generate_build_script_cmake(unittest-cpp)
#generate_build_script_cmake(glfw -DGLFW_USE_HYBRID_HPG=ON)
#generate_build_script_cmake(soia-glew-cmake)
#generate_build_script_cmake(Simple-OpenGL-Image-Library)
#generate_build_script_cmake(freetype2)

# register scripts
#add_thirdparty_script_build(freetype2)
#add_thirdparty_script_build(Simple-OpenGL-Image-Library)
#add_thirdparty_script_build(soia-glew-cmake)
#add_thirdparty_script_build(glfw)
#add_thirdparty_script_build(unittest-cpp)
