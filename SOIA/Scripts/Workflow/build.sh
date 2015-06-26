#!/bin/bash

base_dir="$(dirname "$0")"
source "$base_dir/Common/common.sh"

###################################################
# main

echo_header "Build"

bhelp_1args "$@"
echo_help \
		"Usecase: Builds CMake project in specified folder." \
		"Arg0:    Name of cmake generator to use for build." \
		"         This defines the build folder name."

set_project_vars "$1"
soia_echo "Build folder is: $build_folder."

# invoke cmake
cd "$build_dir"
cmake --build ./ \
	&& echo_success