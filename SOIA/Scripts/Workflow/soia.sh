#!/bin/bash

base_dir="$(dirname "$0")"

source "$base_dir/Common/echo.sh"
source "$base_dir/Common/projectvars.sh"

###################################################
# main

echo_header "SOIA Configure"

if [ "$#" -ne "1" ] || [ "$1" == "-h" ]; then
	echo_help \
		"Usecase: Generates folder to build SOIA." \
		"Arg0:    Name of cmake generator to use for build." \
		"         This defines the build folder name."
	exit
fi

set_project_vars "$1"
soia_echo "Build folder is: $build_folder."

# invoke cmake
cd "$build_folder"
cmake -DTHIRDPARTY_SUCCESS=TRUE -G "$cmake_generator" .. \
	&& echo_success
