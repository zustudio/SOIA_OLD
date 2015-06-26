#!/bin/bash

base_dir="$(dirname "$0")"
source "$base_dir/Common/common.sh"

###################################################
# main

echo_header "Generate"

bhelp_1args "$@"
echo_help \
		"Usecase: Generates CMake project in specified folder." \
		"Arg0:    Name of cmake generator to use for build." \
		"         This defines the build folder name."

set_project_vars "$1"

# invoke cmake
cd "$build_dir"
cmake -G "$cmake_generator" .. \
	&& echo_success