#!/bin/bash

base_dir="$(dirname "$0")"
source "$base_dir/Common/common.sh"

###################################################
# main

echo_header "Build"

bhelp_args 2 "$@"
echo_help \
		"Usecase: Runs executabe in cmake folder." \
		"Arg0:    Name of cmake generator to use for build." \
		"         This defines the build folder name."

set_project_vars "$1"

find_exec="/usr/bin/find"
run_exec=$($find_exec "$build_dir/Binaries" -executable -name "$2.exe" -type f)

soia_echo "Starting $2"
$run_exec \
	&& echo_success