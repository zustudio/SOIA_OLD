cmake_minimum_required(VERSION 3.1)

# prepare thirdparty build
make_thirdparty_directories()

# generate build scripts
generate_build_script_custom(cppcheck "make -j8 SRCDIR=build CFGDIR=${CMAKE_BINARY_DIR}/Install/ThirdParty/bin/cfg" "cp \${L_build_dir}/cppcheck.exe ${CMAKE_BINARY_DIR}/Install/ThirdParty/bin/" "cp -r \${L_build_dir}/cfg ${CMAKE_BINARY_DIR}/Install/ThirdParty/bin/cfg")
generate_build_script_cmake(unittest-cpp)

# register scripts
add_thirdparty_script_build(cppcheck)
add_thirdparty_script_build(unittest-cpp)

# finalize
set_thirdparty_success()


	