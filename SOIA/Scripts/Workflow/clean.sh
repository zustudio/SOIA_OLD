#!/bin/bash

base_dir="$(dirname "$0")"
source "$base_dir/Common/common.sh"

###################################################
# main

echo_header "Build"

bhelp_args 1 "$@"
echo_help \
		"Usecase: Builds CMake project in specified folder." \
		"Arg0:    Name of cmake generator to use for build." \
		"         This defines the build folder name."

set_project_vars "$1"

# invoke cmake
cd "$build_dir/.."
rm -rf "$build_folder" \
	&& echo_success