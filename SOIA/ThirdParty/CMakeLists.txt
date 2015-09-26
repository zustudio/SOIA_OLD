cmake_minimum_required(VERSION 3.1)

# prepare thirdparty build
make_thirdparty_directories()

# generate build scripts
generate_build_script_cmake(unittest-cpp)
generate_build_script_cmake(glfw -DGLFW_USE_HYBRID_HPG=ON)
generate_build_script_cmake(soia-glew-cmake)
generate_build_script_cmake(Simple-OpenGL-Image-Library)
generate_build_script_cmake(freetype2)

# register scripts
add_thirdparty_script_build(freetype2)
add_thirdparty_script_build(Simple-OpenGL-Image-Library)
add_thirdparty_script_build(soia-glew-cmake)
add_thirdparty_script_build(glfw)
add_thirdparty_script_build(unittest-cpp)
