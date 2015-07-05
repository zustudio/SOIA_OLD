cmake_minimum_required(VERSION 3.1)

# prepare thirdparty build
make_thirdparty_directories()

# generate build scripts
generate_build_script_zip(drmemory)
generate_build_script_custom(soia-cppcheck-target-cmake "cp -r -T \${L_build_dir}/ ${CMAKE_BINARY_DIR}/Install/ThirdParty/script/\${L_project_name}/")
generate_build_script_custom(cppcheck "make -j8 SRCDIR=build CFGDIR=${CMAKE_BINARY_DIR}/Install/ThirdParty/bin/cfg" "cp \${L_build_dir}/cppcheck.exe ${CMAKE_BINARY_DIR}/Install/ThirdParty/bin/" "cp -r \${L_build_dir}/cfg ${CMAKE_BINARY_DIR}/Install/ThirdParty/bin/cfg")
generate_build_script_cmake(soia-unittest-cpp)
generate_build_script_cmake(glfw -DGLFW_USE_HYBRID_HPG=ON)
generate_build_script_cmake(glew-cmake)
generate_build_script_cmake(Simple-OpenGL-Image-Library)

# register scripts
add_thirdparty_script_build(Simple-OpenGL-Image-Library)
add_thirdparty_script_build(glew-cmake)
add_thirdparty_script_build(glfw)
add_thirdparty_script_build(drmemory)
add_thirdparty_script_build(soia-cppcheck-target-cmake)
add_thirdparty_script_build(cppcheck)
add_thirdparty_script_build(soia-unittest-cpp)


	