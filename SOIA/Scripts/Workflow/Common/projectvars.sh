#!/bin/bash


base_dir="$(dirname "$0")"

function set_project_vars
{
	if [ "$1" == "Visual Studio 14 2015" ] || [ "$1" == "VS" ];then
		build_suffix="VS"
		cmake_generator="Visual Studio 14 2015"
	elif [ "$1" == "MSYS Makefiles" ] || [ "$1" == "MSYS" ];then 
		build_suffix="MSYS"
		cmake_generator="MSYS Makefiles"
	else
		build_suffix="CUSTOM"
		cmake_generator="$1"
	fi
	build_dir="$base_dir/../../Build_$build_suffix"
	build_folder="Build_$build_suffix"
	mkdir -p "$build_dir"
	
	soia_echo "Build folder is: $build_folder."
}