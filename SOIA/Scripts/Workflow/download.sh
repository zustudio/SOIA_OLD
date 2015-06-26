#!/bin/bash

base_dir="$(dirname "$0")"
source "$base_dir/Common/echo.sh"

#####################################
# main

echo_header "Download dependencies"

soia_echo "Git submodules"
git submodule update --init --recursive

current_os="Windows"
thirdparty_path="../../ThirdParty/"

soia_echo "Binary Thirdparties"
cd "$thirdparty_path"
online_locations=$(grep -r --include=Location.txt "$current_os>")
for location_string in "$online_locations"
do
	location_regex='(.*)/.*:.*>(.*)<'
	if [[ $location_string =~ $location_regex ]];then
		dir="${BASH_REMATCH[1]}"
		location="${BASH_REMATCH[2]}"
		file_ending=$(echo $location | grep -E -o '\.[^\.]*$')
		file="$dir$file_ending"
		
		soia_echo "Downloading $location."
		
		cd "$dir"
		curl -k -L "$location" -o "$file"
		cd ..
	fi
done
